#ifndef DAL_USER_DAO_H
#define DAL_USER_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <optional>
#include <string>

#include "base_dao.h"
#include "user.h"
#include "user_do.h"
namespace fcdeduction {
namespace dao {
class UserDao : public fcdeduction::dao::BaseDao {
 public:
  using BaseDao::BaseDao;
  // 通过userId查询, 判断用户是否存在
  bool userExist(const std::string &tntInstId, const std::string &userId);

  // 通过userId查询用户, 为空则返回 std::nullopt
  std::optional<fcdeduction::dataobject::User> selectByUserId(
      const std::string &tntInstId, const std::string &userId);
  // 新增用户记录
  void insertUser(fcdeduction::dataobject::User &user);
  // 通过主键用户Id删除用户
  void deleteUser(const std::string &tntInstId, const std::string &userId);
};
}  // namespace dao
}  // namespace fcdeduction
#endif