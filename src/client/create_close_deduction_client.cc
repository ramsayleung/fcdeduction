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
#include "src/proto/deduction.grpc.pb.h"
#include "src/util/arg_parse.h"
using deduction::DeduceRequest;
using deduction::DeduceResponse;
using deduction::DeductionFacade;
class CreateCloseDeductionClient {
 public:
  CreateCloseDeductionClient(std::shared_ptr<grpc::Channel> channel)
      : stub_(DeductionFacade::NewStub(channel)) {}
  void create(const std::string &token, const std::string &arNo,
              const std::string &pdCode, const std::string &userId) {
    DeduceRequest request;
    request.set_arno(arNo);
    request.set_pdcode(pdCode);
    request.set_userid(userId);
    request.set_token(token);
    DeduceResponse response;
    grpc::ClientContext context;
    stub_->CreateDeductionService(&context, request, &response);
    std::cout << "status" << response.status() << "\n"
              << " code" << response.code() << "\n"
              << " message" << response.desc() << '\n';
  }

 private:
  std::unique_ptr<DeductionFacade::Stub> stub_;
};
int main(int argc, char const *argv[]) {
  auto channel = grpc::CreateChannel("localhost:50051",
                                     grpc::InsecureChannelCredentials());
  CreateCloseDeductionClient client(channel);
  const char *token = fcdeduction::util::getCmdOption(argv, argv + argc, "-t");
  const char *arNo = fcdeduction::util::getCmdOption(argv, argv + argc, "-a");
  const char *pdCode = fcdeduction::util::getCmdOption(argv, argv + argc, "-p");
  const char *userId = fcdeduction::util::getCmdOption(argv, argv + argc, "-u");
  if (token && arNo && pdCode && userId) {
    spdlog::info("开通服务: token:{0}, arNo: {1}, pdCode: {2}, userId: {3}",
                 token, arNo, pdCode, userId);
    client.create(token, arNo, pdCode, userId);
  }
  return 0;
}
