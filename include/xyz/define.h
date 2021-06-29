/*
 * Project: xyz
 * Created Time: 2021/6/29 11:32:06
 * Author: Xyzhao
 * Brief: define
 * Copyright (c) 2018-2021 Xyzhao. All rights reserved.
 */

#ifndef XYZ_INCLUDE_XYZ_DEFINE_H_
#define XYZ_INCLUDE_XYZ_DEFINE_H_

#include <cstdint>

#ifndef int32
typedef int32_t int32;
#endif
#ifndef uint32
typedef uint32_t uint32;
#endif
#ifndef int64
typedef int64_t int64;
#endif
#ifndef uint64
typedef uint64_t uint64;
#endif

// Disable the copy and assignment operator for a class.
#define XYZ_DISABLE_CLASS_COPY_AND_ASSIGN(classname) \
 private:                                  \
  classname(const classname &);            \
  classname &operator=(const classname &)

// Instantiate a class with float and double specifications.
#define XYZ_INSTANTIATE_TEMPLATE_CLASS(classname)   \
  char gInstantiationGuard##classname; \
  template class classname<float>;     \
  template class classname<int>;       \
  template class classname<uint8_t>

#endif //XYZ_INCLUDE_XYZ_DEFINE_H_
