// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.
//
// Bink media player host.

#ifndef BINK_MEDIA_PLAYER_BINK_MEDIA_PLAYER_HOST_H_
#define BINK_MEDIA_PLAYER_BINK_MEDIA_PLAYER_HOST_H_

#include <Windows.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>

#include "binkmp/include/bink_general_settings.h"
#include "binkmp/include/bink_media_player_factory.h"
#include "binkmp/include/mss_digital_driver_factory.h"

namespace bink {

/**
 * @brief Get width.
 * @param rc Rectangle.
 * @return width.
 */
constexpr long GetWidth(RECT rc) noexcept { return rc.right - rc.left; }

/**
 * @brief Get height.
 * @param rc Rectangle.
 * @return Height.
 */
constexpr long GetHeight(RECT rc) noexcept { return rc.bottom - rc.top; }

/**
 * @brief Bink general settings.
 */
struct BinkMediaPlayerHostGeneralSettings {
  /**
   * @brief Bink malloc.
   */
  bink::BinkMalloc bink_malloc;
  /**
   * @brief Bink free.
   */
  bink::BinkFree bink_free;
  /**
   * @brief Volume level [0..100].
   */
  uint8_t volume_level;
};

/**
 * @brief Bink media player settings.
 */
struct BinkMediaPlayerHostSettings {
  /**
   * @brief Path to opened Bink media.
   */
  const char *media_path;
  /**
   * @brief Window to use as media output.
   */
  void *window;
  /**
   * @brief Native Bink flags.  See BINK_OPEN_FLAGS, like BINKALPHA, etc.
   */
  unsigned int bink_flags;
  /**
   * @brief Native Bink Buffer flags.  See BINKBUFFER_OPEN_FLAGS, like
   * BINKBUFFERPRIMARY.
   */
  unsigned int buffer_flags;
  /**
   * @brief How many cpu cores to use for async decoding.
   */
  unsigned char used_cpus_count;
  /**
   * @brief Padding.
   */
  std::byte pad_[sizeof(char *) - sizeof(used_cpus_count)];
};

/**
 * @brief Bink media player host tick result.
 */
enum class BinkMediaPlayerHostTickResult {
  /**
   * @brief Host not ready.  Run other stuff instead.
   */
  NotReady,
  /**
   * @brief Host has frames.  Bink video is playing.
   */
  HasFrames,
  /**
   * @brief Host has no frames.  Bink video completed.
   */
  NoFrames
};

/**
 * @brief Bink media player host.
 */
class BinkMediaPlayerHost {
 public:
  /**
   * @brief Bink media player host creation result.
   */
  using NewResult = std::variant<BinkMediaPlayerHost, const char *>;

  /**
   * @brief Creates bink media player host.
   * @param maybe_general_settings General settings.
   * @param mss_settings Miles settings.
   * @param player_settings Bink media player settings.
   * @return BInk media player host.
   */
  [[nodiscard]] static NewResult New(
      std::optional<BinkMediaPlayerHostGeneralSettings> maybe_general_settings,
      bink::MssDigitalDriverSettings mss_settings,
      const BinkMediaPlayerHostSettings &player_settings) noexcept;

  BINK_NO_COPY_CTOR_AND_ASSIGNMENT(BinkMediaPlayerHost);

  BinkMediaPlayerHost(BinkMediaPlayerHost &&c) noexcept;
  BinkMediaPlayerHost &operator=(BinkMediaPlayerHost &&c) noexcept;

  /**
   * @brief Ticks host.
   * @return BinkMediaPlayerTickResult.
   */
  [[nodiscard]] BinkMediaPlayerHostTickResult Tick() const noexcept;

  /**
   * @brief Play.
   */
  void Play() const noexcept;

  /**
   * @brief Pause.
   */
  void Pause() const noexcept;

  /**
   * @brief Get media info.
   * @param media_info media info.
   * @return true if success, false otherwise.
   */
  [[nodiscard]] bool GetMediaInfo(
      bink::BinkMediaInfo &media_info) const noexcept;

  /**
   * @brief On paint.
   * @param window Window.
   */
  void OnPaint([[maybe_unused]] HWND window) const noexcept;

  /**
   * @brief On erase background.
   * @return TRUE.
   */
  BOOL OnEraseBackground() const noexcept { return 1; }

  /**
   * @brief On window position changing.
   * @param pos Window position.
   * @return TRUE or FALSE.
   */
  BOOL OnWindowPositionChanging(WINDOWPOS *pos) const noexcept;

  /**
   * @brief On window position changed.
   * @param window Window.
   * @param pos Window position.
   */
  void OnWindowPositionChanged(HWND window,
                               const WINDOWPOS *pos) const noexcept;

 private:
  /**
   * @brief Bink media host ctor.
   * @param mss_digital_driver Miles digital driver.
   * @param bink_media_player Bink media player.
   */
  BinkMediaPlayerHost(
      std::unique_ptr<bink::IMssDigitalDriver> mss_digital_driver,
      std::unique_ptr<bink::IBinkMediaPlayer> bink_media_player) noexcept
      : mss_digital_driver_{std::move(mss_digital_driver)},
        bink_media_player_{std::move(bink_media_player)} {}

  /**
   * @brief Miles digital driver.
   */
  std::unique_ptr<bink::IMssDigitalDriver> mss_digital_driver_;
  /**
   * @brief Bink media player.
   */
  std::unique_ptr<bink::IBinkMediaPlayer> bink_media_player_;
};

}  // namespace bink

#endif  // BINK_MEDIA_PLAYER_BINK_MEDIA_PLAYER_HOST_H_