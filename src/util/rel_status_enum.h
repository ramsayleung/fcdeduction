#ifndef UTIL_REL_STATUS_ENUM_H
#define UTIL_REL_STATUS_ENUM_H
namespace fcdeduction {
namespace util {
enum class RelStatusEnum : char {
  ACTIVE = '1',
  SUSPEND = '2',
  FREEZE = '3',
};
inline std::string enumToString(RelStatusEnum status) {
  switch (status) {
    case RelStatusEnum::ACTIVE:
      return "1";
    case RelStatusEnum::SUSPEND:
      return "2";
    case RelStatusEnum::FREEZE:
      return "3";
    default:
      throw std::invalid_argument("Invalid rel status value");
      break;
  }
}
}  // namespace util
}  // namespace fcdeduction

#endif