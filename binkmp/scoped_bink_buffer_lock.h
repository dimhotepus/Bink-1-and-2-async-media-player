// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_SCOPED_BINK_BUFFER_LOCK_H_
#define BINK_MP_SCOPED_BINK_BUFFER_LOCK_H_

#include <cstddef>

#include "include/bink_base.h"
//
#include "deps/bink/bink.h"

namespace bink {

/**
 * @brief Scoped Bink buffer lock.
 */
class ScopedBinkBufferLock {
 public:
  /**
   * @brief Creates Bink buffer lock.
   * @param bink_buffer Buffer to lock.
   * @return void.
   */
  explicit ScopedBinkBufferLock(HBINKBUFFER bink_buffer) noexcept  //-V730
      : bink_buffer_{bink_buffer},
        is_locked_{::BinkBufferLock(bink_buffer) != 0} {}

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(ScopedBinkBufferLock);

  /*
   * Unlocks Bink buffer if it was locked.
   */
  ~ScopedBinkBufferLock() noexcept {
    if (is_locked()) {
      [[maybe_unused]] const int rc{::BinkBufferUnlock(bink_buffer_)};
      BINK_DCHECK(rc);
    }
  }

  /**
   * @brief Is internal Bink buffer locked?
   * @return true or false.
   */
  [[nodiscard]] bool is_locked() const noexcept { return is_locked_; }

 private:
  /**
   * @brief Native Bink buffer handle.
   */
  const HBINKBUFFER bink_buffer_;
  /**
   * @brief Is buffer locked or not?
   */
  const bool is_locked_;
  /**
   * @brief Explicit padding to see where your memory goes.
   */
  [[maybe_unused]] std::byte pad_[sizeof(char*) - sizeof(is_locked_)];
};

};  // namespace bink

#endif  // !BINK_MP_SCOPED_BINK_BUFFER_LOCK_H_