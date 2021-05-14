// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_BINK_MP_H_
#define BINK_MP_BINK_MP_H_

#include <cstddef>

#include "bink_audio_controls.h"
#include "bink_base.h"
#include "bink_buffer.h"
#include "bink_media_player_settings.h"
#include "deps/bink/bink.h"
#include "ibink_media_player.h"

namespace bink {
/**
 * @brief Bink media player.
 */
class BinkMediaPlayer : public IBinkMediaPlayer {
 public:
  /**
   * @brief Creates Bink media player.
   * @param settings Player settings.
   * @return nothing.
   */
  explicit BinkMediaPlayer(const BinkMediaPlayerSettings& settings) noexcept;

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(BinkMediaPlayer);

  virtual ~BinkMediaPlayer() noexcept;

  /**
   * @brief Is media file opened successfully?
   * @return true or false.
   */
  bool IsOpened() const noexcept override {
    return IsBinkOpened() && is_async_ok_;
  }

  /**
   * @brief Has player frames to play?
   * @return true if has, false if not.
   */
  bool HasFrames() const noexcept override {
    return bink_->FrameNum != bink_->Frames;
  }

  /**
   * @brief Is player finished frame decoding and can present it?
   * @return true if it is, false if not.
   */
  bool CanPresent() const noexcept override;

  /**
   * @brief Draw frame.
   * @param do_present_old_frame Should previous frame be presented or new one?
   * Handy ex. for WM_PAINT handling.
   * @return void.
   */
  void Present(bool do_present_old_frame) const noexcept override;

  /**
   * @brief Begin play media.
   * @return true if success, false if error.
   */
  bool Play() const noexcept override;

  /**
   * @brief Pauses playing media.
   * @return true if success, false if error.
   */
  bool Pause() const noexcept override;

  /**
   * @brief Toggles video on or off.
   * @param on Should enable video?
   * @return Whether the video is currently on (true) or off (false).
   */
  bool ToggleVideo(bool on) const noexcept override;

  /**
   * @brief Gets audio controls for Bink media.
   * @return Audio controls.
   */
  const IBinkAudioControls& GetAudioControls() const noexcept override {
    return bink_audio_controls_;
  }

  /**
   * @brief Gets realtime statistics about playback.
   * @param last_frames_count_to_stats Frame window length to return the
   * realtime information for (in frames).
   * @param realtime_statistics Statistics.
   * @return void
   */
  void GetRealtimeStatistics(
      unsigned last_frames_count_to_stats,
      BinkRealtimeStatistics& realtime_statistics) const noexcept override;

  /**
   * @brief Gets summary statistics about playback.
   * @param summary_statistics Statistics.
   * @return void.
   */
  void GetSummaryStatistics(
      BinkSummaryStatistics& summary_statistics) const noexcept override;

  /**
   * @brief Adjusts the specified window position coordinates for validity with
   * the current BinkBuffer type, because different blitting styles have
   * different constraints.
   * @param x X (left) coordinate that you want to check.
   * @param y Y (top) coordinate that you want to check.
   * @return void.
   */
  void AdjustWindowPos(int& x, int& y) const noexcept override {
    bink_buffer_.AdjustWindowPos(x, y);
  }

  /**
   * @brief Tells the BinkBuffer that either the window position on the desktop
   * or that the playback offset within the window has changed.
   * @param x X (left) coordinate (relative to the upper-left of the window)
   * that you want to blit to.
   * @param y Y (top) coordinate (relative to the upper-left of the window) that
   * you want to blit to.
   * @return Whether the BinkBuffer was successfully repositioned (true) or
   * whether the specified coordinates were invalid (false).
   */
  bool SetWindowOffset(int x, int y) const noexcept override {
    return bink_buffer_.SetWindowOffset(x, y);
  }

  /**
   * @brief Updates window position to fit underlying buffer.
   * @return true on success, false on failure.
   */
  [[nodiscard]] bool UpdateWindowPos() const noexcept {
    return bink_buffer_.UpdateWindowPos();
  }

  /**
   * @brief Returns a string that describes the last global Bink error.
   * @return string if error, nullptr if not.
   */
  [[nodiscard]] const char* GetLastError() const noexcept;

