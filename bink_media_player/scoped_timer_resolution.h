// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.
//
// Set minimum resolution for periodic timers in scope.  Affects Sleep / Wait
// API precision, etc.

#ifndef BINK_MEDIA_PLAYER_SCOPED_TIMER_RESOLUTION_H_
#define BINK_MEDIA_PLAYER_SCOPED_TIMER_RESOLUTION_H_

#include <sal.h>          // _Check_return_
#include <specstrings.h>  // _Post_equals_last_error_

#include <chrono>
#include <cstddef>  // std::byte
#include <variant>

#include "binkmp/include/bink_base.h"

extern "C" __declspec(dllimport) _Return_type_success_(
    return == 0) unsigned __stdcall timeBeginPeriod(_In_ unsigned uPeriod);
extern "C" __declspec(dllimport) _Return_type_success_(
    return == 0) unsigned __stdcall timeEndPeriod(_In_ unsigned uPeriod);

namespace bink {

/**
 * @brief Changes minimum resolution for periodic timers and reverts back when
 * out of scope.
 *
 * "Prior to Windows 10, version 2004, this function affects a global Windows
 * setting.  For all processes Windows uses the lowest value (that is, highest
 * resolution) requested by any process.  Starting with Windows 10, version
 * 2004, this function no longer affects global timer resolution.  For processes
 * which call this function, Windows uses the lowest value (that is, highest
 * resolution) requested by any process.  For processes which have not called
 * this function, Windows does not guarantee a higher resolution than the
 * default system resolution.
 *
 * Starting with Windows 11, if a window-owning process becomes fully occluded,
 * minimized, or otherwise invisible or inaudible to the end user, Windows does
 * not guarantee a higher resolution than the default system resolution.  See
 * SetProcessInformation for more information on this behavior.
 *
 * Setting a higher resolution can improve the accuracy of time-out intervals in
 * wait functions.  However, it can also reduce overall system performance,
 * because the thread scheduler switches tasks more often.  High resolutions can
 * also prevent the CPU power management system from entering power-saving
 * modes.  Setting a higher resolution does not improve the accuracy of the
 * high-resolution performance counter."
 *
 * See
 * https://docs.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timebeginperiod
 */
class ScopedTimerResolution {
 public:
  /**
   * @brief ScopedTimerResolution creation result.
   */
  using NewResult = std::variant<ScopedTimerResolution, unsigned>;

  /**
   * @brief Changes minimum resolution for periodic timers.
   * @param resolution_ms Minimum timers resolution in
   * milliseconds to request.
   * @return ScopedTimerResolution.
   */
  [[nodiscard]] static NewResult New(
      _In_ std::chrono::milliseconds resolution_ms) {
    ScopedTimerResolution resolution{resolution_ms};
    return resolution.is_succeeded() ? NewResult{std::move(resolution)}
                                     : NewResult{resolution.error_code_};
  }

  ScopedTimerResolution(ScopedTimerResolution &&n) noexcept
      : resolution_ms_{std::move(n.resolution_ms_)},
        error_code_{std::move(n.error_code_)} {
    using namespace std::chrono_literals;

    n.resolution_ms_ = 0ms;
    n.error_code_ = 97;  // TIMERR_NOCANDO
  }
  ScopedTimerResolution &operator=(ScopedTimerResolution &&) noexcept = delete;

  /**
   * @brief Restores previous minimum timer resolution.
   */
  ~ScopedTimerResolution() noexcept {
    if (is_succeeded()) {
      // Resolution is not truncated before pass to timeEndPeriod.
      BINK_DCHECK(resolution_ms_.count() <=
                  static_cast<decltype(resolution_ms_)::rep>(
                      std::numeric_limits<unsigned>::max()));

      [[maybe_unused]] const bool is_ok{
          ::timeEndPeriod(static_cast<unsigned>(resolution_ms_.count())) == 0};
      BINK_DCHECK(is_ok);
    }
  }

 private:
  /**
   * @brief New minimum timer resolution in ms.
   */
  std::chrono::milliseconds resolution_ms_;
  /**
   * @brief Minimum timer resolution creation error_code.
   */
  unsigned error_code_;

#ifdef _WIN64
  std::byte pad_[sizeof(char *) - sizeof(error_code_)];  //-V730_NOINIT
#endif

  /**
   * @brief Changes minimum resolution for periodic timers.
   * @param resolution_ms Minimum timers resolution in
   * milliseconds to request.
   * @return nothing.
   */
  explicit ScopedTimerResolution(
      _In_ std::chrono::milliseconds resolution_ms) noexcept
      : resolution_ms_{resolution_ms},
        error_code_{
            ::timeBeginPeriod(static_cast<unsigned>(resolution_ms.count()))} {
    // Resolution is not truncated before pass to timeBeginPeriod.
    BINK_DCHECK(resolution_ms.count() <=
                static_cast<decltype(resolution_ms)::rep>(
                    std::numeric_limits<unsigned>::max()));
    BINK_DCHECK(is_succeeded());
  }

  /**
   * @brief Is set minimum timers resolution succeeded?
   * @return true or false.
   */
  [[nodiscard]] bool is_succeeded() const noexcept { return error_code_ == 0; }
};

}  // namespace bink

#endif  // !BINK_MEDIA_PLAYER_SCOPED_TIMER_RESOLUTION_H_
