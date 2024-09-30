// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_INCLUDE_BINK_MEDIA_PLAYER_SETTINGS_H_
#define BINK_MP_INCLUDE_BINK_MEDIA_PLAYER_SETTINGS_H_

#include "bink_base.h"

namespace bink {

/**
 * @brief Bink sound output system.
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
  /**
   * @brief XAudio2.
   */
  XAudio2,
#endif
#ifndef __APPLE__
  /**
   * @brief Miles Sound System.
   */
  Miles,
#endif
#ifdef __linux__
  /**
   * @brief OpenAL.
   */
  OpenAL,
#endif
#ifdef __APPLE__
  /**
   * @brief MacOS Sound Manager.
   */
  SoundManager,
  /**
   * @brief MacOS Core Audio.
   */
  CoreAudio
#endif
};

struct BinkMediaPlayerSettings {
  /**
   * @brief Path to opened Bink media.
   */
  const char* media_path;
  /**
   * @brief Window to use as media output.
   */
  void* window;
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
   * @brief Sound ouput system.
   */
  BinkSoundOutputSystem sound_output_system;

#if defined(_WIN32)
  /**
   * @brief Either Miles Sound System HDIGDRIVER handle that is returned from
   * the Miles function (AIL_waveOutOpen); DirectSound object handle that is
   * returned from the DirectSound function, CreateDirectSound or IXAudio2
   * handle from XAudio2Create.
   */
  void* miles_driver_or_direct_sound_or_xaudio2;
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

#endif  // !BINK_MP_INCLUDE_BINK_MEDIA_PLAYER_SETTINGS_H_