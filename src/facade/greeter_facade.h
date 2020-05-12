#ifndef GREETER_SERVER_HPP
#define GREETER_SERVER_HPP

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

#ifdef BAZEL_BUILD
#include "src/proto/helloworld.grpc.pb.h"
#else
#include "src/proto/helloworld.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::Greeter;
using helloworld::HelloReply;
using helloworld::HelloRequest;
namespace fcdeduction {
namespace facade {
class GreeterServiceImpl final : public Greeter::Service {
 public:
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override;

  Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
                       HelloReply* reply) override;
};

}  // namespace facade
}  // namespace fcdeduction

#endif
