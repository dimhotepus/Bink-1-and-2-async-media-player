// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_BINK_MP_SETTINGS_H_
#define BINK_MP_BINK_MP_SETTINGS_H_

#include "bink_base.h"
#include "deps/bink/bink.h"

namespace bink {
/**
 * @brief Bink sound ouput system.
 */
enum class BinkSoundOutputSystem {
  /**
   * @brief Default unknown argument.
   */
  Unknown,
#ifdef _WIN32
  /**
   * @brief Direct Sound.
   */
  DirectSound,
#endif
#ifndef __APPLE__
  /**
   * @brief Miles Sound System.
   */
  Miles,
#endif
#ifdef __linux__
  /**
   * @brief SDL_mixer.
   */
  SdlMixer,
#endif
#ifdef __APPLE__
  /**
   * @brief MacOS Sound Manager.
   */
  SoundManager
#endif
};

struct BinkMediaPlayerSettings {
  /**
   * @brief Path to opened Bink media.
   */
  const char* media_path;
  /**
   * @brief Native Bink flags.  See BINK_OPEN_FLAGS, like BINKALPHA, etc.
   */
  unsigned int bink_flags;
  /**
   * @brief Window to use as media output.
   */
  void* window;
  /**
   * @brief Native Bink Buffer flags.  See BINKBUFFER_OPEN_FLAGS, like
   * BINKBUFFERPRIMARY.
   */
  unsigned int buffer_flags;
  /**
   * @brief Sound ouput system.
   */
  BinkSoundOutputSystem sound_output_system;

#if defined(_WIN32)
  /**
   * @brief Either Miles Sound System HDIGDRIVER handle that is returned from
   * the Miles function (AIL_waveOutOpen), or DirectSound object handle that is
   * returned from the DirectSound function, CreateDirectSound.
   */
  void* miles_driver_or_direct_sound;
#elif !defined(__APPLE__)
  /**
   * @brief Miles Sound System HDIGDRIVER handle that is returned from the Miles
   * function (AIL_waveOutOpen).
   */
  void* miles_driver;
#endif

  /**
   * @brief How many cpu cores to use for async decoding.
   */
  unsigned char used_cpus_count;
  /**
   * @brief Padding.
  */
  std::byte pad_[sizeof(char*) - sizeof(used_cpus_count)];
};
}  // namespace bink

#endif  // !BINK_MP_BINK_MP_SETTINGS_H_