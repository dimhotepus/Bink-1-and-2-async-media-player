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
#include <thread>

#include "binkmp/bink_media_player_factory.h"
#include "binkmp/ibink_media_player.h"
#include "binkmp/mss_digital_driver_factory.h"
#include "deps/miles/include/mss.h"
#include "scoped_com_initializer.h"

namespace {
/**
 * @brief Bink media player.
 */
std::unique_ptr<bink::IBinkMediaPlayer> bink_media_player{nullptr};

/**
 * @brief Default window style.
 */
constexpr DWORD DefaultWindowStyle{WS_OVERLAPPEDWINDOW /* & ~WS_SIZEBOX*/};

/**
 * @brief Moves window to the center of the primary monitor.
 * @param hwnd Window.
 * @param repaint_after Should repaint window after move?
 * @return true on success, false otherwise.
 */
bool MoveWindowToPrimaryDisplayCenter(_In_ HWND window,
                                      _In_ bool repaint_after) noexcept {
  BINK_DCHECK(!!window);

  RECT window_rect;
  [[maybe_unused]] bool is_ok{!!::GetWindowRect(window, &window_rect)};
  BINK_DCHECK(is_ok);

  const long screen_width{::GetSystemMetrics(SM_CXSCREEN)},
      screen_height{::GetSystemMetrics(SM_CYSCREEN)};
  const int window_width{std::min(screen_width, window_rect.right)},
      window_height{std::min(screen_height, window_rect.bottom)};
  const int x_pos{(screen_width - window_width) / 2},
      y_pos{(screen_height - window_height) / 2};

  is_ok = !!::MoveWindow(window, x_pos, y_pos, window_width, window_height,
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
      sizeof(previous_window_placement), 0U, 0U};

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

      ::SetWindowPos(window, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top,
                     mi.rcMonitor.right - mi.rcMonitor.left,
                     mi.rcMonitor.bottom - mi.rcMonitor.top,
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
 * @brief Fills a window with black pixels.
 * @param window Window.
 */
void ClearToBlack(HWND window) noexcept {
  PAINTSTRUCT ps;
  // Get the repaint DC and then fill the window with black.
  if (HDC dc{::BeginPaint(window, &ps)}) {
    RECT client_rect;
    [[maybe_unused]] bool ok{!!::GetClientRect(window, &client_rect)};
    BINK_DCHECK(ok);

    ok = !!::PatBlt(dc, client_rect.left, client_rect.top,
                    client_rect.right - client_rect.left,
                    client_rect.bottom - client_rect.top, BLACKNESS);
    BINK_DCHECK(ok);

    // The return value is always nonzero.
    // See
    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-endpaint
    (void)::EndPaint(window, &ps);
  }
}

/**
 * @brief Toggles video on/off.
 * @return void.
 */
void ToggleVideoOnOff() noexcept {
  static bool isVideoOn{true};
  isVideoOn = !isVideoOn;

  bink_media_player->ToggleVideo(isVideoOn);
}

/**
 * @brief Toggles sound on/off.
 * @return void.
 */
void ToggleSoundOnOff() noexcept {
  static bool isSoundOn{true};
  isSoundOn = !isSoundOn;

  bink_media_player->GetAudioControls().ToggleSound(isSoundOn);
}

/**
 * @brief Changes sound volume.
 * @param increase Increase volume?
 * @return void.
 */
void ChangeSoundVolume(bool increase) noexcept {
  static uint16_t volume_level{0U};
  constexpr uint16_t VolumeStep{512U};

  volume_level =
      increase
          ? (std::min(volume_level,
                      static_cast<uint16_t>(
                          std::numeric_limits<uint16_t>::max() - VolumeStep)) +
             VolumeStep)
          : (std::max(volume_level, VolumeStep) - VolumeStep);

  const auto &audio_controls = bink_media_player->GetAudioControls();
  audio_controls.SetVolume({.id = 0}, {.level = volume_level});

  const auto track = audio_controls.GetTrackById({.id = 0});
  if (track) {
    bink::AudioTrackInfo track_info;
    [[maybe_unused]] const bool is_ok{track->GetInfo(track_info)};

    BINK_DCHECK(is_ok);
  }
}

void OnChar(HWND window, TCHAR ch, int) noexcept {
  if (ch == _T('F') || ch == _T('f')) {
    ToggleFullscreenWindow(window, DefaultWindowStyle);
  } else if (ch == _T('V') || ch == _T('v')) {
    ToggleVideoOnOff();
  } else if (ch == _T('S') || ch == _T('s')) {
    ToggleSoundOnOff();
  } else if (ch == _T('+') || ch == _T('-')) {
    ChangeSoundVolume(ch == _T('+'));
  } else {
    // Just close the window if the user hits any other key.
    ::DestroyWindow(window);
  }
}

void OnPaint([[maybe_unused]] HWND window) noexcept {
  ClearToBlack(window);
  bink_media_player->Present(true);
}

void OnKillFocus(HWND, HWND) noexcept {
  // Pause the video when the focus leaves the window.
  bink_media_player->Pause();
}

void OnSetFocus(HWND, HWND) noexcept {
  // Resume the video when the focus set to the window.
  if (bink_media_player) {
    bink_media_player->Play();
  }
}

BOOL OnEraseBkgnd(HWND, HDC) noexcept { return TRUE; }

BOOL OnWindowPosChanging(HWND, WINDOWPOS *pos) noexcept {
  // Is the window even being moved?
  if (!(pos->flags & SWP_NOMOVE)) {
    // Yup, it's being moved - ask the BinkBuffer API to align the coordinates
    // to a fast boundary.
    bink_media_player->AdjustWindowPos(pos->x, pos->y);
  }
  return FALSE;
}

void OnWindowPosChanged(HWND, const WINDOWPOS *) noexcept {
  // Tell the BinkBuffer API when the window moves.
  if (bink_media_player) {
    bink_media_player->SetWindowOffset(0, 0);
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
 * @param previous_instance Previous app instance [obsolete].
 * @return Window.
 */
HWND CreateBinkWindow(_In_ HINSTANCE instance,
                      _In_opt_ HINSTANCE previous_instance) noexcept {
  // Create the window class if this is the first instance.
  if (!previous_instance) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = instance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.lpszClassName = _T("BinkMediaPlayer_Wnd");

    if (!::RegisterClass(&wc)) {
      return nullptr;
    }

    // Return the new window with a tiny initial default size (it is resized
    // later on with the help of the BinkBuffer API).
    return ::CreateWindowEx(0, wc.lpszClassName, _T("Bink Media Player"),
                            DefaultWindowStyle, CW_USEDEFAULT, CW_USEDEFAULT,
                            1024, 768, 0, 0, instance, 0);
  }

  return nullptr;
}
}  // namespace

int WINAPI WinMain(_In_ HINSTANCE instance,
                   _In_opt_ HINSTANCE previous_instance, _In_ LPSTR cmd_line,
                   _In_ int cmd_show) {
  const auto scoped_com_initializer = bink::ScopedComInitializer::New(
      bink::ScopedComInitializerFlags::kApartmentThreaded |
      bink::ScopedComInitializerFlags::kDisableOle1Dde |
      bink::ScopedComInitializerFlags::kSpeedOverMemory);
  if (const auto *rc = std::get_if<std::error_code>(&scoped_com_initializer)) {
    std::string error{rc->message()};
    error.insert(0, "Component Object Model initialization failed: ");

    MessageBoxA(0, error.c_str(), "Bink Media Player - COM initialize Error",
                MB_OK | MB_ICONSTOP);
    return 1;
  }

  HWND window{CreateBinkWindow(instance, previous_instance)};
  if (!window) {
    MessageBox(0, L"Error creating window.",
               L"Bink Media Player - Window Create Error", MB_OK | MB_ICONSTOP);
    return 2;
  }

  /*const auto mss_create_result =
      bink::MssDigitalDriverFactory::Create({.frequency = 44100U,
                                             .bits_per_sample = 16,
                                             .channels_count = MSS_MC_STEREO});
  if (const auto *error = std::get_if<const char *>(&mss_create_result)) {
    ::MessageBoxA(window, *error, "Miles Sound System - Driver Open Error",
                  MB_OK | MB_ICONSTOP);
    return 3;
  }
  const auto &mss_digital_driver =
      std::get<std::unique_ptr<bink::IMssDigitalDriver>>(mss_create_result);*/

  // Too much cores are nonsense, as we have no enough workload for them.
  // Play with this to get optimal values on your platform.
  const auto good_enough_decoder_cpu_cores_count = static_cast<uint8_t>(
      std::clamp(std::thread::hardware_concurrency(), 1U, 4U));
  auto bink_create_result = bink::BinkMediaPlayerFactory::Create(
      {.media_path = cmd_line,
       .window = window,
       .sound_output_system = bink::BinkSoundOutputSystem::DirectSound,
       .used_cpus_count = good_enough_decoder_cpu_cores_count});
  if (const auto *error = std::get_if<const char *>(&bink_create_result)) {
    ::MessageBoxA(window, *error, "Bink Media Player - Media Open Error",
                  MB_OK | MB_ICONSTOP);
    return 4;
  }

  bink_media_player.swap(
      std::get<std::unique_ptr<bink::IBinkMediaPlayer>>(bink_create_result));

  // Move window to primary display center.
  MoveWindowToPrimaryDisplayCenter(window, true);
  // Now display the window and start the message loop.
  ::ShowWindow(window, cmd_show);

  MSG msg;
  for (;;) {
    // Are there any messages to handle?
    if (::PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
      if (msg.message == WM_QUIT) break;

      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
    } else {
      // Is it time for a new Bink frame?
      if (bink_media_player->CanPresent()) {
        // Yup, draw the next frame.
        bink_media_player->Present(false);

        // Check player has frames to present.
        if (!bink_media_player->HasFrames()) {
          // No frames, lets close.
          ::DestroyWindow(window);
        }
      } else {
        // Nope, give the rest of the system a chance to run (1 ms).
        ::Sleep(1);
      }
    }
  }

  return 0;
}
