#include "user_server.hpp"

grpc::Status UserFacadeImpl::Login(grpc::ServerContext *context,
                                   const UserLoginRequest *request,
                                   UserLoginResponse *response) {
  auto loginKey = request->loginkey();
  auto loginValue = request->loginvalue();
  for (auto &entry : userLoginKeyValue_) {
    std::cout << "key: " << entry.first << " value: " << entry.second
              << std::endl;
  }
  if (userLoginKeyValue_.find(loginKey) != userLoginKeyValue_.end()) {
    auto currentValue = userLoginKeyValue_[loginKey];
    if (currentValue == loginValue) {
      // 生成一个唯一Id
      const std::string token = "uuid";
      UserDAO userDao;
      tokenCache_[token] = userDao;
      response->set_status("SUCCESS");
      response->set_code("00");
      response->set_desc("");
      response->set_token(token);
    } else {
      response->set_status("FAILED");
      response->set_code("INCORRECT_LOGIN_VALUE");
      response->set_desc("账户/密码输入不正确");
    }
  } else {
    response->set_status("FAILED");
    response->set_code("USER_NOT_EXIST");
    response->set_desc("用户不存在");
  }
  return grpc::Status::OK;
}