 private:
  /**
   * @brief Bink handle.
   */
  const HBINK bink_;
  /**
   * @brief Bink audio controls.
   */
  const BinkAudioControls bink_audio_controls_;
  /**
   * @brief Bink buffer.
   */
  const BinkBuffer bink_buffer_;
  /**
   * @brief Thread id of Y plane decoding thread.
   */
  mutable unsigned int y_plane_decode_frame_tid;
  /**
   * @brief Thread id of cR, cB, cAlpha planes decoding thread.
   */
  mutable unsigned int cr_cb_alpha_planes_and_sound_tid;
  /**
   * @brief Used for decoding cpu cores count.
   */
  unsigned char used_cpus_count_;
  /**
   * @brief Is asyn decoding initialization / shutdown succeeded?
   */
  bool is_async_ok_;
  /**
   * @brief Explicit padding to see where your memory goes.
   */
  [[maybe_unused]] std::byte
      pad_[sizeof(char*) - sizeof(used_cpus_count_) - sizeof(is_async_ok_)];
  /**
   * @brief How much time in microseconds to wait for async decompression to
   * proceed.
   */
  static constexpr int kAsyncDecompressionWaitMks{500};

  /**
   * @brief Setup async decoding threads.
   * @param used_cpus_count How many cpu cores to use for async decoding.
   * @return true if success, false if failure.
   */
  bool Setup(unsigned char used_cpus_count) noexcept {
    for (unsigned int i{0}; i < used_cpus_count; ++i) {
      // This function starts up a background thread that you can use with
      // the BinkDoFrameAsync function.  On Windows, thread_index can be a
      // value from 0 to 7 and is one of 8 threads.  These threads run at
      // normal priority and are not pegged to any specific CPU.  The
      // async_parameter value is ignored on Windows.
      const int async_errno{BinkStartAsyncThread(static_cast<int>(i), nullptr)};
      if (!async_errno) return false;

      ++used_cpus_count_;
    }

    return true;
  }

  /**
   * @brief Shutdown async decoder threads.
   * @return void.
   */
  void Shutdown() noexcept {
    for (unsigned int i{used_cpus_count_}; i > 0; --i) {
      is_async_ok_ = !!BinkRequestStopAsyncThread(static_cast<int>(i) - 1);
      if (is_async_ok_) {
        is_async_ok_ = !!BinkWaitStopAsyncThread(static_cast<int>(i) - 1);
      }

      BINK_DCHECK(is_async_ok_);
    }
  }

  /**
   * @brief Is bink opened?
   * @return true if it is, false if not.
   */
  bool IsBinkOpened() const noexcept {
    return bink_ != nullptr && bink_buffer_.IsOpened();
  }

  /**
   * @brief Runs background frame decoding.
   * @return true if success, false otherwise.
   */
  bool DecodeFrame() const noexcept;

  /**
   * @brief Wait for background frame decompression to complete.
   * @param wait_for_decompression_mcs How much time in microseconds to give
   * decoder to proceeed before checking completition status of decompression
   * operation.
   * @return true if decompression complete, false otherwise.
   */
  bool DecodeFrameWait(int wait_for_decompression_mcs) const noexcept;

  // Specifies the thread index that the Y plane should be decompressed on.  In
  // Bink, most of the decompression time is spent decompressing the Y plane, so
  // the work can be split between two threads - one for the Y plane
  // decompression and one for "everything else" (the cR, cB and alpha plane and
  // the audio decompression).
  unsigned int GetYPlaneDecodeFrameThreadIdx() const noexcept {
    // return used_cpus_count_ <= 2u ? 0u : 1u;
    return y_plane_decode_frame_tid++ % used_cpus_count_;
  }

  // Specifies the thread index that the cR, cB, and alpha planes should be
  // decompressed on (and the sound).
  unsigned int GetcRcBAlphaPlanesAndSoundDecodeFrameThreadIdx() const noexcept {
    // return used_cpus_count_ > 0 ? used_cpus_count_ - 1 : 0;
    return --cr_cb_alpha_planes_and_sound_tid % used_cpus_count_;
  }

  // Note that if the video is falling behind the audio, then this function may
  // return without copying any pixels.  If the copy is skipped, then this
  // function will return a false.  If copy was successful, then a true
  // will be returned.
  bool Frame2Buffer() const noexcept;

  /**
   * @brief Advances Bink to media next frame.
   * @return void.
   */
  void NextFrame() const noexcept;

  /**
   * @brief Tell the BinkBuffer to blit the pixels onto the screen (if the
  // BinkBuffer is using an off-screen blitting style).
   * @return void.
  */
  void Blit2Buffer() const noexcept;
};
}  // namespace bink

#endif  // !BINK_MP_BINK_MP_H_