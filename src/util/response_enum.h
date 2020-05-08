#ifndef UTIL_RESPONSE_ENUM_H
#define UTIL_RESPONSE_ENUM_H
#include <string>
namespace fcdeduction {
namespace util {

// 模拟Java的enum
class ResponseEnum {
 public:
  // 成功
  static const ResponseEnum SUCCESS;
  // 用户不存在
  static const ResponseEnum USER_NOT_EXIST;
  // 用户账号密码错误
  static const ResponseEnum INCORRECT_LOGIN_VALUE;
  // 用户未登录
  static const ResponseEnum USER_NOT_LOGIN;
  // 产品不存在
  static const ResponseEnum PRODUCT_NOT_EXIST;
  // 合约不存在
  static const ResponseEnum ARRANGEMENT_NOT_EXIST;
  // 重复开通扣费服务
  static const ResponseEnum PRODUCT_DUPLICATE_BIND;
  // 用户未开通指定扣费服务
  static const ResponseEnum PRODUCT_NOT_BIND;
  const std::string getStatus();
  const std::string getCode();
  const std::string getDesc();

 private:
  // 状态, SUCCESS, FAILED, UNKNOWN
  const std::string status;
  // 状态码, 如00, 01
  const std::string code;
  // 描述
  const std::string desc;

  ResponseEnum(const std::string &_status, const std::string &_code,
               const std::string &_desc)
      : status(_status), code(_code), desc(_desc) {}
};
}  // namespace util
}  // namespace fcdeduction
#endif