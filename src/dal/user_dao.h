#ifndef DAL_USER_DAO_H
#define DAL_USER_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <optional>
#include <string>

#include "user.h"
#include "user_do.h"
namespace fcdeduction {
namespace dao {
class UserDao {
 public:
  // 通过userId查询, 判断用户是否存在
  bool userExist(sqlpp::mysql::connection &connection,
                 const std::string &tntInstId, const std::string &userId);
  // 通过userId查询用户, 为空则返回 std::nullopt
  std::optional<fcdeduction::dataobject::User> selectByUserId(
      sqlpp::mysql::connection &connection, const std::string &tntInstId,
      const std::string &userId);
};
}  // namespace dao
}  // namespace fcdeduction
#endif