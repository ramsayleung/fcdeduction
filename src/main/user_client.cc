#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include <grpc/grpc.h>

#include <iostream>
#include <memory>
#include <string>

#include "user.grpc.pb.h"

using user::UserFacade;
using user::UserLoginRequest;
using user::UserLoginResponse;

class UserClient {
   public:
    UserClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(UserFacade::NewStub(channel)) {}
    void login(const std::string &loginValue, const std::string &loginKey) {
        UserLoginRequest request;
        request.set_loginkey(loginKey);
        request.set_loginvalue(loginValue);
        UserLoginResponse response;
        grpc::ClientContext context;
        stub_->Login(&context, request, &response);
        std::cout << "Login()-response: status"
                  << response.status()
                  << " code"
                  << response.code()
                  << " message"
                  << response.desc()
                  << '\n';
    }

   private:
    std::unique_ptr<UserFacade::Stub> stub_;
};
int main(int argc, char const *argv[]) {
    auto channel = grpc::CreateChannel("localhost:5000", grpc::InsecureChannelCredentials());
    UserClient client(channel);
    client.login("ramsay", "888888");
    client.login("ramsay", "123456");
    return 0;
}
