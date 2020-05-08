#ifndef UTIL_REL_STATUS_ENUM_H
#define UTIL_REL_STATUS_ENUM_H
namespace fcdeduction {
namespace util {
enum class RelStatusEnum : char {
  ACTIVE = '1',
  SUSPEND = '2',
  FREEZE = '3',
};
}
}  // namespace fcdeduction

#endif