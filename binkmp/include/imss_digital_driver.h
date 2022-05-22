// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_INCLUDE_IMSS_DIGITAL_DRIVER_H_
#define BINK_MP_INCLUDE_IMSS_DIGITAL_DRIVER_H_

#include "bink_base.h"

using HDIGDRIVER = struct _DIG_DRIVER*;

namespace bink {

/**
 * @brief Miles sound system digital driver.
 */
struct BINK_ATTRIBUTE_NO_VTABLE IMssDigitalDriver {
  virtual ~IMssDigitalDriver() noexcept = 0;

  [[nodiscard]] virtual HDIGDRIVER native_handle() const noexcept = 0;
};

}  // namespace bink

#endif  // !BINK_MP_INCLUDE_IMSS_DIGITAL_DRIVER_H_