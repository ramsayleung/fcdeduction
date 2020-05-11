#ifndef UTIL_ARG_PARSE_H
#define UTIL_ARG_PARSE_H
#include <algorithm>

namespace fcdeduction {
namespace util {
const char* getCmdOption(const char** begin, const char** end,
                         const std::string& option) {
  const char** itr = std::find(begin, end, option);
  if (itr != end && ++itr != end) {
    return *itr;
  }
  return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option) {
  return std::find(begin, end, option) != end;
}

}  // namespace util
}  // namespace fcdeduction
#endif