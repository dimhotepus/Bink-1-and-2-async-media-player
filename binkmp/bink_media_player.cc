// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#include "bink_media_player.h"

#include <algorithm>

#include "bink_buffer.h"
#include "include/bink_base.h"
#include "include/bink_media_player_settings.h"
#include "include/ibink_media_player.h"
#include "scoped_bink_buffer_lock.h"
//
#include "deps/bink/bink.h"

namespace bink {

BinkMediaPlayer::BinkMediaPlayer(  //-V730
    const BinkMediaPlayerSettings& settings) noexcept
    : bink_{::BinkOpen(settings.media_path, settings.bink_flags)},
      bink_audio_controls_{bink_},
      bink_buffer_{settings.window, bink_ ? bink_->Width : 0,
                   bink_ ? bink_->Height : 0, settings.buffer_flags},
      y_plane_decode_frame_tid{0u},
      cr_cb_alpha_planes_and_sound_tid{0u},
      used_cpus_count_{0},
      is_async_ok_{Setup(std::clamp(settings.used_cpus_count, 1ui8, 8ui8))} {
  if (is_async_ok_) {
    // Start the first frame in the background immediately.
    is_async_ok_ = DecodeFrame();
  }
}

BinkMediaPlayer::~BinkMediaPlayer() noexcept {
  Shutdown();

  if (bink_ != nullptr) ::BinkClose(bink_);
}

bool BinkMediaPlayer::CanPresent() const noexcept {
  return ::BinkWait(bink_) == 0;
}

void BinkMediaPlayer::Present(bool do_present_old_frame) const noexcept {
  if (!do_present_old_frame) {
    // Decompress the Bink frame.
    // Is the previous frame done yet (wait for a bit), note that this
    // logic assumes you already have a frame decompressing the first
    // time this function is called.
    if (DecodeFrameWait(kAsyncDecompressionWaitMks)) {
      // We have finished a frame. Keep playing the movie.
      NextFrame();

      // Do we need to skip a frame?
      if (::BinkShouldSkip(bink_)) {
        if (DecodeFrame()) DecodeFrameWait(-1);

        // Are we at the end of the movie?  Nope, advance to the next frame.
        if (HasFrames()) NextFrame();
      }

      // Start decompressing the next frame.
      if (HasFrames()) DecodeFrame();

      // Copy current frame to buffer.
      if (Frame2Buffer()) {
        // Tell the BinkBuffer to blit the pixels onto the screen (if the
        // BinkBuffer is using an off-screen blitting style).
        Blit2Buffer(bink_->FrameRects,
                    static_cast<unsigned>(::BinkGetRects(
                        bink_, bink_buffer_.bink_buffer_->SurfaceType)));
      }
    }

    return;
  }

  // Tell the BinkBuffer to blit the pixels of old frame onto the screen (if the
  // BinkBuffer is using an off-screen blitting style).
  Blit2Buffer(nullptr, 1U);
}

bool BinkMediaPlayer::Play() const noexcept {
  return ::BinkPause(bink_, 0) == 0;
}

bool BinkMediaPlayer::Pause() const noexcept {
  return ::BinkPause(bink_, 1) != 0;
}

bool BinkMediaPlayer::ToggleVideo(bool on) const noexcept {
  return ::BinkSetVideoOnOff(bink_, on ? 1 : 0) != 0;
}

void BinkMediaPlayer::GetRealtimeStatistics(
    unsigned last_frames_count_to_stats,
    BinkRealtimeStatistics& realtime_statistics) const noexcept {
  static_assert(sizeof(BINKREALTIME) == sizeof(BinkRealtimeStatistics));
  static_assert(alignof(BINKREALTIME*) == alignof(BinkRealtimeStatistics*));
  ::BinkGetRealtime(bink_,
                    reinterpret_cast<BINKREALTIME*>(
                        reinterpret_cast<void*>(&realtime_statistics)),
                    last_frames_count_to_stats);
}

void BinkMediaPlayer::GetSummaryStatistics(
    BinkSummaryStatistics& summary_statistics) const noexcept {
  static_assert(sizeof(BINKSUMMARY) == sizeof(BinkSummaryStatistics));
  static_assert(alignof(BINKSUMMARY*) == alignof(BinkSummaryStatistics*));
  ::BinkGetSummary(bink_, reinterpret_cast<BINKSUMMARY*>(
                              reinterpret_cast<void*>(&summary_statistics)));
}

const char* BinkMediaPlayer::GetLastError() const noexcept {
  const char* error{::BinkGetError()};
  return error ? error : bink_buffer_.GetLastError();
}

bool BinkMediaPlayer::DecodeFrame() const noexcept {
  // Bink decompresses the compressed Bink frame into the three internal YUV
  // memory buffers in this function (like BinkDoFrame) only in the
  // background.
  return ::BinkDoFrameAsync(bink_, GetYPlaneDecodeFrameThreadIdx(),
                            GetcRcBAlphaPlanesAndSoundDecodeFrameThreadIdx()) !=
         0;
}

bool BinkMediaPlayer::DecodeFrameWait(
    int wait_for_decompression_mcs) const noexcept {
  return ::BinkDoFrameAsyncWait(bink_, wait_for_decompression_mcs) != 0;
}

// Note that if the video is falling behind the audio, then this function may
// return without copying any pixels.  If the copy is skipped, then this
// function will return a false.  If copy was successful, then a true
// will be returned.
bool BinkMediaPlayer::Frame2Buffer() const noexcept {
  HBINKBUFFER buffer{bink_buffer_.bink_buffer_};
  // Lock the BinkBuffer so that we can copy the decompressed frame into it.
  ScopedBinkBufferLock lock{buffer};

  // Copy the decompressed frame into the BinkBuffer (this might be
  // on-screen).
  return lock.is_locked() &&
         ::BinkCopyToBuffer(bink_, buffer->Buffer, buffer->BufferPitch,
                            buffer->Height, 0, 0, buffer->SurfaceType) == 0;
}

void BinkMediaPlayer::NextFrame() const noexcept { ::BinkNextFrame(bink_); }

void BinkMediaPlayer::Blit2Buffer(BINKRECT* rects,
                                  unsigned int rects_num) const noexcept {
  bink_buffer_.Blit(rects, rects_num);
}

[[nodiscard]] std::tuple<unsigned, unsigned> BinkMediaPlayer::FindClosestScale(
    unsigned expected_width, unsigned expected_height) const noexcept {
  // Integral scaling is much faster, so always scale the video as such.
  unsigned new_width{bink_->Width}, new_height{bink_->Height};

  // Find if we need to scale up or down.
  if (new_width < expected_width && new_height < expected_height) {
    // Scaling up by powers of two
    unsigned scale{0};

    while ((new_width << (scale + 1)) <= expected_width &&
           (new_height << (scale + 1)) <= expected_height)
      scale++;

    return {new_width << scale, new_height << scale};
  }

  if (new_width > expected_width && new_height > expected_height) {
    // Scaling down by powers of two.
    unsigned scale{0};

    while ((new_width >> scale) > expected_width &&
           (new_height >> scale) > expected_height)
      scale++;

    return {new_width >> scale, new_height >> scale};
  }

  return {new_width, new_height};
}

}  // namespace bink