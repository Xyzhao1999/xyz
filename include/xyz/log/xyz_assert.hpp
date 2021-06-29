/*
 * Project: xyz
 * Created Time: 2021/6/29 11:56:06
 * Author: Xyzhao
 * Brief: xyz_assert
 * Copyright (c) 2018-2021 Xyzhao. All rights reserved.
 */

#ifndef XYZ_INCLUDE_XYZ_LOG_XYZ_ASSERT_HPP_
#define XYZ_INCLUDE_XYZ_LOG_XYZ_ASSERT_HPP_

#include <cassert>
#include "log.hpp"

#define XYZ_CHECK(expr) \
  do {                   \
    if(!static_cast <bool> (expr)) {XYZ_ERROR("ASSERT", "Assertion failed: %s",#expr); std::abort();} \
  } while(0)

#ifndef NDEBUG
#define XYZ_ASSERT(expr) XYZ_CHECK(expr)
#else
#define AC_ASSERT(expr) (__ASSERT_VOID_CAST (0))
#endif

#endif //XYZ_INCLUDE_XYZ_LOG_XYZ_ASSERT_HPP_
