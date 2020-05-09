#ifndef DAL_ARRANGEMENT_DAO_H
#define DAL_ARRANGEMENT_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <optional>
#include <string>

#include "arrangement.h"
#include "arrangement_do.h"
namespace fcdeduction {
namespace dao {
class ArrangementDao {
 public:
 // 通过合约号判断合约是否存在.
  bool arExist(sqlpp::mysql::connection &connection,
               const std::string &tntInstId, const std::string &arNo);
 // 通过合约号查询合约信息, 为空则返回 std::nullopt.
  std::optional<fcdeduction::dataobject::Arrangement> selectByArNo(
      sqlpp::mysql::connection &connection, const std::string &tntInstId,
      const std::string &arNo);
};
}  // namespace dao
}  // namespace fcdeduction
#endif