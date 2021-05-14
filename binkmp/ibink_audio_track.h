// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_IBINK_AUDIO_TRACK_H_
#define BINK_MP_IBINK_AUDIO_TRACK_H_

#include <algorithm>
#include <cstdint>
#include <vector>

#include "bink_base.h"
#include "deps/bink/bink.h"

namespace bink {
/**
 * @brief Audio track id.
 */
struct AudioTrackId {
  /**
   * @brief Specifies the track id.
   */
  uint32_t id;
};

/**
 * @brief Audio track info.
 */
struct AudioTrackInfo {
  int32_t index;
  uint32_t frequency;
  uint32_t bits_per_sample;
  uint32_t channels_count;
  uint32_t max_size;
};

/**
 * @brief Bink audio track.
 */
struct BINK_ATTRIBUTE_NO_VTABLE IBinkAudioTrack {
  virtual ~IBinkAudioTrack() = 0;

  /**
   * @brief Is track opened?
   * @return true or false.
   */
  [[nodiscard]] virtual bool IsOpened() const noexcept = 0;

  /**
   * @brief Get track info.
   * @param info Track info.
   * @return true if success, false otherwise.
   */
  [[nodiscard]] virtual bool GetInfo(AudioTrackInfo& info) const noexcept = 0;

  /**
   * @brief Get track data.
   * @return Track data.
   */
  [[nodiscard]] virtual std::vector<uint8_t> GetData() const noexcept = 0;
};
}  // namespace bink

#endif  // !BINK_MP_IBINK_AUDIO_TRACK_H_