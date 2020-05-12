#include "user_facade.h"

#include <chrono>

#include "spdlog/spdlog.h"
#include "src/dal/identification_dao.h"
#include "src/dal/user_dao.h"
#include "src/manager/crypto_manager.h"
#include "src/manager/token_manager.h"
#include "src/util/config.h"
#include "src/util/constant.h"
#include "src/util/ident_type_enum.h"
void setResponse(UserLoginResponse *response,
                 const fcdeduction::util::ResponseEnum &respEnum) {
  response->set_status(respEnum.getStatus());
  response->set_code(respEnum.getCode());
  response->set_desc(respEnum.getDesc());
}
void setResponse(LoginSessionValidateResponse *response,
                 const fcdeduction::util::ResponseEnum &respEnum) {
  response->set_status(respEnum.getStatus());
  response->set_code(respEnum.getCode());
  response->set_desc(respEnum.getDesc());
}
grpc::Status fcdeduction::facade::UserFacadeImpl::Login(
    grpc::ServerContext *context, const UserLoginRequest *request,
    UserLoginResponse *response) {
  using namespace fcdeduction::util;
  auto loginKey = request->loginkey();
  auto loginValue = request->loginvalue();
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  spdlog::info("start: 用户登录, loginKey:{0}", loginKey);
  fcdeduction::dao::UserDao userDao;
  fcdeduction::dao::IdentificationDao identDao;
  std::optional<std::string> foundUser =
      identDao.findUserIdByIdentKeyAndIdentType(
          fcdeduction::util::getTntInstIdByEnv(), loginKey,
          fcdeduction::util::IdentTypeEnum::PASSWORD);
  // 判断用户是否存在
  if (!foundUser.has_value()) {
    spdlog::warn("用户不存在, loginKey:{0}", loginKey);
    setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_EXIST);
    return grpc::Status::OK;
  }
  bool exist =
      userDao.userExist(fcdeduction::util::getTntInstIdByEnv(), foundUser.value());
  // 判断用户是否存在
  if (!exist) {
    spdlog::warn("用户不存在, loginKey:{0}, userId: {1}", loginKey, *foundUser);
    setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_EXIST);
    return grpc::Status::OK;
  }
  // 判断账号密码是否正确
  // 此次密码是通过 sha256(明文+salt)加密的, 在实际项目中,
  // 加密会用的是国密SM2/SM3/SM4或者椭圆加密, 为了安全性要求,
  // 相应的密钥也会由专门的密钥平台分发.
  std::string salt = getEnvironmentVariableOrDefault("salt", "111111");
  fcdeduction::manager::CryptoManager cryptoManager;
  std::string encrypted = cryptoManager.sha256(loginValue, salt);
  bool identMatch = identDao.identMatch(
      fcdeduction::util::getTntInstIdByEnv(), *foundUser, loginKey, encrypted,
      fcdeduction::util::IdentTypeEnum::PASSWORD);
  if (identMatch) {
    // 生成一个唯一Id
    const std::string token = cryptoManager.generateUUIDV4();
    spdlog::info("登录成功, 生成token, loginKey:{0}, token: {1}", loginKey,
                 token);
    fcdeduction::manager::TokenManager tokenManager;
    tokenManager.addUserToken(token, foundUser.value());
    response->set_token(token);
    setResponse(response, fcdeduction::util::ResponseEnum::SUCCESS);
  } else {
    spdlog::warn("账密不正确, loginKey:{0}", loginKey);
    // TRACE(("账密不正确, loginKey:%s, loginValue: %s", loginKey, loginValue));
    setResponse(response,
                fcdeduction::util::ResponseEnum::INCORRECT_LOGIN_VALUE);
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
          .count();
  spdlog::info("end: 用户登录, loginKey:{0}, 耗时: {1}ms", loginKey, elapsed);
  return grpc::Status::OK;
}
grpc::Status fcdeduction::facade::UserFacadeImpl::validateLoginSession(
    grpc::ServerContext *context, const LoginSessionValidateRequest *request,
    LoginSessionValidateResponse *response) {
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  spdlog::info("start: 用户登录鉴权, token:{0}", request->token());
  fcdeduction::manager::TokenManager tokenManager;
  std::optional<std::string> foundUserId =
      tokenManager.getUserInfoByTokenId(request->token());
  if (!foundUserId.has_value()) {
    spdlog::warn("用户未登录, token: {0}", request->token());
    setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_LOGIN);
    return grpc::Status::OK;
  }

  fcdeduction::dao::UserDao userDao;
  bool exist =
      userDao.userExist(fcdeduction::util::getTntInstIdByEnv(), foundUserId.value());

  // 判断用户是否存在, 防止出现, 用户被删除, token没被清除,
  // 也被认为正常登录成功的情况.
  if (!exist) {
    spdlog::warn("用户不存在, userId: {0}", *foundUserId);
    setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_EXIST);
    return grpc::Status::OK;
  }
  bool validateOk = tokenManager.checkUserToken(request->token());
  if (validateOk) {
    setResponse(response, fcdeduction::util::ResponseEnum::SUCCESS);
  } else {
    setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_LOGIN);
    spdlog::warn("通过token判断用户未登录, token:{0}", request->token());
  }
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
          .count();
  spdlog::info("end: 用户登录鉴权, token:{0}, 耗时: {1}ms", request->token(),
               elapsed);
  return grpc::Status::OK;
}