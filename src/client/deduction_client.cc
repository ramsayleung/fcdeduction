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
            std::cout << "status" << response.status() << "\n"
                      << " code" << response.code() << "\n"
                      << " message" << response.desc() << '\n';
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
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
            std::cout << "status" << response.status() << "\n"
                      << " code" << response.code() << "\n"
                      << " message" << response.desc() << '\n';
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
        }
    }
    void queryList(const std::string &token, const std::string &arNo,
                   const std::string &userId) {
        DeductionListQueryRequest request;
        request.set_arno(arNo);
        request.set_userid(userId);
        request.set_token(token);
        DeductionListQueryResponse response;
        grpc::ClientContext context;
        Status status = stub_->QueryDeductionListByUserIdAndArType(&context, request, &response);
        if (status.ok()) {
            std::cout << "status" << response.status() << "\n"
                      << " code" << response.code() << "\n"
                      << " message" << response.desc() << '\n';
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
        }
    }

   private:
    std::unique_ptr<DeductionFacade::Stub> stub_;
};
int main(int argc, char const *argv[]) {
    auto channel = grpc::CreateChannel("localhost:50051",
                                       grpc::InsecureChannelCredentials());
    DeductionClient client(channel);
    const char *token = fcdeduction::util::getCmdOption(argv, argv + argc, "--token");
    const char *arNo = fcdeduction::util::getCmdOption(argv, argv + argc, "--arno");
    const char *pdCode = fcdeduction::util::getCmdOption(argv, argv + argc, "--pdcode");
    const char *userId = fcdeduction::util::getCmdOption(argv, argv + argc, "--userid");
    const char *interface = fcdeduction::util::getCmdOption(argv, argv + argc, "--interface");
    if (interface) {
        if (std::string(interface) == "create" && token && arNo && pdCode && userId) {
            spdlog::info("开通服务: token:{0}, arNo: {1}, pdCode: {2}, userId: {3}",
                         token, arNo, pdCode, userId);
            client.create(token, arNo, pdCode, userId);
        } else if (std::string(interface) == "close" && token && arNo && pdCode && userId) {
            spdlog::info("关闭服务: token:{0}, arNo: {1}, pdCode: {2}, userId: {3}",
                         token, arNo, pdCode, userId);
            client.close(token, arNo, pdCode, userId);
        } else if (std::string(interface) == "queryList" && token && arNo && userId) {
            spdlog::info("查询服务列表: token:{0}, arNo: {1}, userId: {2}",
                         token, arNo, pdCode, userId);
            client.queryList(token, arNo, userId);
        }
    }
    return 0;
}
