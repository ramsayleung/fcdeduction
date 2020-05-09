#ifndef DAL_BASE_DAO_H
#define DAL_BASE_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <memory>

#include "src/manager/database_manager.hpp"

namespace fcdeduction {
namespace dao {
class BaseDao {
 public:
  explicit BaseDao() {
    fcdeduction::manager::DatabaseManager dbManager(
        getenv("mysql_host"), getenv("mysql_database"), getenv("mysql_user"),
        getenv("mysql_password"));
    pconnection = dbManager.getConnection();
  }

 protected:
  std::shared_ptr<sqlpp::mysql::connection> pconnection;
};
}  // namespace dao
}  // namespace fcdeduction
#endif