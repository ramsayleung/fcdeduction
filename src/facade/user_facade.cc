#include "user_facade.h"

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "src/dal/identification_dao.h"
#include "src/dal/user_dao.h"
#include "src/manager/crypto_manager.h"
#include "src/manager/token_manager.h"
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
    auto loginKey = request->loginkey();
    auto loginValue = request->loginvalue();
    spdlog::info("start: 用户登录, loginKey:{0}, loginValue: {1}", loginKey,
                 loginValue);
    fcdeduction::dao::UserDao userDao;
    fcdeduction::dao::IdentificationDao identDao;
    std::optional<std::string> foundUser =
        identDao.findUserIdByIdentKeyAndIdentType(
            fcdeduction::util::TNT_INST_ID, loginKey,
            fcdeduction::util::IdentTypeEnum::PASSWORD);
    // 判断用户是否存在
    if (!foundUser.has_value()) {
        spdlog::warn("用户不存在, loginKey:{0}, loginValue: {1}", loginKey,
                     loginValue);
        setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_EXIST);
        return grpc::Status::OK;
    }
    bool exist =
        userDao.userExist(fcdeduction::util::TNT_INST_ID, foundUser.value());
    // 判断用户是否存在
    if (!exist) {
        spdlog::warn("用户不存在, loginKey:{0}, loginValue: {1}, userId: {2}",
                     loginKey, loginValue, *foundUser);
        setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_EXIST);
        return grpc::Status::OK;
    }
    // 判断账号密码是否正确
    // 此次密码是通过 sha256(明文+salt)加密的, 在实际项目中,
    // 加密会用的是国密SM2/SM3/SM4或者椭圆加密, 为了安全性要求,
    // 相应的密钥也会由专门的密钥平台分发.
    std::string salt = getenv("salt");
    fcdeduction::manager::CryptoManager cryptoManager;
    std::string encrypted = cryptoManager.sha256(loginValue, salt);
    bool identMatch = identDao.identMatch(
        fcdeduction::util::TNT_INST_ID, *foundUser, loginKey, encrypted,
        fcdeduction::util::IdentTypeEnum::PASSWORD);
    if (identMatch) {
        // 生成一个唯一Id
        const std::string token = cryptoManager.generateUUIDV4();
        spdlog::info(
            "登录成功, 生成token, loginKey:{0}, loginValue: {1}, token: {2}",
            loginKey, loginValue, token);
        fcdeduction::manager::TokenManager tokenManager;
        tokenManager.addUserToken(token, foundUser.value());
        response->set_token(token);
        setResponse(response, fcdeduction::util::ResponseEnum::SUCCESS);
    } else {
        spdlog::warn("账密不正确, loginKey:{0}, loginValue: {1}", loginKey,
                     loginValue);
        // TRACE(("账密不正确, loginKey:%s, loginValue: %s", loginKey, loginValue));
        setResponse(response,
                    fcdeduction::util::ResponseEnum::INCORRECT_LOGIN_VALUE);
    }
    return grpc::Status::OK;
}
grpc::Status fcdeduction::facade::UserFacadeImpl::validateLoginSession(
    grpc::ServerContext *context, const LoginSessionValidateRequest *request,
    LoginSessionValidateResponse *response) {
    fcdeduction::manager::TokenManager tokenManager;
    std::optional<std::string> foundUserId =
        tokenManager.getUserInfoByTokenId(request->token());
    if (!foundUserId.has_value()) {
        setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_LOGIN);
    }

    fcdeduction::dao::UserDao userDao;
    bool exist =
        userDao.userExist(fcdeduction::util::TNT_INST_ID, foundUserId.value());

    // 判断用户是否存在
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
    return grpc::Status::OK;
}