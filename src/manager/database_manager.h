#ifndef DATEBASE_MANAGER_HPP
#define DATEBASE_MANAGER_HPP
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include "spdlog/spdlog.h"
namespace fcdeduction {
namespace manager {
class DatabaseManager {
 public:
  // 初始化时获取数据库连接, 每次初始化时新建一个连接.
  // TODO 更优的做法是使用连接池
  DatabaseManager(const std::string &host, const std::string &database,
                  const std::string &user, const std::string &password) {
    auto config = std::make_shared<sqlpp::mysql::connection_config>();
    config->database = database;
    config->host = host;
    config->password = password;
    config->user = user;
    try {
      this->connection =
          std::make_unique<sqlpp::mysql::connection>(std::move(config));
    } catch (const sqlpp::exception &e) {
      spdlog::error("初始化数据库失败, {0}", e.what());
      throw std::runtime_error("初始化数据库失败" + std::string(e.what()));
    }
  }
  // 获取数据库连接.
  std::unique_ptr<sqlpp::mysql::connection> getConnection();

 private:
  std::unique_ptr<sqlpp::mysql::connection> connection;
};
}  // namespace manager
}  // namespace fcdeduction
#endif