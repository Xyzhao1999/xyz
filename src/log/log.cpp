/*
 * Project: xyz
 * Created Time: 2021/4/11 15:40:04
 * Author: Xyzhao
 * Brief: log
 * Copyright (c) 2018-2021 Xyzhao. All rights reserved.
 */



#include <iostream>
#include <memory>


#include <spdlog/spdlog.h>
#include <spdlog/pattern_formatter.h>
#include <spdlog/fmt/bundled/printf.h>

#include "xyz/log/log.hpp"

#if defined(XYZ_LOG_CONSOLE)
#include <spdlog/sinks/stdout_color_sinks.h>
#endif

#if defined(XYZ_LOG_FILE)
#include <spdlog/sinks/rotating_file_sink.h>
#endif

#if defined(__ANDROID__) && defined(XYZ_LOG_ANDROID)
#include <spdlog/sinks/android_sink.h>
#endif

xyz::Log &xyz::Log::instance() {
  static xyz::Log log;
  return log;
}

std::unique_ptr<spdlog::logger> &xyz::Log::logger() {
  return logger_;
}

int xyz::Log::init() {
  if (logger_ != nullptr) {
    std::cout << "Log is initialized !" << std::endl;
    return -1;
  }

  try {
    std::vector<spdlog::sink_ptr> log_sinks;

#if defined(XYZ_LOG_CONSOLE)
    {
      std::string console_log_format = "%^[%Y/%m/%d %T.%e][%t][%L][%s,%!:%#]%v%$";
      auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
      console_sink->set_level(spdlog::level::trace);
      console_sink->set_pattern(console_log_format);
      log_sinks.push_back(console_sink);
    }
#endif

#if defined(__ANDROID__) && defined(XYZ_LOG_ANDROID)
    {
        std::string android_log_format = "[%s,%!:%#]%v";
        auto android_sink = std::make_shared<spdlog::sinks::android_sink_mt>(" Log");
        android_sink->set_level(spdlog::level::trace);
        android_sink->set_pattern(android_log_format);
        log_sinks.push_back(android_sink);
      }
#endif

#if defined(XYZ_LOG_FILE)
    {
#if !defined(XYZ_LOG_FILENAME)
#define XYZ_LOG_FILENAME "/tmp/log/xyz.log"
#endif

#if !defined(XYZ_LOG_FILESIZE)
#define XYZ_LOG_FILESIZE 10485760
#endif

#if !defined(XYZ_LOG_FILE_NUM)
#define XYZ_LOG_FILE_NUM 5
#endif
        std::string file_log_format = "[%Y/%m/%d %T.%e][%t][%L][%s,%!:%#]%v";
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            XYZ_LOG_FILENAME, XYZ_LOG_FILESIZE, XYZ_LOG_FILE_NUM);
        file_sink->set_level(spdlog::level::trace);
        file_sink->set_pattern(file_log_format);
        log_sinks.push_back(file_sink);
      }
#endif

    if (!log_sinks.empty()) {
      logger_ = spdlog::details::make_unique<spdlog::logger>("Log", log_sinks.begin(), log_sinks.end());
      logger_->set_level(spdlog::level::trace);
      logger_->flush_on(spdlog::level::warn);
      spdlog::flush_every(std::chrono::seconds(3));
    } else {
      std::cout << "Log log sink is empty!" << std::endl;
      return -2;
    }
  } catch (const spdlog::spdlog_ex &ex) {
    std::cout << "Log initialization failed: " << ex.what() << std::endl;
    return -3;
  }
  return 0;
}

void xyz::_log_printf(int level_enum, const char *tag,
                      spdlog::source_loc loc, const std::string &str) noexcept {
  auto logger = &xyz::Log::instance().logger();
  if (level_enum >= XYZ_LOG_ACTIVE_LEVEL && level_enum < XYZ_LOG_LEVEL::OFF &&
      (*logger) && (*logger)->should_log(static_cast<spdlog::level::level_enum>(level_enum))) {
    (*logger)->log(loc, static_cast<spdlog::level::level_enum>(level_enum), "[{:^.8s}]: {}", tag, str);
  }
}