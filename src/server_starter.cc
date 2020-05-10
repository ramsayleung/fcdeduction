#include "facade/user_facade.h"
#include "facade/greeter_facade.hpp"

void startServer() {
    std::string addr = "0.0.0.0:50051";
    fcdeduction::facade::UserFacadeImpl userFacadeservice;
    fcdeduction::facade::GreeterServiceImpl greeterFacadeService;
    grpc::ServerBuilder builder;
    builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&userFacadeservice);
    builder.RegisterService(&greeterFacadeService);
    auto server = builder.BuildAndStart();
    std::cout << " Server listening on " << addr << '\n';
    server->Wait();

}
int main(int argc, char const *argv[]) {
    startServer();
    return 0;
}
