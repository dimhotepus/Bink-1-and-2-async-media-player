// Copyright (c) 2021 The WhiteBox Authors.  All rights reserved.
// Use of this source code is governed by a 3-Clause BSD license that can be
// found in the LICENSE file.

#ifndef BINK_MP_INCLUDE_BINK_BASE_H_
#define BINK_MP_INCLUDE_BINK_BASE_H_

#include <cassert>
#include <memory>
#include <system_error>
#include <variant>

/*
 * Checks x is set in debug mode.
 */
#ifndef BINK_DCHECK
#define BINK_DCHECK(x) assert(x);
#endif  // BINK_DCHECK

/*
 * Disables copy constructor and assignment for className.
 */
#define BINK_NO_COPY_CTOR_AND_ASSIGNMENT(className) \
  className(className&) = delete;                   \
  className& operator=(className&)

/*
 * Disables move constructor and assignment for className.
 */
#define BINK_NO_MOVE_CTOR_AND_ASSIGNMENT(className) \
  className(className&&) = delete;                  \
  className& operator=(className&&)

/*
 * Disables copy & move constructors and assignment for className.
 */
#define BINK_NO_COPY_AND_MOVE_CTOR_AND_ASSIGNMENT(className) \
  BINK_NO_COPY_CTOR_AND_ASSIGNMENT(className);               \
  BINK_NO_MOVE_CTOR_AND_ASSIGNMENT(className)

namespace bink {

/**
 * @brief Bink media player create result.
 */
template <typename T>
using CreateResult = std::variant<std::unique_ptr<T>, const char*>;

/**
 * @brief Error code result.
 */
template <typename T>
using SystemResult = std::variant<T, std::error_code>;

}  // namespace bink

#ifdef _MSC_VER
/*
 * Defines no virtual table attribute.  Classes with such attribute will never
 * be instantiated on their own.  Using this form of __declspec can result in a
 * significant reduction in code size.
 */
#define BINK_ATTRIBUTE_NO_VTABLE __declspec(novtable)

#if defined(BINKMP_EXPORTS)
#define BINK_ATTRIBUTE_API __declspec(dllexport)
#else
#define BINK_ATTRIBUTE_API __declspec(dllimport)
#endif
#else
/*
 * Do nothing.
 */
#define BINK_ATTRIBUTE_NO_VTABLE
/*
 * Do nothing.
 */
#define BINK_ATTRIBUTE_API
#endif

#endif  // !BINK_MP_INCLUDE_BINK_BASE_H_