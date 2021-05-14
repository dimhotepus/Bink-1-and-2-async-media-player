// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#include "bink_general_settings.h"

#include "bink_base.h"
#include "deps/bink/bink.h"

namespace bink {
void BinkGeneralSettings::SetMemoryHandlers(BinkMalloc bink_malloc,
                                            BinkFree bink_free) noexcept {
  BINK_DCHECK(bink_malloc);
  bink_malloc_ = bink_malloc;
  BINK_DCHECK(bink_free);
  bink_free_ = bink_free;

  ::BinkSetMemory(bink_malloc_, bink_free_);
}

std::tuple<BinkMalloc, BinkFree>
BinkGeneralSettings::GetMemoryHandlers() noexcept {
  return {bink_malloc_, bink_free_};
}

void* BinkGeneralSettings::GetBinkLogoAddress() noexcept {
  return ::BinkLogoAddress();
}

void BinkGeneralSettings::SetFrameRate(uint32_t frame_rate,
                                       uint32_t frame_rate_div) noexcept {
  ::BinkSetFrameRate(frame_rate, frame_rate_div);
}
}  // namespace bink