#ifndef FACADE_DEDUCTION_FACADE_H
#define FACADE_DEDUCTION_FACADE_H

#include <grpc++/security/server_credentials.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc/grpc.h>

#include "src/proto/deduction.grpc.pb.h"
using deduction::DeduceRequest;
using deduction::DeduceResponse;
using deduction::DeductionFacade;
using deduction::DeductionListQueryRequest;
using deduction::DeductionListQueryResponse;
namespace fcdeduction {
namespace facade {
class DeductionFacadeImpl final : public DeductionFacade::Service {
 public:
  // 开通扣费服务
  grpc::Status CreateDeductionService(grpc::ServerContext* context,
                                      const DeduceRequest* request,
                                      DeduceResponse* response) override;
  // 关闭扣费信息
  grpc::Status CloseDeductionService(grpc::ServerContext* context,
                                     const DeduceRequest* request,
                                     DeduceResponse* response) override;
  // 查询扣费服务列表
  grpc::Status QueryDeductionListByUserIdAndArType(
      grpc::ServerContext* context, const DeductionListQueryRequest* request,
      DeductionListQueryResponse* response) override;
};
}  // namespace facade
}  // namespace fcdeduction
#endif