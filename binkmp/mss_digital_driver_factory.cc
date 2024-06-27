// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#include "include/mss_digital_driver_factory.h"

#include "mss_digital_driver.h"

namespace bink {

CreateResult<IMssDigitalDriver> MssDigitalDriverFactory::Create(
    MssDigitalDriverSettings settings) {
  auto driver = std::make_unique<MssDigitalDriver>(
      settings.frequency, settings.bits_per_sample, settings.channels_count,
      settings.flags);
  return driver->IsOpened() ? CreateResult<IMssDigitalDriver>{std::move(driver)}
                            : CreateResult<IMssDigitalDriver>{
                                  std::unexpect, driver->GetLastError()};
}

}  // namespace bink