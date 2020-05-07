#ifndef DAL_ARRANGEMENT_DAO_H
#define DAL_ARRANGEMENT_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <memory>
#include <string>
namespace fcdeduction {
namespace dao {
class ArrangementDao {
 public:
  bool arExist(sqlpp::mysql::connection &connection,
               const std::string &tntInstId, const std::string &arNo);
};
}  // namespace dao
}  // namespace fcdeduction
#endif