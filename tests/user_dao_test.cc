#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/user.h"
#include "src/dal/user_dao.h"
#include "src/manager/database_manager.hpp"
model::DeUser deuser = {};
namespace mysql = sqlpp::mysql;
void testDeleteUser(mysql::connection& connection, const std::string& userId,
                    const std::string& tntInstId) {
  connection(sqlpp::remove_from(deuser).where(deuser.userId == userId and
                                              deuser.tntInstId == tntInstId));
}

void testSelectUserByCondition(mysql::connection& connection,
                               const std::string& userId,
                               const std::string& tntInstId) {
  const auto& user = connection(sqlpp::select(all_of(deuser))
                                    .from(deuser)
                                    .where(deuser.userId == userId and
                                           deuser.tntInstId == tntInstId))
                         .front();
  EXPECT_EQ(user.userId, userId);
  std::cout << "user.userId " << user.userId << " "
            << "user.userName" << user.userName << " "
            << "user.userType" << user.userType << " "
            << "user.tntInstId" << user.tntInstId << " "
            << "\n";
}

void testInsertUser(mysql::connection& connection, const std::string& userId,
                    const std::string& tntInstId) {
  connection(sqlpp::insert_into(deuser).set(
      deuser.userId = userId, deuser.tntInstId = tntInstId,
      deuser.userName = "TestInsert", deuser.userType = "1",
      deuser.gmtCreate = std::chrono::system_clock::now(),
      deuser.gmtModified = std::chrono::system_clock::now()));
}
TEST(DAOTEST, USEREXISTTEST) {
  const std::string userId = "00001000";
  const std::string tntInstId = "A0000001";
  fcdeduction::manager::DatabaseManager dbManager(
      "127.0.0.1", getenv("mysql_database"), getenv("mysql_user"),
      getenv("mysql_password"));
  auto connection = dbManager.getConnection();
  // 在插入前先删除可能存在的数据
  testDeleteUser(*connection, userId, tntInstId);
  // 调用插入
  testInsertUser(*connection, userId, tntInstId);
  // 确保插入成功
  testSelectUserByCondition(*connection, userId, tntInstId);
  // 确保用户存在
  fcdeduction::dao::UserDao userDao;
  EXPECT_TRUE(userDao.userExist(*connection, userId, tntInstId));
  // 然后再删掉, 保证下次插入成功
  testDeleteUser(*connection, userId, tntInstId);
}