#include "src/dal/user_dao.h"

#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/user.h"
#include "src/dal/user_do.h"
#include "src/manager/database_manager.hpp"
TEST(DAOTEST, USEREXISTTEST) {
  const std::string userId = "00001000";
  const std::string tntInstId = "A0000001";
  fcdeduction::dataobject::User user;
  user.userId = userId;
  user.tntInstId = tntInstId;
  user.userName = "TestInsert";
  user.userType = "1";
  user.gmtCreate = std::chrono::system_clock::now();
  user.gmtModified = std::chrono::system_clock::now();
  fcdeduction::dao::UserDao userDao;
  // 在插入前先删除可能存在的数据
  userDao.deleteUser(tntInstId, userId);
  // 调用插入
  userDao.insertUser(user);
  // 确保用户存在
  EXPECT_TRUE(userDao.userExist(tntInstId, userId));
  // 然后再删掉, 保证下次插入成功
  userDao.deleteUser(tntInstId, userId);
}