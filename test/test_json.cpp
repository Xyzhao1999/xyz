/*
 * Project: xyz
 * Created Time: 2021/3/16 15:10:03
 * Author: Xyzhao
 * Brief: log_test
 * Copyright (c) 2018-2021 Xyzhao. All rights reserved.
 */

// 在导入库前定义
// 默认情况下，Debug版本到DEBUG，RELEASE版本到INFO
#define XYZ_LOG_ACTIVE_LEVEL XYZ_LOG_LEVEL_TRACE
#include <xyz/xyz.h>

int main() {
  std::string json_string = R"({"happy": true, "pi": 3.141})";

  airia::json test_json = airia::json::parse(json_string);

  XYZ_INFO("json", "%lf", double(test_json["pi"]));

  return 0;
}