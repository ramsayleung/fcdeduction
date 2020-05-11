#ifndef UTIL_AR_CODE_ENUM_H
#define UTIL_AR_CODE_ENUM_H
#include <map>
#include <string>
namespace fcdeduction {
namespace util {
class ArCodeEnum {
 public:
  // 扣费合约
  static const ArCodeEnum DEDUCTION_AR;

  const std::string &getArType() const;
  const std::string &getArNo() const;
  static const std::map<std::string, std::string> enumMap();

 private:
  // 合约类型
  const std::string arType;
  // 合约号
  const std::string arNo;
  ArCodeEnum(const std::string &_arType, const std::string &_arNo)
      : arType(_arType), arNo(_arNo) {}
};
}  // namespace util
}  // namespace fcdeduction
#endif