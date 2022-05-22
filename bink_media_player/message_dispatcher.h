// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.
//
// Bink media player host.

#ifndef BINK_MEDIA_PLAYER_MESSAGE_DISPATCHER_H_
#define BINK_MEDIA_PLAYER_MESSAGE_DISPATCHER_H_

#include <Windows.h>

#include <type_traits>

#include "binkmp/include/bink_base.h"

namespace bink {

/**
 * @brief OnIdle concept.
 * @tparam F function.
 */
template <typename F>
concept OnIdle = std::is_invocable_r_v<void, F>;

/**
 * @brief Message dispatcher.
 * @tparam IdleFunction
 */
template <OnIdle IdleFunction>
class MessageDispatcher {
 public:
  /**
   * @brief ctor.
   * @param window Window.
   * @param on_idle Idle function.
   */
  MessageDispatcher(_In_opt_ HWND window, _In_ IdleFunction on_idle) noexcept
      : window_{window}, on_idle_{on_idle} {}

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(MessageDispatcher);

  /**
   * @brief Dispatches message for window.
   * @return true if continue dispatching, false otherwise.
   */
  [[nodiscard]] bool Dispatch() const noexcept {
    MSG msg;

    if (::PeekMessage(&msg, window_, 0, 0, PM_NOREMOVE)) {
      const BOOL rc{::GetMessage(&msg, window_, 0, 0)};

      if (rc == -1 || msg.message == WM_QUIT) [[unlikely]] {
        return false;
      }

      ::TranslateMessage(&msg);
      ::DispatchMessage(&msg);
    } else {
      on_idle_();
    }

    return true;
  }

 private:
  const HWND window_;
  const IdleFunction on_idle_;
};

}  // namespace bink

#endif  // BINK_MEDIA_PLAYER_MESSAGE_DISPATCHER_H_