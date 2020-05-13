#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc/grpc.h>

#include <iostream>
#include <memory>
#include <string>

#include "spdlog/spdlog.h"
#include "src/proto/user.grpc.pb.h"
#include "src/util/arg_parse.h"
using grpc::Status;
using user::LoginSessionValidateRequest;
using user::LoginSessionValidateResponse;
using user::UserFacade;
using user::UserLoginRequest;
using user::UserLoginResponse;
class UserClient {
 public:
  UserClient(std::shared_ptr<grpc::Channel> channel)
      : stub_(UserFacade::NewStub(channel)) {}
  void login(const std::string &loginKey, const std::string &loginValue) {
    UserLoginRequest request;
    request.set_loginkey(loginKey);
    request.set_loginvalue(loginValue);
    UserLoginResponse response;
    grpc::ClientContext context;
    Status status = stub_->Login(&context, request, &response);
    if (status.ok()) {
      spdlog::info(
          "UserFacade.Login() response: status:{0}, code:{1}, desc: {2}",
          response.status(), response.code(), response.desc());
      if (response.code() == "00") {
        spdlog::info("UserFacade.Login() successfully: token:{0}",
                     response.token());
      }
    } else {
      spdlog::error("通讯异常: error_code: {0}, error_message{1}",
                    status.error_code(), status.error_message());
    }
  }

  void validate(const std::string &token) {
    LoginSessionValidateRequest request;
    LoginSessionValidateResponse response;
    request.set_token(token);
    grpc::ClientContext context;
    Status status = stub_->validateLoginSession(&context, request, &response);
    if (status.ok()) {
      spdlog::info(
          "UserFacade.validateLoginSession() response: status:{0}, code:{1}, "
          "desc: {2}",
          response.status(), response.code(), response.desc());
    } else {
      spdlog::error("通讯异常: error_code: {0}, error_message{1}",
                    status.error_code(), status.error_message());
    }
  }

 private:
  std::unique_ptr<UserFacade::Stub> stub_;
};
int main(int argc, char const *argv[]) {
  std::string address = "0.0.0.0:50051";
  const char *target =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--target");
  if (target) {
    address = target;
  }
  const char *loginKey =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--key");
  const char *loginValue =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--value");
  const char *token =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--token");
  auto channel =
      grpc::CreateChannel(address, grpc::InsecureChannelCredentials());
  UserClient client(channel);
  if (loginKey && loginValue) {
    spdlog::info("用户登录: loginKey:{0}, loginValue: {1}", loginKey,
                 loginValue);
    client.login(loginKey, loginValue);
  }
  if (token) {
    spdlog::info("登录态校验: token:{0}", token);
    client.validate(token);
  }
  return 0;
}
