// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_BINK_AUDIO_TRACK_H_
#define BINK_MP_BINK_AUDIO_TRACK_H_

#include <algorithm>
#include <cstdint>
#include <vector>

#include "bink_base.h"
#include "deps/bink/bink.h"
#include "ibink_audio_track.h"

namespace bink {
/**
 * @brief Bink audio track.
 */
class BinkAudioTrack : public IBinkAudioTrack {
 public:
  /**
   * @brief Creates Bink audio track.
   * @param bink Bink media handle.
   * @param track_id Track id.
   * @return nothing.
   */
  BinkAudioTrack(HBINK bink, AudioTrackId track_id) noexcept
      : bink_track_{::BinkOpenTrack(bink, track_id.id)} {
    BINK_DCHECK(!!bink);
    BINK_DCHECK(!!bink_track_);
  }
  BinkAudioTrack(BinkAudioTrack&& t) noexcept
      : bink_track_{std::move(t.bink_track_)} {
    t.bink_track_ = nullptr;
  }
  BinkAudioTrack& operator=(BinkAudioTrack&& t) noexcept {
    std::swap(bink_track_, t.bink_track_);
    return *this;
  }

  ~BinkAudioTrack() noexcept {
    // Close the Bink audio track.
    if (IsOpened()) ::BinkCloseTrack(bink_track_);
  }

  BINK_NO_COPY_CTOR_AND_ASSIGNMENT(BinkAudioTrack);

  /**
   * @brief Is track opened?
   * @return true or false.
   */
  [[nodiscard]] bool IsOpened() const noexcept {
    return bink_track_ != nullptr;
  }

  /**
   * @brief Get track info.
   * @param info Track info.
   * @return true if success, false otherwise.
   */
  [[nodiscard]] bool GetInfo(AudioTrackInfo& info) const noexcept {
    if (IsOpened()) {
      info.index = bink_track_->trackindex;
      info.frequency = bink_track_->Frequency;
      info.bits_per_sample = bink_track_->Bits;
      info.channels_count = bink_track_->Channels;
      info.max_size = bink_track_->MaxSize;

      return true;
    }

    return false;
  }

  /**
   * @brief Get track data.
   * @return Track data.
   */
  [[nodiscard]] std::vector<uint8_t> GetData() const noexcept {
    if (IsOpened()) {
      std::vector<uint8_t> data;
      data.resize(static_cast<size_t>(bink_track_->MaxSize));

      [[maybe_unused]] const uint32_t data_bytes_count{
          ::BinkGetTrackData(bink_track_, data.data())};
      BINK_DCHECK(static_cast<size_t>(data_bytes_count) == data.size());

      return data;
    }

    return {};
  }

 private:
  HBINKTRACK bink_track_;
};
};  // namespace bink

#endif  // !BINK_MP_BINK_AUDIO_TRACK_H_