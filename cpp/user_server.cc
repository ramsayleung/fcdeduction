#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>

#include <iostream>
#include <unordered_map>

#include "user.grpc.pb.h"

using user::User;
using user::UserLoginRequest;
using user::UserLoginResponse;
class UserDAO {
};
class UserImpl final : public User::Service {
   public:
    grpc::Status Login(grpc::ServerContext *context, const UserLoginRequest *request, UserLoginResponse *response) override {
        auto loginKey = request->loginkey();
        auto loginValue = request->loginvalue();
        for (auto &entry : userLoginKeyValue_) {
            std::cout << "key: " << entry.first << " value: " << entry.second << std::endl;
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

   private:
    std::unordered_map<std::string, std::string> userLoginKeyValue_ = {{"ramsay", "123456"}};
    std::unordered_map<std::string, UserDAO> tokenCache_;
};
int main(int argc, char const *argv[]) {
    std::string addr = "0.0.0.0:5000";
    UserImpl service;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    auto server = builder.BuildAndStart();
    std::cout << " Server listening on " << addr << '\n';
    server->Wait();
    return 0;
}
