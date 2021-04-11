/*
 * Project: xyz
 * Created Time: 2021/4/11 17:01:04
 * Author: Xyzhao
 * Brief: version
 * Copyright (c) 2018-2021 Xyzhao. All rights reserved.
 */

#include <string>
#include "xyz/version.h"

std::string xyz::get_xyz_version() {
  return std::string(" ~~ xyz ~~ \n\tVersion: ") + std::to_string(XYZ_VERSION_MAJOR) + "."
      + std::to_string(XYZ_VERSION_MINOR) + "." + std::to_string(XYZ_VERSION_PATCH)
      + std::string("\n\tGit hash: ") + std::string(XYZ_GIT_HASH);
}