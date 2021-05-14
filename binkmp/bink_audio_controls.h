// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_BINK_AUDIO_CONTROLS_H_
#define BINK_MP_BINK_AUDIO_CONTROLS_H_

#include <algorithm>

#include "bink_audio_track.h"
#include "bink_base.h"
#include "deps/bink/bink.h"
#include "ibink_audio_controls.h"

namespace bink {
/**
 * @brief Bink audio controls.
 */
class BinkAudioControls : public IBinkAudioControls {
 public:
  explicit BinkAudioControls(HBINK bink) noexcept : bink_{bink} {}

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(BinkAudioControls);

  /**
   * @brief Toggles sound on or off.  Not a mute!  Tells Bink skip decompressing
   * the audio.
   * @param on Should enable sound decompressing?
   * @return Whether the sound is currently on (true) or off (false).
   */
  bool ToggleSound(bool on) const noexcept override {
    BINK_DCHECK(bink_);
    return ::BinkSetSoundOnOff(bink_, on ? 1 : 0) != 0;
  }

  /**
   * @brief Get track by id.
   * @param track_id Track id.
   * @return Track if any.
   */
  std::unique_ptr<IBinkAudioTrack> GetTrackById(
      AudioTrackId track_id) const noexcept override {
    auto track = std::make_unique<BinkAudioTrack>(bink_, track_id);
    return track->IsOpened() ? std::move(track)
                             : std::unique_ptr<IBinkAudioTrack>{};
  }

  /**
   * @brief Get tracks count.
   * @return Tracks count.
   */
  uint32_t GetTracksCount() const noexcept override {
    BINK_DCHECK(bink_);
    return static_cast<uint32_t>(std::max(0, bink_->NumTracks));
  }

  /**
   * @brief Sets the volume of a Bink sound track.
   * @param track Track id.
   * @param volume Volume.
   * @return void.
   */
  void SetVolume(AudioTrackId track,
                 AudioVolume volume) const noexcept override {
    BINK_DCHECK(bink_);
    ::BinkSetVolume(bink_, track.id, volume.level);
  }

  /**
   * @brief Sets the speaker pan (left to right balance) of a Bink sound track.
   * @param track Track id.
   * @param balance Balance.
   * @return void.
   */
  void SetBalance(AudioTrackId track,
                  AudioBalance balance) const noexcept override {
    BINK_DCHECK(bink_);
    ::BinkSetPan(bink_, track.id, balance.value);
  }

  /**
   * @brief This function will perform background sound Bink services
   * explicitly.  This function can be called periodically when you have an
   * extremely CPU-intensive task that is causing the sound to break up.
   * @return void.
   */
  void TickSound() const noexcept override {
    BINK_DCHECK(bink_);
    ::BinkService(bink_);
  }

 private:
  const HBINK bink_;
};
}  // namespace bink

#endif  // !BINK_MP_BINK_AUDIO_CONTROLS_H_