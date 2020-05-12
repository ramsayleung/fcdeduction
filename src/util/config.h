#ifndef UTIL_CONFIG_H
#define UTIL_CONFIG_H
#include <string>
namespace fcdeduction {
namespace util {
inline std::string getEnvironmentVariableOrDefault(const std::string& variable_name,
                                            const std::string& default_value) {
  const char* value = getenv(variable_name.c_str());
  return value ? value : default_value;
}
}  // namespace util
}  // namespace fcdeduction
#endif