// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.
//
// Based on "Example of using Bink with BinkBuffers on Win32, Author: Jeff
// Roberts".

#define NOMINMAX
#include <Windows.h>
#include <tchar.h>
#include <windowsx.h>

#include <algorithm>
#include <limits>
#include <optional>
#include <thread>

#include "bink_media_player_host.h"
#include "message_dispatcher.h"
#include "scoped_com_initializer.h"
#include "scoped_show_cursor.h"
#include "scoped_timer_resolution.h"
//
#include "deps/miles/include/mss.h"

namespace {

/**
 * @brief Bink media player.
 */
std::optional<bink::BinkMediaPlayerHost> bink_media_player_host;

/**
 * @brief Default window style.
 */
constexpr DWORD DefaultWindowStyle{WS_OVERLAPPEDWINDOW};

/**
 * @brief Moves window to the center of the primary monitor.
 * @param hwnd Window.
 * @param repaint_after Should repaint window after move?
 * @return true on success, false otherwise.
 */
bool MoveToMainDisplayCenter(_In_ HWND window,
                             _In_ bool repaint_after) noexcept {
  BINK_DCHECK(!!window);

  RECT window_rect;
  bool is_ok{!!::GetWindowRect(window, &window_rect)};
  BINK_DCHECK(is_ok);

  const unsigned dpi{::GetDpiForWindow(window)};

  const long screen_width{::GetSystemMetricsForDpi(SM_CXSCREEN, dpi)},
      screen_height{::GetSystemMetricsForDpi(SM_CYSCREEN, dpi)};
  const int window_width{std::min(screen_width, bink::GetWidth(window_rect))},
      window_height{std::min(screen_height, bink::GetHeight(window_rect))};
  const int x{(screen_width - window_width) / 2},
      y{(screen_height - window_height) / 2};

  is_ok = is_ok && !!::MoveWindow(window, x, y, window_width, window_height,
                                  repaint_after ? TRUE : FALSE);
  BINK_DCHECK(is_ok);

  return is_ok;
}

/**
 * @brief Toggles between full screen and normal size window.  See
 * https://devblogs.microsoft.com/oldnewthing/20100412-00/?p=14353
 * @param window Window.
 * @param default_window_style Window style when window is of normal size.
 */
void ToggleFullscreenWindow(_In_ HWND window, _In_ DWORD default_window_style) {
  static WINDOWPLACEMENT previous_window_placement{
      sizeof(previous_window_placement), 0U, 0U, {}, {}, {}};

  BINK_DCHECK(!!window);

  const LONG_PTR window_style{GetWindowLongPtr(window, GWL_STYLE)};
  const bool is_fullscreen_now{
      !(window_style & static_cast<LONG_PTR>(default_window_style))};
  if (!is_fullscreen_now) {
    MONITORINFO mi{sizeof(mi), {}, {}, 0U};

    if (::GetWindowPlacement(window, &previous_window_placement) &&
        ::GetMonitorInfo(::MonitorFromWindow(window, MONITOR_DEFAULTTOPRIMARY),
                         &mi)) {
      ::SetWindowLongPtr(
          window, GWL_STYLE,
          window_style & ~static_cast<LONG_PTR>(default_window_style));

      const RECT &monitor_rc{mi.rcMonitor};

      ::SetWindowPos(window, HWND_TOP, monitor_rc.left, monitor_rc.top,
                     bink::GetWidth(monitor_rc), bink::GetHeight(monitor_rc),
                     SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
    }
  } else {
    ::SetWindowLongPtr(
        window, GWL_STYLE,
        window_style | static_cast<LONG_PTR>(default_window_style));

    ::SetWindowPlacement(window, &previous_window_placement);
    ::SetWindowPos(window, nullptr, 0, 0, 0, 0,
                   SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER |
                       SWP_FRAMECHANGED);
  }
}

/**
 * @brief Converts UTF8 to wide.
 * @param source UTF8 string.
 * @return Wide string.
 */
[[nodiscard]] std::wstring Utf8ToWide(const std::string &source) {
  if (source.empty()) return std::wstring{};

  if (source.size() > static_cast<size_t>(std::numeric_limits<int>::max())) {
    BINK_DCHECK(false);  // UTF8ToWide source size is too large.
    return std::wstring{};
  }

  const int size{::MultiByteToWideChar(
      CP_UTF8, 0, &source[0], static_cast<int>(source.size()), nullptr, 0)};
  BINK_DCHECK(size > 0);
  std::wstring result(static_cast<size_t>(size), L'\0');
  if (::MultiByteToWideChar(CP_UTF8, 0, &source[0],
                            static_cast<int>(source.size()), &result[0],
                            size) != size) {
    BINK_DCHECK(false);  // MultiByteToWideChar failed.
    return std::wstring{};
  }
  return result;
}

/**
 * @brief Extract short video name from command line.
 * @param command_line Command line.
 * @return Short exe name.
 */
[[nodiscard]] std::optional<std::string> get_short_video_name_from_command_line(
    const std::string &command_line) noexcept {
  // Sometimes /foo/bla is also passed on windows, ex. by Visual Studio g3log
  // tests discovery.
  constexpr char native_path_separators[]{"\\/"};

  // Assume "x:\zzzzz\yyyy.exe" www on Windows.
  if (command_line.starts_with('"')) {
    const size_t end_double_quote_idx{command_line.find('"', 1U)};
    const size_t separator_before_name_idx{command_line.find_last_of(
        native_path_separators, end_double_quote_idx)};

    if (end_double_quote_idx != std::string::npos &&
        separator_before_name_idx != std::string::npos) {
      return command_line.substr(
          separator_before_name_idx + 1,
          end_double_quote_idx - separator_before_name_idx - 1);
    }
  }

  // Has path separators.
  if (const size_t separator_before_name_idx{
          command_line.find_last_of(native_path_separators)};
      separator_before_name_idx != std::string::npos) {
    return command_line.substr(
        separator_before_name_idx + 1,
        command_line.size() - separator_before_name_idx - 1);
  }

  // As is.
  return command_line;
}

void OnChar(HWND window, TCHAR ch, int) noexcept {
  if (ch == _T('F') || ch == _T('f')) {
    ToggleFullscreenWindow(window, DefaultWindowStyle);
  } else {
    // Just close the window if the user hits any other key.
    ::DestroyWindow(window);
  }
}

void OnPaint([[maybe_unused]] HWND window) noexcept {
  bink_media_player_host->OnPaint(window);
}

void OnKillFocus(HWND, HWND) noexcept {
  // Pause the video when the focus leaves the window.
  bink_media_player_host->Pause();
}

void OnSetFocus(HWND, HWND) noexcept {
  // Resume the video when the focus set to the window.
  if (bink_media_player_host) bink_media_player_host->Play();
}

BOOL OnEraseBkgnd(HWND, HDC) noexcept {
  return bink_media_player_host->OnEraseBackground();
}

BOOL OnWindowPosChanging(HWND, WINDOWPOS *pos) noexcept {
  // Window is being moved - ask the BinkBuffer API to align the coordinates
  // to a fast boundary.
  return bink_media_player_host
             ? bink_media_player_host->OnWindowPositionChanging(pos)
             : FALSE;
}

void OnWindowPosChanged(HWND window, const WINDOWPOS *pos) noexcept {
  // Tell the BinkBuffer API when the window moves.
  if (bink_media_player_host) {
    bink_media_player_host->OnWindowPositionChanged(window, pos);
  }
}

void OnDestroy(HWND) noexcept {
  // Post the quit message.
  ::PostQuitMessage(0);
}

/**
 * @brief The main window message procedure.
 * @param window Window.
 * @param message Window message.
 * @param wParam Wide message param.
 * @param lParam Low message param.
 * @return Message processing result code.
 */
LRESULT WINAPI WindowProc(HWND window, UINT message, WPARAM wParam,
                          LPARAM lParam) {
  switch (message) {
    HANDLE_MSG(window, WM_PAINT, OnPaint);
    HANDLE_MSG(window, WM_CHAR, OnChar);
    HANDLE_MSG(window, WM_KILLFOCUS, OnKillFocus);
    HANDLE_MSG(window, WM_SETFOCUS, OnSetFocus);
    HANDLE_MSG(window, WM_ERASEBKGND, OnEraseBkgnd);
    HANDLE_MSG(window, WM_WINDOWPOSCHANGING, OnWindowPosChanging);
    HANDLE_MSG(window, WM_WINDOWPOSCHANGED, OnWindowPosChanged);
    HANDLE_MSG(window, WM_DESTROY, OnDestroy);
  }
  // Call the OS default window procedure.
  return ::DefWindowProc(window, message, wParam, lParam);
}

/**
 * @brief Creates a window class and window handle.
 * @param instance App instance.
 * @param cmd_line Command line.
 * @return Window.
 */
[[nodiscard]] HWND CreateBinkWindow(_In_ HINSTANCE instance,
                                    _In_z_ LPCSTR cmd_line) noexcept {
  WNDCLASS wc = {};
  // Handle resizes in WM_PAINT.
  wc.style = CS_OWNDC | CS_VREDRAW | CS_HREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = instance;
  wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
  wc.lpszClassName = _T("BinkMediaPlayer_Wnd");

  if (!::RegisterClass(&wc)) {
    return nullptr;
  }

  const auto maybe_short_video_name =
      get_short_video_name_from_command_line(cmd_line);
  const std::wstring short_video_name{
      Utf8ToWide(maybe_short_video_name.value_or(std::string{"N/A"}))};

  std::wstring window_title{_T("Bink Media Player --- ")};
  window_title.append(short_video_name);

  // Return the new window with a tiny initial default size (it is resized later
  // on with the help of the BinkBuffer API).
  return ::CreateWindowEx(0, wc.lpszClassName, window_title.c_str(),
                          DefaultWindowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
                          1024, 768, 0, 0, instance, 0);
}

}  // namespace

int WINAPI WinMain(_In_ HINSTANCE instance, _In_opt_ HINSTANCE,
                   _In_ LPSTR cmd_line, _In_ int cmd_show) {
  // Bink depends on COM.
  const auto scoped_com_initializer = bink::ScopedComInitializer::New(
      bink::ScopedComInitializerFlags::kApartmentThreaded |
      bink::ScopedComInitializerFlags::kDisableOle1Dde |
      bink::ScopedComInitializerFlags::kSpeedOverMemory);
  if (!scoped_com_initializer.has_value()) {
    std::string error{scoped_com_initializer.error().message()};
    error.insert(0, "Component Object Model initialization failed: ");

    MessageBoxA(0, error.c_str(), "Bink Media Player - COM Initialize Error",
                MB_OK | MB_ICONSTOP);
    return 1;
  }

  using namespace std::chrono_literals;

  // Increase precision of timing functions.  Consume more power for high
  // precision timers.
  const auto scoped_timer_resolution = bink::ScopedTimerResolution::New(8ms);
  if (const auto *rc = std::get_if<unsigned>(&scoped_timer_resolution)) {
    std::string error{std::to_string(*rc)};
    error.insert(0, "Scoped timer resolution is not set: ");

    MessageBoxA(0, error.c_str(),
                "Bink Media Player - Timer Resolution Change Error",
                MB_OK | MB_ICONSTOP);
    return 2;
  }

  HWND window{CreateBinkWindow(instance, cmd_line)};
  if (!window) {
    MessageBox(0, L"Error creating window.",
               L"Bink Media Player - Window Create Error", MB_OK | MB_ICONSTOP);
    return 3;
  }

  constexpr unsigned kBinkFlags{0};

  // Too much cores are nonsense, as we have no enough workload for them.  Play
  // with this to get optimal values on your platform.
  const auto good_enough_decoder_cpu_cores_count = static_cast<uint8_t>(
      std::clamp(std::thread::hardware_concurrency(), 1U, 2U));  //-V112
  auto bink_media_player_result = bink::BinkMediaPlayerHost::New(
      std::nullopt,
      {.frequency = 44100U,
       .bits_per_sample = 16,
       .channels_count = MSS_MC_USE_SYSTEM_CONFIG},
      {.media_path = cmd_line,
       .window = window,
       .bink_flags = kBinkFlags,
       .used_cpus_count = good_enough_decoder_cpu_cores_count});
  if (!bink_media_player_result.has_value()) {
    ::MessageBoxA(window, bink_media_player_result.error(),
                  "Bink Media Player - Media Open Error", MB_OK | MB_ICONSTOP);
    return 4;  //-V112
  }

  auto maybe_bink_media_player =
      std::optional{std::move(*bink_media_player_result)};
  bink_media_player_host.swap(maybe_bink_media_player);

  bink::BinkMediaInfo media_info = {};
  if (!bink_media_player_host->GetMediaInfo(media_info)) {
    ::MessageBoxA(window, "Unable to get media info.",
                  "Bink Media Player - Media Open Error", MB_OK | MB_ICONSTOP);
    return 5;
  }

  // Size the window such that its client area exactly fits our Bink movie.
  ::SetWindowPos(window, nullptr, 0, 0,
                 static_cast<int>(media_info.window_width),
                 static_cast<int>(media_info.window_height), SWP_NOMOVE);

  // Move window to primary display center.
  MoveToMainDisplayCenter(window, true);
  // Now display the window and start the message loop.
  ::ShowWindow(window, cmd_show);

  // Hide cursor while playing.
  bink::ScopedShowCursor scoped_show_cursor{false};

  const auto on_idle = [&]() noexcept {
    const auto tick_result = bink_media_player_host->Tick();

    // Has Bink presented something?
    if (tick_result != bink::BinkMediaPlayerHostTickResult::NotReady) {
      const auto has_frames =
          tick_result == bink::BinkMediaPlayerHostTickResult::HasFrames;

      // No frames, lets close.
      if (!has_frames) ::DestroyWindow(window);
    } else {
      // Nope, give the rest of the system a chance to run (1 ms).
      std::this_thread::sleep_for(1ms);
    }
  };

  const bink::MessageDispatcher message_dispatcher{nullptr, on_idle};

  for (;;) {
    // Run dispatch message cycle.
    if (!message_dispatcher.Dispatch()) break;
  }

  return 0;
}
