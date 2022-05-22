// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_INCLUDE_BINK_GENERAL_SETTINGS_H_
#define BINK_MP_INCLUDE_BINK_GENERAL_SETTINGS_H_

#include <cstdint>
#include <tuple>

#include "bink_base.h"

namespace bink {

/**
 * @brief Function that will allocate memory on Bink's behalf.
 * Returns the new pointer or nullptr or (void*)-1 if the allocation failed.
 * If the allocation fails, you can return nullptr and Bink will attempt to
 * allocate memory from the operating system, or you can return (void*)-1 and
 * Bink will simply fail the allocation.
 *
 * You must return 32-byte aligned memory pointers from this function!
 */
using BinkMalloc = void*(__stdcall*)(uint32_t bytes) noexcept;
/**
 * @brief Free memory allocated by a previous call to the BinkMalloc function.
 */
using BinkFree = void(__stdcall*)(void* ptr) noexcept;

/**
 * @brief Bink general settings.
 */
class BINK_ATTRIBUTE_API BinkGeneralSettings {
 public:
  /**
   * @brief Creates Bink general settings.
   * @return nothing.
   */
  BinkGeneralSettings() noexcept = default;

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(BinkGeneralSettings);

  /**
   * @brief Sets memory handlers for internal Bink routines.
   * @param bink_malloc Malloc.
   * @param bink_free Free.
   * @return void.
   */
  void SetMemoryHandlers(BinkMalloc bink_malloc, BinkFree bink_free) noexcept;

  /**
   * @brief Gets memory handlers.
   * @return tuple with malloc & free handlers.
   */
  std::tuple<BinkMalloc, BinkFree> GetMemoryHandlers() noexcept;

  /**
   * @brief Gets pointer to embedded Bink logo file.  This function returns the
   * address of the embedded Bink logo file.  The address returned from this
   * function can be passed directly to BinkOpen using the BINKFROMMEMORY flag.
   * This is a convenient way to access the Bink logo for credits display.
   * @return pointer to Bink logo.
   */
  void* GetBinkLogoAddress() noexcept;

  /**
   * @brief Overrides the Bink file's built-in frame rate.  This function allows
   * you to alter the playback speed of a Bink file at run-time.  If the Bink
   * file has audio, the sound will be sped-up or slowed-down to maintain
   * audio/video sync.  To use this function, you first make this call and then
   * you add the BINKFRAMERATE flag in your BinkOpen call.
   * @param frame_rate Along with FrameRateDiv, specifies the frame rate to use.
   * The frame rate is calculated as FrameRate/FrameRateDiv.  So, for example,
   * at 15 fps, FrameRate would be 15 and FrameRateDiv would be 1.
   * @param frame_rate_div Specifies the frame rate divisor.
   * @return void.
   */
  void SetFrameRate(uint32_t frame_rate, uint32_t frame_rate_div) noexcept;

 private:
  BinkMalloc bink_malloc_ = nullptr;
  BinkFree bink_free_ = nullptr;
};

};  // namespace bink

#endif  // !BINK_MP_INCLUDE_BINK_GENERAL_SETTINGS_H_