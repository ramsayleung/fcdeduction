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

 private:
  std::unique_ptr<UserFacade::Stub> stub_;
};
int main(int argc, char const *argv[]) {
  auto channel =
      grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials());
  UserClient client(channel);
  const char *loginKey =
      fcdeduction::util::getCmdOption(argv, argv + argc, "-k");
  const char *loginValue =
      fcdeduction::util::getCmdOption(argv, argv + argc, "-v");
  if (loginKey && loginValue) {
    spdlog::info("用户登录: loginKey:{0}, loginValue: {1}", loginKey,
                 loginValue);
    client.login(loginKey, loginValue);
  }
  return 0;
}
