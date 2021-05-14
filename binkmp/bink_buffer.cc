// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#include "bink_buffer.h"

#include <Windows.h>

namespace bink {
bool BinkBuffer::UpdateWindowPos() const noexcept {
#ifdef __RADWIN__
  // Size the window such that its client area exactly fits our Bink movie.
  return SetWindowPos(static_cast<HWND>(window_), nullptr, 0, 0,
                      static_cast<int>(bink_buffer_->WindowWidth),
                      static_cast<int>(bink_buffer_->WindowHeight),
                      SWP_NOMOVE) != 0;
#else
#error Please, define function to set window size exactly to size of Bink \
                    buffer on your platform.
#endif
}
}  // namespace bink