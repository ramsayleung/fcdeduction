#include "src/facade/user_facade.h"

#include <chrono>
#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/identification_dao.h"
#include "src/dal/user_dao.h"
#include "src/manager/crypto_manager.h"
#include "src/manager/redis_manager.h"
#include "src/manager/snowflake_id_manager.h"
#include "src/manager/token_manager.h"
#include "src/util/config.h"
#include "src/util/constant.h"
#include "src/util/rel_status_enum.h"
#include "src/util/response_enum.h"
static fcdeduction::facade::UserFacadeImpl service;

static fcdeduction::manager::SnowFlakeIdManager idManager(
    fcdeduction::util::DATA_CENTER_ID, fcdeduction::util::MACHINE_ID);

static fcdeduction::dao::IdentificationDao identDao;

static fcdeduction::dao::UserDao userDao;

static fcdeduction::manager::CryptoManager cryptoManager;

static fcdeduction::manager::RedisManager redisManager;

static fcdeduction::manager::TokenManager tokenManager;
TEST(FACADE_TEST, USER_FACADE_LOGIN_TEST) {
  // int main() {
  using namespace fcdeduction::util;
  user::UserLoginRequest request;
  request.set_loginkey("ramsay");
  request.set_loginvalue("password");
  user::UserLoginResponse response;
  grpc::ServerContext context;
  // 用户不存在, db无数据
  service.Login(&context, &request, &response);
  EXPECT_EQ(response.code(), "01");
  EXPECT_EQ(response.status(), "FAILED");

  fcdeduction::dataobject::Identification ident;
  const std::string salt = getEnvironmentVariableOrDefault("salt", "111111");
  const std::string plainText = "password";
  ident.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  ident.identId = idManager.nextId();
  ident.identKey = "ramsay";
  ident.identType = fcdeduction::util::enumToString(
      fcdeduction::util::IdentTypeEnum::PASSWORD);
  ident.identValue = cryptoManager.sha256(plainText, salt);
  ident.userId = "userId000";
  ident.gmtCreate = std::chrono::system_clock::now();
  ident.gmtModified = std::chrono::system_clock::now();

  fcdeduction::dataobject::User user;
  user.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  user.userId = "userId000";
  user.userType = "1";
  user.userName = "ramsay";
  user.gmtCreate = std::chrono::system_clock::now();
  user.gmtModified = std::chrono::system_clock::now();

  // 运行前清理数据
  identDao.deleteIdent(fcdeduction::util::getTntInstIdByEnv(), ident.userId,
                       ident.identKey, ident.identType);
  userDao.deleteUser(fcdeduction::util::getTntInstIdByEnv(), user.userId);

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
  EXPECT_TRUE(redisManager.get(ident.userId).has_value());
  EXPECT_EQ(response.code(), "00");
  std::cout << "response.code: " << response.code() << '\n'
            << "response.status: " << response.status() << '\n';
  EXPECT_EQ(response.status(), "SUCCESS");

  // 清理数据
  identDao.deleteIdent(fcdeduction::util::getTntInstIdByEnv(), ident.userId,
                       ident.identKey, ident.identType);
  userDao.deleteUser(fcdeduction::util::getTntInstIdByEnv(), user.userId);
}

TEST(FACADE_TEST, USER_FACADE_VALIDATE_LOGIN_SESSION_TEST) {
  using namespace fcdeduction::util;
  fcdeduction::dataobject::User user;
  user.tntInstId = getTntInstIdByEnv();
  user.userId = "userId000";
  user.userType = "1";
  user.userName = "ramsay";
  user.gmtCreate = std::chrono::system_clock::now();
  user.gmtModified = std::chrono::system_clock::now();

  const std::string token1 = cryptoManager.generateUUIDV4();
  const std::string token2 = cryptoManager.generateUUIDV4();
  const std::string userId = user.userId;
  grpc::ServerContext context;
  user::LoginSessionValidateRequest request;
  user::LoginSessionValidateResponse response;
  request.set_token(token1);
  // 未设置登录态
  service.validateLoginSession(&context, &request, &response);
  EXPECT_EQ(response.status(), ResponseEnum::USER_NOT_LOGIN.getStatus());
  EXPECT_EQ(response.code(), ResponseEnum::USER_NOT_LOGIN.getCode());

  // 设置登录态, 但用户不存在.
  tokenManager.addUserToken(token1, userId);
  service.validateLoginSession(&context, &request, &response);
  EXPECT_EQ(response.status(), ResponseEnum::USER_NOT_EXIST.getStatus());
  EXPECT_EQ(response.code(), ResponseEnum::USER_NOT_EXIST.getCode());

  // 插入用户
  userDao.deleteUser(user.tntInstId, user.userId);
  userDao.insertUser(user);
  service.validateLoginSession(&context, &request, &response);
  EXPECT_EQ(response.status(), ResponseEnum::SUCCESS.getStatus());
  EXPECT_EQ(response.code(), ResponseEnum::SUCCESS.getCode());

  // 设置一个新的登录态, 原来的登录态被失效.
  tokenManager.addUserToken(token2, userId);
  service.validateLoginSession(&context, &request, &response);
  EXPECT_EQ(response.status(), ResponseEnum::USER_NOT_LOGIN.getStatus());
  EXPECT_EQ(response.code(), ResponseEnum::USER_NOT_LOGIN.getCode());
  userDao.deleteUser(user.tntInstId, user.userId);
}
