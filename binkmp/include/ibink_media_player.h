// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_INCLUDE_IBINK_MEDIA_PLAYER_H_
#define BINK_MP_INCLUDE_IBINK_MEDIA_PLAYER_H_

#include "bink_base.h"
#include "ibink_audio_controls.h"

namespace bink {

/**
 * @brief Bink media info.
 */
struct BinkMediaInfo {
  /**
   * @brief Height.
   */
  unsigned height;
  /**
   * @brief Width.
   */
  unsigned width;
  /**
   * @brief Window height.
   */
  unsigned window_height;
  /**
   * @brief Window width.
   */
  unsigned window_width;
};

/**
 * @brief Bink realtime playback statistics.
 */
struct BinkRealtimeStatistics {
  unsigned FrameNum;               // Current frame number
  unsigned FrameRate;              // Frame rate
  unsigned FrameRateDiv;           // Frame rate divisor
  unsigned Frames;                 // Frames in this sample period
  unsigned FramesTime;             // Time is ms for these frames
  unsigned FramesVideoDecompTime;  // Time decompressing these frames
  unsigned FramesAudioDecompTime;  // Time decompressing these frames
  unsigned FramesReadTime;         // Time reading these frames
  unsigned FramesIdleReadTime;     // Time reading these frames at idle
  unsigned FramesThreadReadTime;   // Time reading these frames in background
  unsigned FramesBlitTime;         // Time blitting these frames
  unsigned ReadBufferSize;         // Size of read buffer
  unsigned ReadBufferUsed;         // Amount of read buffer currently used
  unsigned FramesDataRate;         // Data rate for these frames
};

/**
 * @brief Bink summary playback statistics.
 */
struct BinkSummaryStatistics {
  unsigned Width;                 // Width of frames
  unsigned Height;                // Height of frames
  unsigned TotalTime;             // Total time (ms)
  unsigned FileFrameRate;         // Frame rate
  unsigned FileFrameRateDiv;      // Frame rate divisor
  unsigned FrameRate;             // Frame rate
  unsigned FrameRateDiv;          // Frame rate divisor
  unsigned TotalOpenTime;         // Time to open and prepare for decompression
  unsigned TotalFrames;           // Total Frames
  unsigned TotalPlayedFrames;     // Total Frames played
  unsigned SkippedFrames;         // Total number of skipped frames
  unsigned SkippedBlits;          // Total number of skipped blits
  unsigned SoundSkips;            // Total number of sound skips
  unsigned TotalBlitTime;         // Total time spent blitting
  unsigned TotalReadTime;         // Total time spent reading
  unsigned TotalVideoDecompTime;  // Total time spent decompressing video
  unsigned TotalAudioDecompTime;  // Total time spent decompressing audio
  unsigned TotalIdleReadTime;     // Total time spent reading while idle
  unsigned TotalBackReadTime;     // Total time spent reading in background
  unsigned TotalReadSpeed;        // Total io speed (bytes/second)
  unsigned SlowestFrameTime;      // Slowest single frame time (ms)
  unsigned Slowest2FrameTime;     // Second slowest single frame time (ms)
  unsigned SlowestFrameNum;       // Slowest single frame number
  unsigned Slowest2FrameNum;      // Second slowest single frame number
  unsigned AverageDataRate;       // Average data rate of the movie
  unsigned AverageFrameSize;      // Average size of the frame
  unsigned HighestMemAmount;      // Highest amount of memory allocated
  unsigned TotalIOMemory;         // Total extra memory allocated
  unsigned HighestIOUsed;         // Highest extra memory actually used
  unsigned Highest1SecRate;       // Highest 1 second rate
  unsigned Highest1SecFrame;      // Highest 1 second start frame
};

/**
 * @brief Bink media player.
 */
struct BINK_ATTRIBUTE_NO_VTABLE IBinkMediaPlayer {
  virtual ~IBinkMediaPlayer() noexcept = 0;

  /**
   * @brief Is media file opened successfully?
   * @return true or false.
   */
  [[nodiscard]] virtual bool IsOpened() const noexcept = 0;

  /**
   * @brief Has player frames to play?
   * @return true if has, false if not.
   */
  [[nodiscard]] virtual bool HasFrames() const noexcept = 0;

  /**
   * @brief Is player finished frame decoding and can present it?
   * @return true if it is, false if not.
   */
  [[nodiscard]] virtual bool CanPresent() const noexcept = 0;

  /**
   * @brief Draw frame.
   * @param do_present_old_frame Should previous frame be presented or new one?
   * Handy ex. for WM_PAINT handling.
   * @return void.
   */
  virtual void Present(bool do_present_old_frame) const noexcept = 0;

  /**
   * @brief Begin play media.
   * @return true if success, false if error.
   */
  virtual bool Play() const noexcept = 0;

  /**
   * @brief Pauses playing media.
   * @return true if success, false if error.
   */
  virtual bool Pause() const noexcept = 0;

  /**
   * @brief Toggles video on or off.
   * @param on Should enable video?
   * @return Whether the video is currently on (true) or off (false).
   */
  virtual bool ToggleVideo(bool on) const noexcept = 0;

  /**
   * @brief Get bink media info.
   * @return true if success, false if error.
   */
  [[nodiscard]] virtual bool GetMediaInfo(
      BinkMediaInfo& media_info) const noexcept = 0;

  /**
   * @brief Gets audio controls for Bink media.
   * @return Audio controls.
   */
  [[nodiscard]] virtual const IBinkAudioControls& GetAudioControls()
      const noexcept = 0;

  /**
   * @brief Gets realtime statistics about playback.
   * @return void.
   */
  virtual void GetRealtimeStatistics(
      unsigned last_frames_count_to_stats,
      BinkRealtimeStatistics& realtime_statistics) const noexcept = 0;

  /**
   * @brief Gets summary statistics about playback.
   * @param summary_statistics Statistics.
   * @return void.
   */
  virtual void GetSummaryStatistics(
      BinkSummaryStatistics& summary_statistics) const noexcept = 0;

  /**
   * @brief Adjusts the specified window position coordinates for validity with
   * the current BinkBuffer type, because different blitting styles have
   * different constraints.
   * @param x X (left) coordinate that you want to check.
   * @param y Y (top) coordinate that you want to check.
   * @return void.
   */
  virtual void AdjustWindowPos(int& x, int& y) const noexcept = 0;

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
  virtual bool SetWindowOffset(int x, int y) const noexcept = 0;

  /**
   * @brief This function sets a new shrink/stretch scale to use.  Not all of
   * the blitting styles can do shrinking or stretching, so be sure to specify
   * one of the BINKBUFFERSTRETCHX, BINKBUFFERSTRETCHY, BINKBUFFERSHRINKX, or
   * BINKBUFFERSHRINKY constants when you open the BinkBuffer, or your scale
   * factor may be ignored.
   * @param width New width.
   * @param height New height.
   * @return true on success, false on failure.
   */
  virtual bool SetWindowScale(unsigned width,
                              unsigned height) const noexcept = 0;
};

}  // namespace bink

#endif  // !BINK_MP_INCLUDE_IBINK_MEDIA_PLAYER_H_