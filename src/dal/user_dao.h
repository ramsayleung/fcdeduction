#ifndef DAL_USER_DAO_H
#define DAL_USER_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <memory>
#include <string>
namespace fcdeduction {
namespace dao {
class UserDao {
 public:
  bool userExist(sqlpp::mysql::connection &connection,
                 const std::string &tntInstId, const std::string &userId);
};
}  // namespace dao
}  // namespace fcdeduction
#endif