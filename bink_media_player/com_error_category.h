// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.
//
// COM error category.

#ifndef BINK_MEDIA_PLAYER_COM_ERROR_CATEGORY_H_
#define BINK_MEDIA_PLAYER_COM_ERROR_CATEGORY_H_

#include <comdef.h>

#include <string>
#include <system_error>

#include "binkmp/include/bink_base.h"

using HRESULT = long;

namespace bink {

/**
 * @brief Convert wide string to ansi.
 * @param in Ansi string.
 * @return Wide string.
 */
[[nodiscard]] inline std::string WideToAnsi(const std::wstring& in) {
  const std::size_t in_size{in.size() + 1};
  std::string ansi(in_size, '\0');

  [[maybe_unused]] const std::error_code rc{
      ::wcstombs_s(nullptr, &ansi[0], in_size, in.data(), in_size),
      std::generic_category()};
  // Only debug as invalid CRT parameter handler expected to terminate app.
  BINK_DCHECK(!rc);

  ansi.resize(in_size - 1);

  return ansi;
}

/**
 * @brief Component Object Model error category.
 */
class ComErrorCategory : public std::error_category {
 public:
  ComErrorCategory() noexcept = default;

  /**
   * @brief Error category name.
   * @return Category name.
   */
  [[nodiscard]] const char* name() const noexcept override { return "com"; }

  /**
   * @brief Gets error value HRESULT description.
   * @param error_value HRESULT.
   * @return Error description.
   */
  [[nodiscard]] std::string message(int error_value) const override {
    const _com_error com_error{static_cast<HRESULT>(error_value)};
#ifdef _UNICODE
    return WideToAnsi(com_error.ErrorMessage());
#else
    return std::string{com_error.ErrorMessage()};
#endif
  }

  BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(ComErrorCategory);
};

/**
 * @brief Gets COM error category singleton.
 * @return COM error category singleton.
 */
[[nodiscard]] inline ComErrorCategory& com_error_category() {
  static ComErrorCategory com_error_category;
  return com_error_category;
}

/**
 * @brief Get COM error code.
 * @param rc Native system COM error code.
 * @return System COM error code.
 */
[[nodiscard]] inline std::error_code GetComErrorCode(
    const HRESULT result) noexcept {
  return std::error_code{result, com_error_category()};
}

}  // namespace bink

#endif  // !BINK_MEDIA_PLAYER_COM_ERROR_CATEGORY_H_
