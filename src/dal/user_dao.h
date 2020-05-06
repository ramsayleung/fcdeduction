#ifndef DAL_USER_DAO_H
#define DAL_USER_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <string>
namespace fcdeduction {
namespace dao {
class UserDao {
   public:
    bool userExist(const std::string &userId, const std::string tntInstId);
};
}  // namespace dao
}  // namespace fcdeduction
#endif