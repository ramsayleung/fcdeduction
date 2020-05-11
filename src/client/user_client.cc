#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc/grpc.h>

#include <iostream>
#include <memory>
#include <string>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"
#include "src/proto/user.grpc.pb.h"
#include "src/util/arg_parse.h"
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
    stub_->Login(&context, request, &response);
    std::cout << "Login()-response: status" << response.status() << "\n"
              << " code" << response.code() << "\n"
              << " message" << response.desc() << '\n';
  }

 private:
  std::unique_ptr<UserFacade::Stub> stub_;
};
int main(int argc, char const *argv[]) {
  auto channel = grpc::CreateChannel("0.0.0.0:50051",
                                     grpc::InsecureChannelCredentials());
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
