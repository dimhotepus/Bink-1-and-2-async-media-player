// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_MSS_BOOTSTRAPPER_H_
#define BINK_MP_MSS_BOOTSTRAPPER_H_

#include "include/bink_base.h"
//
#include "deps/miles/include/mss.h"

namespace bink {

/**
 * @brief Miles sound system bootstrapper.
 */
class MssBootstrapper {
 public:
  /**
   * @brief Creates Miles sound system bootstrapper.
   * @return nothing.
   */
  MssBootstrapper() noexcept : is_bootstrapped_{::AIL_startup() != 0} {}

  ~MssBootstrapper() noexcept { ::AIL_shutdown(); }

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(MssBootstrapper);

  /**
   * @brief Is bootsrapper succeeded?
   * @return true if it is, false otherwise.
   */
  [[nodiscard]] bool IsBootstrapped() const noexcept {
    return is_bootstrapped_;
  }

 private:
  const bool is_bootstrapped_;
};

}  // namespace bink

#endif  // !BINK_MP_MSS_BOOTSTRAPPER_H_