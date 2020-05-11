#include "src/facade/user_facade.h"

#include <chrono>
#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/identification_dao.h"
#include "src/dal/user_dao.h"
#include "src/manager/crypto_manager.h"
#include "src/manager/redis_manager.hpp"
#include "src/manager/snowflake_id_manager.h"
#include "src/manager/token_manager.h"
#include "src/util/constant.h"
#include "src/util/rel_status_enum.h"

TEST(FACADE_TEST, USER_FACADE_LOGIN_TEST) {
  // int main() {
  fcdeduction::facade::UserFacadeImpl service;
  fcdeduction::manager::SnowFlakeIdManager idManager(
      fcdeduction::util::DATA_CENTER_ID, fcdeduction::util::MACHINE_ID);
  user::UserLoginRequest request;
  request.set_loginkey("ramsay");
  request.set_loginvalue("password");
  user::UserLoginResponse response;
  grpc::ServerContext context;
  // 用户不存在, db无数据
  service.Login(&context, &request, &response);
  EXPECT_EQ(response.code(), "01");
  EXPECT_EQ(response.status(), "FAILED");

  fcdeduction::dao::IdentificationDao identDao;
  fcdeduction::dao::UserDao userDao;
  fcdeduction::dataobject::Identification ident;
  fcdeduction::manager::CryptoManager cryptoManager;
  const std::string salt = getenv("salt");
  const std::string plainText = "password";
  ident.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  ident.identId = idManager.nextId();
  ident.identKey = "ramsay";
  ident.identType = fcdeduction::util::enumToString(
      fcdeduction::util::IdentTypeEnum::PASSWORD);
  ident.identValue = cryptoManager.sha256(plainText, salt);
  ident.userId = "userId000";
  ident.gmtCreate = std::chrono::system_clock::now();
  ident.gmtModified = std::chrono::system_clock::now();

  fcdeduction::dataobject::User user;
  user.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  user.userId = "userId000";
  user.userType = "1";
  user.userName = "ramsay";
  user.gmtCreate = std::chrono::system_clock::now();
  user.gmtModified = std::chrono::system_clock::now();

  // 运行前清理数据
  identDao.deleteIdent(fcdeduction::util::TEST_TNT_INST_ID, ident.userId,
                       ident.identKey, ident.identType);
  userDao.deleteUser(fcdeduction::util::TEST_TNT_INST_ID, user.userId);

  identDao.insertIdent(ident);
  service.Login(&context, &request, &response);

  // 用户不存在, user表无对应用户
  EXPECT_EQ(response.code(), "01");
  EXPECT_EQ(response.status(), "FAILED");

  userDao.insertUser(user);

  // 账密不正确
  request.set_loginvalue("hahaha");
  service.Login(&context, &request, &response);
  EXPECT_EQ(response.code(), "02");
  EXPECT_EQ(response.status(), "FAILED");

  request.set_loginvalue("password");
  // 登录成功
  service.Login(&context, &request, &response);
  fcdeduction::manager::RedisManager redisManager;
  EXPECT_TRUE(redisManager.get(ident.userId).has_value());
  EXPECT_EQ(response.code(), "00");
  std::cout << "response.code: " << response.code() << '\n'
            << "response.status: " << response.status() << '\n';
  EXPECT_EQ(response.status(), "SUCCESS");

  // 清理数据
  identDao.deleteIdent(fcdeduction::util::TEST_TNT_INST_ID, ident.userId,
                       ident.identKey, ident.identType);
  userDao.deleteUser(fcdeduction::util::TEST_TNT_INST_ID, user.userId);
}
TEST(FACADE_TEST, USER_FACADE_VALIDATE_LOGIN_SESSION_TEST) {
  fcdeduction::manager::CryptoManager cryptoManager;
  const std::string token1 = cryptoManager.generateUUIDV4();
  const std::string token2 = cryptoManager.generateUUIDV4();
  const std::string userId = "user1";
  fcdeduction::manager::TokenManager tokenManager;
  tokenManager.addUserToken(token1, userId);
  grpc::ServerContext context;
  fcdeduction::facade::UserFacadeImpl service;
  user::LoginSessionValidateRequest request;
  user::LoginSessionValidateResponse response;
  request.set_token(token1);
  service.validateLoginSession(&context, &request, &response);
  EXPECT_EQ(response.status(), "SUCCESS");
  EXPECT_EQ(response.code(), "00");
  tokenManager.addUserToken(token2, userId);
  service.validateLoginSession(&context, &request, &response);
  EXPECT_EQ(response.status(), "FAILED");
  EXPECT_EQ(response.code(), "03");
}
