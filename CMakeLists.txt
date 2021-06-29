cmake_minimum_required(VERSION 3.11)

# Check *nix
if (NOT UNIX)
  message(FATAL_ERROR "This CMakeList only support in UNIX platform now.")
endif (NOT UNIX)

set(XYZ_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

include(cmake/utils.cmake)
# Version
set(XYZ_VERSION_MAJOR 0)
set(XYZ_VERSION_MINOR 0)
set(XYZ_VERSION_PATCH 1)
set(XYZ_VERSION "${XYZ_VERSION_MAJOR}.${XYZ_VERSION_MINOR}.${XYZ_VERSION_PATCH}")

project(xyz VERSION ${XYZ_VERSION} LANGUAGES CXX)
find_package(Threads REQUIRED)

set(XYZ_GIT_HASH "unknown")
get_git_hash(XYZ_GIT_HASH)

message(STATUS " ~~ Using xyz ~~ ")
message(STATUS "xyz version: ${XYZ_VERSION}")
message(STATUS "xyz git hash: ${XYZ_GIT_HASH}")

configure_file(
    "${XYZ_ROOT_DIR}/cmake/version.h.in"
    "${XYZ_ROOT_DIR}/include/xyz/version.h"
)

include(GNUInstallDirs)

# Common compile option
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif ()

if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif ()


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -fnon-call-exceptions -fPIE -fomit-frame-pointer -fvisibility=hidden")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -fnon-call-exceptions -fPIE -fomit-frame-pointer -fvisibility=hidden")

set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler='-Wall -Wextra'")
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} --default-stream per-thread")

if (CMAKE_BUILD_TYPE MATCHES "Debug")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g3 -Og")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Og")
elseif (CMAKE_BUILD_TYPE MATCHES "Release")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3 -DNDEBUG")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")

  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstrict-aliasing -ffunction-sections -fdata-sections -ffast-math")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstrict-aliasing -ffunction-sections -fdata-sections -ffast-math")# -fno-rtti -fno-exceptions ")

  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility-inlines-hidden")

  set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -Xcompiler='-O3 -DNDEBUG'")

  if (ANDROID)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pie -fPIE -s")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--gc-sections")
  endif ()
endif ()


include_directories(include)

add_subdirectory(src)

# test
option(XYZ_BUILD_TEST "build for test" ON)
if (XYZ_BUILD_TEST)
  add_subdirectory(test)
endif ()
