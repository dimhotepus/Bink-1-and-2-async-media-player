// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_MSS_DIGITAL_DRIVER_H_
#define BINK_MP_MSS_DIGITAL_DRIVER_H_

#include <cstdint>

#include "include/bink_base.h"
#include "include/imss_digital_driver.h"
#include "mss_bootstrapper.h"
//
#include "deps/miles/include/mss.h"

namespace bink {

/**
 * @brief Miles sound sytem digital driver.
 */
class MssDigitalDriver : public IMssDigitalDriver {
 public:
  MssDigitalDriver(uint32_t frequency, int32_t bits_per_sample,
                   int32_t channels_count, uint32_t flags) noexcept
      : mss_bootstrapper_{},
        di_driver_{mss_bootstrapper_.IsBootstrapped()
                       ? ::AIL_open_digital_driver(frequency, bits_per_sample,
                                                   channels_count, flags)
                       : nullptr} {}

  ~MssDigitalDriver() noexcept {
    if (di_driver_) {
      ::AIL_close_digital_driver(di_driver_);
    }
  }

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(MssDigitalDriver);

  [[nodiscard]] HDIGDRIVER native_handle() const noexcept override {
    return di_driver_;
  }

  [[nodiscard]] bool IsOpened() const noexcept { return !!di_driver_; }

  [[nodiscard]] const char *GetLastError() const noexcept {
    return ::AIL_last_error();
  }

 private:
  const MssBootstrapper mss_bootstrapper_;
  const HDIGDRIVER di_driver_;
};

}  // namespace bink

#endif  // !BINK_MP_MSS_DIGITAL_DRIVER_H_