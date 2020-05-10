#include "user_facade.hpp"

#include "src/dal/identification_dao.h"
#include "src/dal/user_dao.h"
#include "src/manager/crypto_manager.h"
#include "src/manager/token_manager.h"
#include "src/util/constant.h"
#include "src/util/ident_type_enum.h"
void fcdeduction::facade::setResponse(
    UserLoginResponse *response,
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
    fcdeduction::dao::UserDao userDao;
    fcdeduction::dao::IdentificationDao identDao;
    std::optional<std::string> foundUser = identDao.findUserIdByIdentKeyAndIdentType(fcdeduction::util::TNT_INST_ID, loginKey, fcdeduction::util::IdentTypeEnum::PASSWORD);
    // 判断用户是否存在
    if (!foundUser.has_value()) {
        setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_EXIST);
        return grpc::Status::OK;
    }
    bool exist = userDao.userExist(fcdeduction::util::TNT_INST_ID, foundUser.value());
    // 判断用户是否存在
    if (!exist) {
        setResponse(response, fcdeduction::util::ResponseEnum::USER_NOT_EXIST);
        return grpc::Status::OK;
    }
    // 判断账号密码是否正确
    // 此次密码是通过 sha256(明文+salt)加密的, 在实际项目中, 加密会用的是国密SM2/SM3/SM4或者椭圆加密, 为了安全性要求, 相应的密钥也会由专门的密钥平台分发.
    std::string salt = getenv("salt");
    fcdeduction::manager::CryptoManager cryptoManager;
    std::string encrypted = cryptoManager.sha256(loginValue, salt);
    if (identDao.identMatch(fcdeduction::util::TNT_INST_ID, *foundUser, loginKey, encrypted, fcdeduction::util::IdentTypeEnum::PASSWORD)) {
        // 生成一个唯一Id
        const std::string token = cryptoManager.generateUUIDV4();
        fcdeduction::manager::TokenManager tokenManager;
        tokenManager.addUserToken(token, foundUser.value());
        response->set_token(token);
        setResponse(response, fcdeduction::util::ResponseEnum::SUCCESS);
    } else {
        setResponse(response, fcdeduction::util::ResponseEnum::INCORRECT_LOGIN_VALUE);
    }
    return grpc::Status::OK;
}