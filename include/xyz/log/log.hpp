/*
 * Project: xyz
 * Created Time: 2021/4/11 15:40:04
 * Author: Xyzhao
 * Brief: log
 * Copyright (c) 2018-2021 Xyzhao. All rights reserved.
 */

#ifndef INCLUDE_XYZ_LOG_LOG_HPP_
#define INCLUDE_XYZ_LOG_LOG_HPP_

#include <spdlog/logger.h>
#include <spdlog/fmt/bundled/printf.h>

#include "xyz/log/config.h"

#if !defined(XYZ_LOG_ACTIVE_LEVEL)
#if defined(NDEBUG)
#define XYZ_LOG_ACTIVE_LEVEL XYZ_LOG_LEVEL_INFO
#else
#define XYZ_LOG_ACTIVE_LEVEL XYZ_LOG_LEVEL_DEBUG
#endif // defined(NDEBUG)
#endif // !defined(XYZ_LOG_ACTIVE_LEVEL)

#define XYZ_LOG_LEVEL_TRACE 0
#define XYZ_LOG_LEVEL_DEBUG 1
#define XYZ_LOG_LEVEL_INFO 2
#define XYZ_LOG_LEVEL_WARN 3
#define XYZ_LOG_LEVEL_ERROR 4
#define XYZ_LOG_LEVEL_CRITICAL 5
#define XYZ_LOG_LEVEL_OFF 6

enum XYZ_LOG_LEVEL {
  TRACE = XYZ_LOG_LEVEL_TRACE,
  DEBUG = XYZ_LOG_LEVEL_DEBUG,
  INFO = XYZ_LOG_LEVEL_INFO,
  WARN = XYZ_LOG_LEVEL_WARN,
  ERROR = XYZ_LOG_LEVEL_ERROR,
  CRITICAL = XYZ_LOG_LEVEL_CRITICAL,
  OFF = XYZ_LOG_LEVEL_OFF,
  XYZ_LOG_LEVEL_NUMBER
};

namespace xyz {

class Log {
 public:
  static Log &instance();

  std::unique_ptr<spdlog::logger> &logger();

  Log(const Log &) = delete;

  Log &operator=(const Log &) = delete;

  int init();

 private:
  std::unique_ptr<spdlog::logger> logger_ = nullptr;

  Log() = default;

  ~Log() = default;

};

void _log_printf(int level_enum, const char *tag, spdlog::source_loc loc, const std::string &str) noexcept;

} // namespace xyz



#define XYZ_LOG_PRINTF(Level, tag, format, ...) \
  xyz::_log_printf(Level, tag, spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, fmt::sprintf(format, ##__VA_ARGS__))

#define XYZ_LOG(Level, tag, format, ...) XYZ_LOG_PRINTF(Level, tag, format, ##__VA_ARGS__)

#if XYZ_LOG_ACTIVE_LEVEL <= XYZ_LOG_LEVEL_TRACE
#define XYZ_LOG_TRACE(tag, format, ...) XYZ_LOG_PRINTF(XYZ_LOG_LEVEL::TRACE, tag, format, ##__VA_ARGS__)
#else
#define XYZ_LOG_TRACE(tag, format, ...) (void)0
#endif

#if XYZ_LOG_ACTIVE_LEVEL <= XYZ_LOG_LEVEL_DEBUG
#define XYZ_LOG_DEBUG(tag, format, ...) XYZ_LOG_PRINTF(XYZ_LOG_LEVEL::DEBUG, tag, format, ##__VA_ARGS__)
#else
#define XYZ_LOG_DEBUG(tag, format, ...) (void)0
#endif

#if XYZ_LOG_ACTIVE_LEVEL <= XYZ_LOG_LEVEL_INFO
#define XYZ_LOG_INFO(tag, format, ...) XYZ_LOG_PRINTF(XYZ_LOG_LEVEL::INFO, tag, format, ##__VA_ARGS__)
#else
#define XYZ_LOG_INFO(tag, format, ...) (void)0
#endif

#if XYZ_LOG_ACTIVE_LEVEL <= XYZ_LOG_LEVEL_WARN
#define XYZ_LOG_WARN(tag, format, ...) XYZ_LOG(XYZ_LOG_LEVEL::WARN, tag, format, ##__VA_ARGS__)
#else
#define XYZ_LOG_WARN(tag, format, ...) (void)0
#endif

#if XYZ_LOG_ACTIVE_LEVEL <= XYZ_LOG_LEVEL_ERROR
#define XYZ_LOG_ERROR(tag, format, ...) XYZ_LOG_PRINTF(XYZ_LOG_LEVEL::ERROR, tag, format, ##__VA_ARGS__)
#else
#define XYZ_LOG_ERROR(tag, format, ...) (void)0
#endif

#if XYZ_LOG_ACTIVE_LEVEL <= XYZ_LOG_LEVEL_CRITICAL
#define XYZ_LOG_CRITICAL(tag, format, ...) XYZ_LOG_PRINTF(XYZ_LOG_LEVEL::CRITICAL, tag, format, ##__VA_ARGS__)
#else
#define XYZ_LOG_CRITICAL(tag, format, ...) (void)0
#endif

#endif //INCLUDE_XYZ_LOG_LOG_HPP_
