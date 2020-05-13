#include "facade/deduction_facade.h"
#include "facade/greeter_facade.h"
#include "facade/user_facade.h"
void startServer() {
  std::string addr = "0.0.0.0:50051";
  fcdeduction::facade::UserFacadeImpl userFacadeservice;
  fcdeduction::facade::GreeterServiceImpl greeterFacadeService;
  fcdeduction::facade::DeductionFacadeImpl deductionFacadeService;
  grpc::ServerBuilder builder;
  builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
  builder.RegisterService(&userFacadeservice);
  builder.RegisterService(&greeterFacadeService);
  builder.RegisterService(&deductionFacadeService);
  auto server = builder.BuildAndStart();
  std::cout << " Server listening on " << addr << '\n';
  server->Wait();
}
int main(int argc, char const *argv[]) {
  startServer();
  return 0;
}
