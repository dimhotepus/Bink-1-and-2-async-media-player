// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.
//
// Bink media player host.

#include "bink_media_player_host.h"

#include <Windows.h>

namespace {

/**
 * @brief Fills a window with black pixels.
 * @param window Window.
 */
void ClearToBlack(HWND window) noexcept {
  BINK_DCHECK(!!window);

  PAINTSTRUCT ps;
  // Get the repaint DC and then fill the window with black.
  if (HDC dc{::BeginPaint(window, &ps)}) {
    const RECT &rc{ps.rcPaint};

    [[maybe_unused]] const bool is_ok{
        !!::PatBlt(dc, rc.left, rc.top, bink::GetWidth(rc), bink::GetHeight(rc),
                   BLACKNESS)};
    BINK_DCHECK(is_ok);

    // The return value is always nonzero.
    // See
    // https://docs.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-endpaint
    (void)::EndPaint(window, &ps);
  }
}

/**
 * @brief Gets video offsets for window.
 * @param content Media.
 * @param window Window.
 * @return {x, y} offsets for video in |window|.
 */
std::tuple<unsigned, unsigned> GetMediaOffsetsForWindow(
    bink::BinkMediaInfo content, HWND window) noexcept {
  BINK_DCHECK(!!window);

  RECT rc;
  [[maybe_unused]] const bool is_ok{!!::GetClientRect(window, &rc)};
  BINK_DCHECK(is_ok);

  const auto width = static_cast<unsigned>(bink::GetWidth(rc));
  const auto height = static_cast<unsigned>(bink::GetHeight(rc));

  const auto get_shift = [](unsigned area, unsigned inner) noexcept {
    return area > inner ? (area - inner) / 2U : 0U;
  };

  const unsigned x{get_shift(width, content.width)};
  const unsigned y{get_shift(height, content.height)};

  return std::tuple{x, y};
}

}  // namespace

namespace bink {

[[nodiscard]] BinkMediaPlayerHost::NewResult BinkMediaPlayerHost::New(
    std::optional<BinkMediaPlayerHostGeneralSettings> maybe_general_settings,
    bink::MssDigitalDriverSettings mss_settings,
    const BinkMediaPlayerHostSettings &player_settings) noexcept {
  if (maybe_general_settings.has_value()) {
    const auto &general_settings = *maybe_general_settings;
    auto settings = bink::BinkGeneralSettings();

    // Memory handlers should be set first as bink relies on them.
    settings.SetMemoryHandlers(general_settings.bink_malloc,
                               general_settings.bink_free);
  }

  auto mss_create_result = bink::MssDigitalDriverFactory::Create(mss_settings);
  if (auto *error = std::get_if<const char *>(&mss_create_result))
      [[unlikely]] {
    return NewResult{*error};
  }

  auto mss_digital_driver = std::move(
      std::get<std::unique_ptr<bink::IMssDigitalDriver>>(mss_create_result));

  auto bink_create_result =
      bink::BinkMediaPlayerFactory::Create(bink::BinkMediaPlayerSettings{
          .media_path = player_settings.media_path,
          .window = player_settings.window,
          .bink_flags = player_settings.bink_flags,
          .buffer_flags = player_settings.buffer_flags,
          .sound_output_system = bink::BinkSoundOutputSystem::Miles,
          .miles_driver_or_direct_sound = mss_digital_driver->native_handle(),
          .used_cpus_count = player_settings.used_cpus_count});
  if (const auto *error = std::get_if<const char *>(&bink_create_result))
      [[unlikely]] {
    return NewResult{*error};
  }

  std::unique_ptr<bink::IBinkMediaPlayer> bink_media_player = std::move(
      std::get<std::unique_ptr<bink::IBinkMediaPlayer>>(bink_create_result));

  if (maybe_general_settings.has_value()) {
    const auto &audio_controls = bink_media_player->GetAudioControls();

    // Ok, media is open, let's set volume for all tracks.
    const uint32_t tracks_count{audio_controls.GetTracksCount()};
    for (uint32_t i{0}; i < tracks_count; ++i) {
      audio_controls.SetVolume(
          bink::AudioTrackId{.id = i},
          bink::AudioVolume{.level = maybe_general_settings->volume_level});
    }
  }

  return NewResult{BinkMediaPlayerHost{std::move(mss_digital_driver),
                                       std::move(bink_media_player)}};
}

BinkMediaPlayerHost::BinkMediaPlayerHost(BinkMediaPlayerHost &&c) noexcept
    : mss_digital_driver_{std::move(c.mss_digital_driver_)},
      bink_media_player_{std::move(c.bink_media_player_)} {}

BinkMediaPlayerHost &BinkMediaPlayerHost::operator=(
    BinkMediaPlayerHost &&c) noexcept {
  std::swap(mss_digital_driver_, c.mss_digital_driver_);
  std::swap(bink_media_player_, c.bink_media_player_);
  return *this;
}

[[nodiscard]] BinkMediaPlayerHostTickResult BinkMediaPlayerHost::Tick() const noexcept {
  // Is it time for a new Bink frame?
  if (bink_media_player_->CanPresent()) {
    // Yup, draw the next frame.
    bink_media_player_->Present(false);

    // Check player has frames to present.
    return bink_media_player_->HasFrames()
        ? BinkMediaPlayerHostTickResult::HasFrames
        : BinkMediaPlayerHostTickResult::NoFrames;
  }

  // Nope, give the rest of the system a chance to run.
  return BinkMediaPlayerHostTickResult::NotReady;
}

void BinkMediaPlayerHost::Play() const noexcept { bink_media_player_->Play(); }

void BinkMediaPlayerHost::Pause() const noexcept {
  bink_media_player_->Pause();
}

[[nodiscard]] bool BinkMediaPlayerHost::GetMediaInfo(
    bink::BinkMediaInfo &media_info) const noexcept {
  return bink_media_player_->GetMediaInfo(media_info);
}

void BinkMediaPlayerHost::OnPaint([[maybe_unused]] HWND window) const noexcept {
  ClearToBlack(window);
  bink_media_player_->Present(true);
}

BOOL BinkMediaPlayerHost::OnWindowPositionChanging(
    WINDOWPOS *pos) const noexcept {
  // Is the window even being moved?
  if (!(pos->flags & SWP_NOMOVE)) {
    // Yup, it's being moved - ask the BinkBuffer API to align the coordinates
    // to a fast boundary.
    bink_media_player_->AdjustWindowPos(pos->x, pos->y);
  }
  return FALSE;
}

void BinkMediaPlayerHost::OnWindowPositionChanged(
    HWND window, const WINDOWPOS *pos) const noexcept {
  bink::BinkMediaInfo content;

  [[maybe_unused]] bool is_ok{bink_media_player_->GetMediaInfo(content)};
  BINK_DCHECK(is_ok);

  const auto [x, y] = GetMediaOffsetsForWindow(content, window);

  // Tell the BinkBuffer API to scale when needed.
  is_ok = bink_media_player_->SetWindowScale(pos->cx, pos->cy);
  BINK_DCHECK(is_ok);

  // Tell the BinkBuffer API when the window moves.
  is_ok = bink_media_player_->SetWindowOffset(x, y);
  BINK_DCHECK(is_ok);
}

}  // namespace bink