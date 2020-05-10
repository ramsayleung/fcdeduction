#include "response_enum.h"
using namespace fcdeduction::util;
const std::string& ResponseEnum::getStatus() const { return status; }
const std::string& ResponseEnum::getCode() const { return code; }
const std::string& ResponseEnum::getDesc() const { return desc; }
const std::string getCode();
const std::string getDesc();
const ResponseEnum ResponseEnum::SUCCESS = ResponseEnum("SUCCESS", "00", "");
const ResponseEnum ResponseEnum::USER_NOT_EXIST =
    ResponseEnum("FAILED", "01", "用户不存在");
const ResponseEnum ResponseEnum::INCORRECT_LOGIN_VALUE =
    ResponseEnum("FAILED", "02", "用户账号密码错误");
const ResponseEnum ResponseEnum::USER_NOT_LOGIN =
    ResponseEnum("FAILED", "03", "用户未登录");
const ResponseEnum ResponseEnum::PRODUCT_NOT_EXIST =
    ResponseEnum("FAILED", "14", "产品不存在");
const ResponseEnum ResponseEnum::ARRANGEMENT_NOT_EXIST =
    ResponseEnum("FAILED", "15", "合约不存在");
const ResponseEnum ResponseEnum::PRODUCT_DUPLICATE_BIND =
    ResponseEnum("FAILED", "16", "重复开通扣费服务");
const ResponseEnum ResponseEnum::PRODUCT_NOT_BIND =
    ResponseEnum("FAILED", "17", "用户未开通指定扣费服务");