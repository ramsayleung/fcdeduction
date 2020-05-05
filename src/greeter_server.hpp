#ifndef GREETER_SERVER_HPP
#define GREETER_SERVER_HPP

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "src/helloworld.grpc.pb.h"
#else
#include "src/helloworld.grpc.pb.h"
#endif

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;
class GreeterServiceImpl final : public Greeter::Service {
public:
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override;

  Status SayHelloAgain(ServerContext* context, const HelloRequest* request,
			HelloReply* reply) override;
};


#endif
