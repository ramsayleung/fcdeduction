#include "user_server.hpp"
#include "greeter_server.hpp"

void startServer() {
    std::string addr = "0.0.0.0:50051";
    UserFacadeImpl userFacadeservice;
    GreeterServiceImpl greeterFacadeService;
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
