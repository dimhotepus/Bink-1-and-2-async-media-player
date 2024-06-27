// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.
//
// Initializes COM in scope.

#ifndef BINK_MEDIA_PLAYER_SCOPED_COM_INITIALIZER_H_
#define BINK_MEDIA_PLAYER_SCOPED_COM_INITIALIZER_H_

#include <comdef.h>
#include <sal.h>

#include <cstddef>  // std::byte
#include <string>
#include <thread>
#include <type_traits>

#include "binkmp/include/bink_base.h"
#include "com_error_category.h"

using HRESULT = long;

_Check_return_ extern "C" __declspec(dllimport) HRESULT
    __stdcall CoInitializeEx(_In_opt_ void* pvReserved,
                             _In_ unsigned long dwCoInit);
extern "C" __declspec(dllimport) void __stdcall CoUninitialize(void);

namespace bink {

/**
 * @brief Enun concept.
 * @tparam TEnum Enum.
 */
template <typename TEnum>
concept Enum = std::is_enum_v<TEnum>;

/**
 * @brief Safely casts enum value to its underlying type.
 * @tparam TEnum Enum.
 * @param value Enum value.
 * @return Enum value with underlying enum type.
 */
template <Enum TEnum>
constexpr auto underlying_cast(TEnum value) noexcept {
  return static_cast<std::underlying_type_t<TEnum>>(value);
}

/**
 * @brief COM initilizer flags.
 */
enum class ScopedComInitializerFlags : unsigned long {
  /**
   * @brief Initializes the thread for apartment-threaded object concurrency.
   */
  kApartmentThreaded = 0x2UL,
  /**
   * @brief Initializes the thread for multithreaded object concurrency.
   */
  kMultiThreaded = 0x0UL,
  /**
   * @brief Disables DDE for OLE1 support.
   */
  kDisableOle1Dde = 0x4UL,
  /**
   * @brief Increase memory usage in an attempt to increase performance.
   */
  kSpeedOverMemory = 0x8UL
};

/**
 * @brief operator|.
 * @param left Left.
 * @param right Right.
 * @return Left | Right.
 */
[[nodiscard]] constexpr ScopedComInitializerFlags operator|(
    ScopedComInitializerFlags left, ScopedComInitializerFlags right) noexcept {
  return static_cast<ScopedComInitializerFlags>(underlying_cast(left) |
                                                underlying_cast(right));
}

/**
 * @brief Initializes Component Object Model at scope level.
 */
class ScopedComInitializer {
 public:
  /**
   * @brief Initializes COM with |coinit| flags for scope.
   * @param flags Flags.
   * @return ScopedComInitializer
   */
  static SystemResult<ScopedComInitializer> New(
      const ScopedComInitializerFlags flags) noexcept {
    auto init = ScopedComInitializer{flags};
    return !init.error_code()
               ? SystemResult<ScopedComInitializer>{std::move(init)}
               : SystemResult<ScopedComInitializer>{std::unexpect,
                                                    init.error_code()};
  }

  ScopedComInitializer(ScopedComInitializer&& i) noexcept
      : error_code_{std::move(i.error_code_)}
#ifndef NDEBUG
        ,
        thread_id_{i.thread_id_}
#endif
  {
    // Ensure no deinitialization occurs.
    i.error_code_ = std::error_code{EINVAL, std::generic_category()};
  }

  ScopedComInitializer& operator=(ScopedComInitializer&&) = delete;

  BINK_NO_COPY_CTOR_AND_ASSIGNMENT(ScopedComInitializer);

  /*
   * @brief Shut down COM.
   */
  ~ScopedComInitializer() noexcept {
#ifndef NDEBUG
    const std::thread::id this_thread_id{std::this_thread::get_id()};
    // COM should be freed on the same thread as it was initialized.
    BINK_DCHECK(this_thread_id == thread_id_);
#endif

    if (!error_code()) {
      ::CoUninitialize();
    }
  }

 private:
  /**
   * @brief Error code.
   */
  std::error_code error_code_;
#ifndef NDEBUG
  /**
   * @brief COM initializing thread id.
   */
  std::thread::id thread_id_;
  [[maybe_unused]] std::byte pad_[4];  //-V730_NOINIT
#endif

  /**
   * @brief Initializes COM with |coinit| flags for scope.
   * @param flags Flags.
   * @return nothing.
   */
  explicit ScopedComInitializer(const ScopedComInitializerFlags flags) noexcept
      : error_code_{GetComErrorCode(
            ::CoInitializeEx(nullptr, underlying_cast(flags)))}
#ifndef NDEBUG
        ,
        thread_id_{std::this_thread::get_id()}
#endif
  {
    BINK_DCHECK(!error_code());
  }

  /**
   * @brief Get COM initialization result.
   * @return Error code.
   */
  [[nodiscard]] std::error_code error_code() const noexcept {
    return error_code_;
  }
};

}  // namespace bink

#endif  // !BINK_MEDIA_PLAYER_SCOPED_COM_INITIALIZER_H_
