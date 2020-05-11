#include "ar_code_enum.h"
using namespace fcdeduction::util;
const std::string& ArCodeEnum::getArNo() const { return arNo; }
const std::string& ArCodeEnum::getArType() const { return arType; }
const std::map<std::string, std::string> ArCodeEnum::enumMap() {
  std::map<std::string, std::string> enums;
  enums[DEDUCTION_AR.getArType()] = enums[DEDUCTION_AR.getArNo()];
  return enums;
}
const ArCodeEnum ArCodeEnum::DEDUCTION_AR =
    ArCodeEnum("DEDUCTION", "457176612421775381");