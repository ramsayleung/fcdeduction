#ifndef USER_SERVER_HPP
#define USER_SERVER_HPP
#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>

#include <iostream>
#include <unordered_map>

#include "src/proto/user.grpc.pb.h"

using user::UserFacade;
using user::UserLoginRequest;
using user::UserLoginResponse;
namespace fcdeduction {
namespace facade {
class UserDAO {};

class UserFacadeImpl final : public UserFacade::Service {
 public:
  grpc::Status Login(grpc::ServerContext *context,
                     const UserLoginRequest *request,
                     UserLoginResponse *response) override;

 private:
  std::unordered_map<std::string, std::string> userLoginKeyValue_ = {
      {"ramsay", "123456"}};
  std::unordered_map<std::string, UserDAO> tokenCache_;
};
}  // namespace facade
};  // namespace fcdeduction

#endif
