/*
 * Project: xyz
 * Created Time: 2021/3/16 15:10:03
 * Author: Xyzhao
 * Brief: log_test
 * Copyright (c) 2018-2021 Xyzhao. All rights reserved.
 */

// 在导入库前定义
// 默认情况下，Debug版本到DEBUG，RELEASE版本到INFO
#define XYZ_LOG_ACTIVE_LEVEL XYZ_LOG_LEVEL_ERROR
#include <xyz/log/log.hpp>
int main() {
  static int __xyz_log_init_flag__ = xyz::Log::instance().init();

  XYZ_LOG(XYZ_LOG_LEVEL::TRACE, "TEST", "XYZ_LOG_LEVEL_TRACE");
  XYZ_LOG(XYZ_LOG_LEVEL::DEBUG, "TEST", "XYZ_LOG_LEVEL_DEBUG");
  XYZ_LOG(XYZ_LOG_LEVEL::INFO, "TEST", "XYZ_LOG_LEVEL_INFO");
  XYZ_LOG(XYZ_LOG_LEVEL::WARN, "TEST", "XYZ_LOG_LEVEL_WARN");
  XYZ_LOG(XYZ_LOG_LEVEL::ERROR, "TEST", "XYZ_LOG_LEVEL_ERROR");
  XYZ_LOG(XYZ_LOG_LEVEL::CRITICAL, "TEST", "XYZ_LOG_LEVEL_CRITICAL");

  XYZ_LOG_TRACE("TEST", "XYZ_LOG_TRACE");
  XYZ_LOG_DEBUG("TEST", "XYZ_LOG_DEBUG");
  XYZ_LOG_INFO("TEST", "XYZ_LOG_INFO");
  XYZ_LOG_WARN("TEST", "XYZ_LOG_WARN");
  XYZ_LOG_ERROR("TEST", "XYZ_LOG_ERROR");
  XYZ_LOG_CRITICAL("TEST", "XYZ_LOG_CRITICAL");

  return 0;
}