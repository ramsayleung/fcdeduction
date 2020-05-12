#ifndef DAL_BASE_DAO_H
#define DAL_BASE_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <memory>

#include "src/manager/database_manager.hpp"
#include "src/util/config.h"

namespace fcdeduction {
namespace dao {
class BaseDao {
 public:
  explicit BaseDao() {
    using namespace fcdeduction::util;
    fcdeduction::manager::DatabaseManager dbManager(
        getEnvironmentVariableOrDefault("mysql_host", "127.0.0.1"),
        getEnvironmentVariableOrDefault("mysql_database", "fcdeduction"),
        getEnvironmentVariableOrDefault("mysql_user", "root"),
        getEnvironmentVariableOrDefault("mysql_password", "password"));
    pconnection = dbManager.getConnection();
  }

 protected:
  std::shared_ptr<sqlpp::mysql::connection> pconnection;
};
}  // namespace dao
}  // namespace fcdeduction
#endif