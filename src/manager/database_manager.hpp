#ifndef DATEBASE_MANAGER_HPP
#define DATEBASE_MANAGER_HPP
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <iostream>
#include <memory>
#include <string>
namespace fcdeduction {
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&... args) {
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
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
    this->connection =
        fcdeduction::make_unique<sqlpp::mysql::connection>(std::move(config));
  }
  // 获取数据库连接.
  std::unique_ptr<sqlpp::mysql::connection> getConnection();

 private:
  std::unique_ptr<sqlpp::mysql::connection> connection;
};
}  // namespace manager
}  // namespace fcdeduction
#endif