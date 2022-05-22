// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.
//
// Scoped show cursor.

#ifndef BINK_MEDIA_PLAYER_SCOPED_SHOW_CURSOR_H_
#define BINK_MEDIA_PLAYER_SCOPED_SHOW_CURSOR_H_

#include <comdef.h>

#include <string>
#include <system_error>

#include "binkmp/include/bink_base.h"

using HRESULT = long;

namespace bink {

/**
 * @brief Show or hide cursor in scope.
 */
class ScopedShowCursor {
 public:
  /**
   * @brief Creates scoped cursor.
   * @param should_show Show cursor or not?
   */
  explicit ScopedShowCursor(bool should_show) noexcept
      : should_show_{should_show} {
    ::ShowCursor(should_show ? TRUE : FALSE);
  }

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(ScopedShowCursor);

  ~ScopedShowCursor() noexcept { ::ShowCursor(should_show_ ? FALSE : TRUE); }

 private:
  const bool should_show_;
};

}  // namespace bink

#endif  // !BINK_MEDIA_PLAYER_SCOPED_SHOW_CURSOR_H_
