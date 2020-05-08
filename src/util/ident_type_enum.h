#ifndef UTIL_IDENT_TYPE_ENUM_H
#define UTIL_IDENT_TYPE_ENUM_H
#include <string>
namespace fcdeduction {
namespace util {
enum class IdentTypeEnum : char {
  PASSWORD = '1',
  SECURITY_QUESTION = '2',
  FACE_RECOGNITION = '3'
};
inline std::string enumToString(IdentTypeEnum identType) {
  switch (identType) {
    case IdentTypeEnum::PASSWORD:
      return "1";
    case IdentTypeEnum::SECURITY_QUESTION:
      return "2";
    case IdentTypeEnum::FACE_RECOGNITION:
      return "3";
    default:
      throw std::invalid_argument("Invalid ident type value");
      break;
  }
}
}  // namespace util
}  // namespace fcdeduction
#endif