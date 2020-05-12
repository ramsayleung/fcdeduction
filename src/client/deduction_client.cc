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
using deduction::DeductionListQueryRequest;
using deduction::DeductionListQueryResponse;
using grpc::Status;
class DeductionClient {
 public:
  DeductionClient(std::shared_ptr<grpc::Channel> channel)
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
    Status status = stub_->CreateDeductionService(&context, request, &response);
    if (status.ok()) {
      spdlog::info(
          "DeductionFacade.create() response: status:{0}, code:{1}, desc: "
          "{2}",
          response.status(), response.code(), response.desc());
    } else {
      spdlog::error("通讯异常: error_code: {0}, error_message{1}",
                    status.error_code(), status.error_message());
    }
  }
  void close(const std::string &token, const std::string &arNo,
             const std::string &pdCode, const std::string &userId) {
    DeduceRequest request;
    request.set_arno(arNo);
    request.set_pdcode(pdCode);
    request.set_userid(userId);
    request.set_token(token);
    DeduceResponse response;
    grpc::ClientContext context;
    Status status = stub_->CloseDeductionService(&context, request, &response);
    if (status.ok()) {
      spdlog::info(
          "DeductionFacade.close() response: status:{0}, code:{1}, desc: "
          "{2}",
          response.status(), response.code(), response.desc());
    } else {
      spdlog::error("通讯异常: error_code: {0}, error_message{1}",
                    status.error_code(), status.error_message());
    }
  }
  void queryList(const std::string &token, const std::string &arNo,
                 const std::string &userId, const uint32_t pageIndex,
                 const uint32_t pageSize) {
    DeductionListQueryRequest request;
    request.set_arno(arNo);
    request.set_userid(userId);
    request.set_token(token);
    request.set_pageindex(pageIndex);
    request.set_pagesize(pageSize);
    DeductionListQueryResponse response;
    grpc::ClientContext context;
    Status status = stub_->QueryDeductionListByUserIdAndArType(
        &context, request, &response);
    if (status.ok()) {
      spdlog::info(
          "DeductionFacade.queryList() response: status:{0}, code:{1}, desc: "
          "{2}",
          response.status(), response.code(), response.desc());
      if (response.code() == "00") {
        for (int i = 0; i < response.simpliedproductinfo_size(); i++) {
          const std::string pdCode =
              response.simpliedproductinfo(i).productcode();
          const std::string pdName =
              response.simpliedproductinfo(i).productname();
          const std::string pdOrgName =
              response.simpliedproductinfo(i).proudctorgname();
          spdlog::info("扣费服务列表: 产品码:{0}, 产品名:{1}, 产品所属机构:{2}",
                       pdCode, pdName, pdOrgName);
        }
      }
    } else {
      spdlog::error("通讯异常: error_code: {0}, error_message{1}",
                    status.error_code(), status.error_message());
    }
  }

 private:
  std::unique_ptr<DeductionFacade::Stub> stub_;
};
int main(int argc, char const *argv[]) {
  auto channel = grpc::CreateChannel("localhost:50051",
                                     grpc::InsecureChannelCredentials());
  DeductionClient client(channel);
  const char *token =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--token");
  const char *arNo =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--arno");
  const char *pdCode =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--pdcode");
  const char *userId =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--userid");
  const char *interface =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--interface");
  const char *pi =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--pageindex");
  const char *ps =
      fcdeduction::util::getCmdOption(argv, argv + argc, "--pagesize");
  // 默认index
  uint32_t pageIndex = 0;
  // 默认size
  uint32_t pageSize = 20;
  if (pi) {
    pageIndex = static_cast<uint32_t>(std::stoul(pi));
  }
  if (ps) {
    pageSize = static_cast<uint32_t>(std::stoul(ps));
  }
  if (interface) {
    if (std::string(interface) == "create" && token && arNo && pdCode &&
        userId) {
      spdlog::info("开通服务: token:{0}, arNo: {1}, pdCode: {2}, userId: {3}",
                   token, arNo, pdCode, userId);
      client.create(token, arNo, pdCode, userId);
    } else if (std::string(interface) == "close" && token && arNo && pdCode &&
               userId) {
      spdlog::info("关闭服务: token:{0}, arNo: {1}, pdCode: {2}, userId: {3}",
                   token, arNo, pdCode, userId);
      client.close(token, arNo, pdCode, userId);
    } else if (std::string(interface) == "querylist" && token && arNo &&
               userId) {
      spdlog::info(
          "查询服务列表: token:{0}, arNo: {1}, userId: {2}, pageIndex: {3}, "
          "pageSize: {4}",
          token, arNo, userId, pageIndex, pageSize);
      client.queryList(token, arNo, userId, pageIndex, pageSize);
    }
  }
  return 0;
}
