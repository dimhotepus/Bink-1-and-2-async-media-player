// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_INCLUDE_IBINK_AUDIO_CONTROLS_H_
#define BINK_MP_INCLUDE_IBINK_AUDIO_CONTROLS_H_

#include <cstdint>
#include <memory>

#include "bink_base.h"
#include "ibink_audio_track.h"

namespace bink {

/**
 * @brief Audio volume settings.
 */
struct AudioVolume {
  /**
   * @brief Specifies the new volume setting from 0 (silent) to 50 (normal)
   * to 100 (maximum amplification).  Note that most sound systems don't do
   * amplification (neither Miles nor DirectSound does) - in these cases,
   * volumes above 50 are the same as 50.
   */
  uint8_t level;
};

/**
 * @brief Balance
 */
struct AudioBalance {
  /**
   * @brief Balance, from 0 (all the way left) to 50 (split evenly between
   * left and right), and 100 (all the way right).
   */
  uint8_t value;
};

/**
 * @brief Bink audio controls.
 */
struct BINK_ATTRIBUTE_NO_VTABLE IBinkAudioControls {
  virtual ~IBinkAudioControls() = 0;

  /**
   * @brief Toggles sound on or off.
   * @param on Should enable sound?
   * @return Whether the sound is currently on (true) or off (false).
   */
  virtual bool ToggleSound(bool on) const noexcept = 0;

  /**
   * @brief Get tracks count.
   * @return Tracks count.
   */
  virtual [[nodiscard]] uint32_t GetTracksCount() const noexcept = 0;

  /**
   * @brief Get track by id.
   * @param track_id Track id.
   * @return Track if any.
   */
  virtual [[nodiscard]] std::unique_ptr<IBinkAudioTrack> GetTrackById(
      AudioTrackId track_id) const noexcept = 0;

  /**
   * @brief Sets the volume of a Bink sound track.  The volume parameter
   * specifies the new volume setting from 0 (silent) to 32768 (normal) to 65536
   * (maximum amplification).  Note that most sound systems don't do
   * amplification (neither Miles nor DirectSound does) - in these cases,
   * volumes above 32768 are the same as 32768.
   * @param track Track id.
   * @param volume Volume.
   * @return void.
   */
  virtual void SetVolume(AudioTrackId track,
                         AudioVolume volume) const noexcept = 0;

  /**
   * @brief Sets the speaker pan (left to right balance) of a Bink sound track.
   * @param track Track id.
   * @param balance Balance.
   * @return void.
   */
  virtual void SetBalance(AudioTrackId track,
                          AudioBalance balance) const noexcept = 0;

  /**
   * @brief This function will perform background sound Bink services
   * explicitly.  This function can be called periodically when you have an
   * extremely CPU-intensive task that is causing the sound to break up.
   * @return void.
   */
  virtual void TickSound() const noexcept = 0;
};

}  // namespace bink

#endif  // !BINK_MP_INCLUDE_IBINK_AUDIO_CONTROLS_H_