
set(SPDLOG_GIT_URL "https://github.com/gabime/spdlog.git" CACHE STRING "spdlog git url")
set(SPDLOG_GIT_TAG v1.8.5)

add_git_external_party(spdlog ${SPDLOG_GIT_URL} ${SPDLOG_GIT_TAG})

# set config for log
option(XYZ_LOG_CONSOLE "print log to console" ON)
if (ANDROID)
  option(XYZ_LOG_ANDROID "print log using android log system" ON)
endif ()
option(XYZ_LOG_FILE "print log to file" OFF)
if (XYZ_LOG_FILE)
  set(XYZ_LOG_FILENAME "/tmp/log/xyz.log" CACHE STRING "Path to save log file.")
  set(XYZ_LOG_FILESIZE "10485760" CACHE STRING "Size for each log file.")
  set(XYZ_LOG_FILE_NUM "5" CACHE STRING "Number of log files.")
endif ()


configure_file(
    "${XYZ_ROOT_DIR}/cmake/log_config.h.in"
    "${XYZ_ROOT_DIR}/include/xyz/log/config.h"
)

set(XYZ_LOG_SRCS
    ${XYZ_ROOT_DIR}/src/log/log.cpp
    ${XYZ_ROOT_DIR}/include/xyz/log/log.hpp
    ${XYZ_ROOT_DIR}/include/xyz/log/config.h
    )

#include_directories(spdlog::spdlog)

add_library(xyz_log STATIC ${XYZ_LOG_SRCS})

#target_include_directories(log PRIVATE
#    "$<BUILD_INTERFACE:${XYZ_ROOT_DIR}/include>"
#    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDE_DIR}>"
#    )
target_link_libraries(xyz_log PUBLIC spdlog::spdlog)

add_library(xyz::log ALIAS xyz_log)
