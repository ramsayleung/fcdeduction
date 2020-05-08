#ifndef DAL_IDENTIFICATION_H
#define DAL_IDENTIFICATION_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include "src/util/ident_type_enum.h"
namespace fcdeduction {
namespace dao {
class IdentificationDao {
 public:
  // 判断用户对应的识别key与识别value是否正确
  bool identMatch(sqlpp::mysql::connection &connection,
                  const std::string &tntInstId, const std::string &userId,
                  const std::string &identKey, const std::string &identValue,
                  const fcdeduction::util::IdentTypeEnum &identType);
};
}  // namespace dao
}  // namespace fcdeduction
#endif