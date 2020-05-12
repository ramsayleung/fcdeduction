#ifndef UTIL_CONSTANT_H
#define UTIL_CONSTANT_H
#include <string>

#include "config.h"
namespace fcdeduction {
namespace util {
// 默认租户Id
inline const std::string TNT_INST_ID = "FINC0001";
// 测试租户Id
inline const std::string TEST_TNT_INST_ID = "TEST0001";
// 数据中心Id, 理应每个数据中心一个Id, 但预设只有一个数据中心
inline const int DATA_CENTER_ID = 25;
// 机器Id, 预设只有一台机器.
inline const int MACHINE_ID = 4;
inline const std::string getTntInstIdByEnv() {
  const std::string env = getEnvironmentVariableOrDefault("app_env", "prod");
  if (env == "prod") {
    return TNT_INST_ID;
  } else if (env == "test") {
    return TEST_TNT_INST_ID;
  } else {
    return TNT_INST_ID;
  }
}
}  // namespace util
}  // namespace fcdeduction
#endif