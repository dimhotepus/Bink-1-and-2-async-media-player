// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_BINK_BUFFER_H_
#define BINK_MP_BINK_BUFFER_H_

#include "deps/bink/bink.h"
#include "bink_base.h"

namespace bink {
/**
 * @brief Bink buffer.
 */
class BinkBuffer {
  friend class BinkMediaPlayer;

 public:
  /**
   * @brief Create bink buffer.
   * @param window Window handle abstraction.
   * @param width Window width.
   * @param height Window height.
   * @param buffer_flags Native Bink buffer flags.  See BINKBUFFERAUTO, etc.)
   * @return nothing.
   */
  BinkBuffer(void* window, unsigned int width, unsigned int height,
             unsigned int buffer_flags) noexcept
      : window_{window},
        bink_buffer_{BinkBufferOpen(window, width, height, buffer_flags)} {}

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(BinkBuffer);

  ~BinkBuffer() noexcept {
    // Close the Bink buffer.
    if (IsOpened()) BinkBufferClose(bink_buffer_);
  }

  /**
   * @brief Is buffer opened?
   * @return true or false.
   */
  [[nodiscard]] bool IsOpened() const noexcept {
    return bink_buffer_ != nullptr;
  }

  /**
   * @brief Get last global buffer error description.  It is especially handy if
   * BinkBufferOpen fails.
   * @return Last global buffer error description or nullptr if no error.
   */
  [[nodiscard]] const char* GetLastError() const noexcept {
    return BinkBufferGetError();
  }

  /**
   * @brief Copies the pixel data onto the screen from buffer.  This function
   * blits the pixel data onto the screen for the off-screen style BinkBuffers.
   * For overlay BinkBuffers, this function blits the color key pixels into your
   * window (this allows the overlay to appear on the screen).  For primary
   * surface BinkBuffers, this function simply returns without doing anything.
   * @param rects A pointer to an array of rectangular areas to copy.
   * @param num_rects Specifies the number rectangles pointed to by the rects
   * parameter.
   * @return void.
   */
  void Blit(BINKRECT* rects, unsigned int num_rects) const noexcept {
    BinkBufferBlit(bink_buffer_, rects, num_rects);
  }

 private:
  /**
   * @brief Window to blit buffer to.
  */
  void* window_;
  /**
   * @brief Native buffer handle.
  */
  const HBINKBUFFER bink_buffer_;

  /**
   * @brief Adjusts the specified window position coordinates for validity with
   * the current BinkBuffer type, because different blitting styles have
   * different constraints.
   * @param x X (left) coordinate that you want to check.
   * @param y Y (top) coordinate that you want to check.
   * @return void.
   */
  void AdjustWindowPos(int& x, int& y) const noexcept {
    BinkBufferCheckWinPos(bink_buffer_, &x, &y);
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
  bool SetWindowOffset(int x, int y) const noexcept {
    return BinkBufferSetOffset(bink_buffer_, x, y) != 0;
  }

  /**
   * @brief Updates window position to fit underlying buffer.
   * @return true on success, false on failure.
  */
  bool UpdateWindowPos() const noexcept;
};
};  // namespace bink

#endif  // !BINK_MP_BINK_BUFFER_H_