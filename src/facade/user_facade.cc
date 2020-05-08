#include "user_facade.hpp"

#include "src/manager/token_manager.hpp"
void fcdeduction::facade::setResponse(UserLoginResponse *response,const fcdeduction::util::ResponseEnum& respEnum) {
  // response->set_status();
  // response->set_code();
  // response->set_desc();
}
grpc::Status fcdeduction::facade::UserFacadeImpl::Login(
    grpc::ServerContext *context, const UserLoginRequest *request,
    UserLoginResponse *response) {
  auto loginKey = request->loginkey();
  auto loginValue = request->loginvalue();
  // 判断用户是否存在
  if (true) {
    // 判断账号密码是否正确
    if (true) {
      // 生成一个唯一Id
      const std::string token = "uuid";
      // fcdeduction::util::ResponseEnum success =
      //     fcdeduction::util::ResponseEnum::SUCCESS;
      // setResponse(response, SUCCESS());
      response->set_token(token);
    } else {
      // setResponse(response, INCORRECT_LOGIN_VALUE());
    }
  } else {
    // setResponse(response, USER_NOT_EXIST());
  }
  return grpc::Status::OK;
}