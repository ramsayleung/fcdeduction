#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/user.h"
#include "src/manager/database_manager.hpp"
#include "src/util/config.h"

namespace mysql = sqlpp::mysql;
model::DeUser deuser = {};
void testDelete(mysql::connection& connection) {
  connection(sqlpp::remove_from(deuser).where(deuser.userId == "05686723" and
                                              deuser.tntInstId == "00000001"));
}

void testSelectByCondition(mysql::connection& connection) {
  const auto& user = connection(sqlpp::select(all_of(deuser))
                                    .from(deuser)
                                    .where(deuser.userId == "05686723" and
                                           deuser.tntInstId == "00000001"))
                         .front();
  EXPECT_EQ(user.userName, "TestInsert");
  EXPECT_EQ(user.userId, "05686723");
}

void testInsert(mysql::connection& connection) {
  // 在插入前先删除可能存在的数据
  testDelete(connection);
  connection(sqlpp::insert_into(deuser).set(
      deuser.userId = "05686723", deuser.tntInstId = "00000001",
      deuser.userName = "TestInsert", deuser.userType = "1",
      deuser.gmtCreate = std::chrono::system_clock::now(),
      deuser.gmtModified = std::chrono::system_clock::now()));
  // 确保插入成功
  testSelectByCondition(connection);
  // 然后再删掉, 保证下次插入成功
  testDelete(connection);
}

void testSelect(mysql::connection& connection) {
  for (const auto& row : connection(
           sqlpp::select(all_of(deuser)).from(deuser).unconditionally())) {
    std::cerr << "row.name: " << row.userName << ", row.id: " << row.userId
              << std::endl;
  };
}

TEST(DATABASEMANAGERTEST, MAINTEST) {
  using namespace fcdeduction::util;
  fcdeduction::manager::DatabaseManager dbManager(
      getEnvironmentVariableOrDefault("mysql_host", "127.0.0.1"),
      getEnvironmentVariableOrDefault("mysql_database", "fcdeduction"),
      getEnvironmentVariableOrDefault("mysql_user", "root"),
      getEnvironmentVariableOrDefault("mysql_password", "password"));
  auto connection = dbManager.getConnection();
  testSelect(*connection);
  testInsert(*connection);
  testSelect(*connection);
}
TEST(SQLPP11TEST, MAINTEST) {
  using namespace fcdeduction::util;
  auto config = std::make_shared<mysql::connection_config>();
  config->host = getEnvironmentVariableOrDefault("mysql_host", "127.0.0.1");
  config->user = getEnvironmentVariableOrDefault("mysql_user", "root");
  config->database =
      getEnvironmentVariableOrDefault("mysql_database", "fcdeduction");
  config->password =
      getEnvironmentVariableOrDefault("mysql_password", "password");
  config->debug = true;
  try {
    mysql::connection connection(config);
    testSelect(connection);
    testInsert(connection);
    testSelect(connection);
  } catch (const std::exception& e) {
    std::cerr << "For testing, you'll need to create a database sqlpp_mysql "
                 "for user root (no password)"
              << std::endl;
    std::cerr << e.what() << std::endl;
  }
}  // namespace mysql=sqlpp::mysql;
