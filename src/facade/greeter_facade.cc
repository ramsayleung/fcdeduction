/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "greeter_facade.h"

// Logic and data behind the server's behavior.
grpc::Status fcdeduction::facade::GreeterServiceImpl::SayHello(
    ServerContext* context, const HelloRequest* request, HelloReply* reply) {
  std::string prefix("Hello ");
  reply->set_message(prefix + request->name());
  return Status::OK;
}

grpc::Status fcdeduction::facade::GreeterServiceImpl::SayHelloAgain(
    ServerContext* context, const HelloRequest* request, HelloReply* reply) {
  std::string prefix("Hello again ");
  reply->set_message(prefix + request->name());
  return Status::OK;
}
