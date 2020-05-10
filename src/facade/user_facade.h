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
#include "src/util/response_enum.h"
using user::LoginSessionValidateRequest;
using user::LoginSessionValidateResponse;
using user::UserFacade;
using user::UserLoginRequest;
using user::UserLoginResponse;
namespace fcdeduction {
namespace facade {
void setResponse(UserLoginResponse *response,
                 const fcdeduction::util::ResponseEnum &respEnum);

class UserFacadeImpl final : public UserFacade::Service {
 public:
  grpc::Status Login(grpc::ServerContext *context,
                     const UserLoginRequest *request,
                     UserLoginResponse *response) override;
  grpc::Status validateLoginSession(
      grpc::ServerContext *context, const LoginSessionValidateRequest *request,
      LoginSessionValidateResponse *response) override;

 private:
};
}  // namespace facade
};  // namespace fcdeduction

#endif
