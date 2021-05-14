// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_IMSS_DIGITAL_DRIVER_FACTORY_H_
#define BINK_MP_IMSS_DIGITAL_DRIVER_FACTORY_H_

#include <cstdint>
#include <memory>

#include "bink_base.h"
#include "deps/miles/include/mss.h"
#include "imss_digital_driver.h"

namespace bink {
/**
 * @brief Miles digital driver settings.
 */
struct MssDigitalDriverSettings {
  /**
   * @brief Frequency.
   */
  uint32_t frequency;
  /**
   * @brief Bits per sample.
   */
  int32_t bits_per_sample;
  /**
   * @brief Channels count.
   */
  int32_t channels_count;
  /**
   * @brief Native driver flags.
   */
  uint32_t flags;
};

/**
 * @brief Miles sound system driver factory.
 */
class BINK_ATTRIBUTE_API MssDigitalDriverFactory {
 public:
  /**
   * @brief Creates Miles sound system driver.
   * @param settings Miles sound system driver settings.
   * @return Either Miles sound system driver or error description.
   */
  static CreateResult<IMssDigitalDriver> Create(
      const MssDigitalDriverSettings &settings);

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(MssDigitalDriverFactory);

 private:
  MssDigitalDriverFactory() = delete;
};
}  // namespace bink

#endif  // !BINK_MP_IMSS_DIGITAL_DRIVER_FACTORY_H_