#include "deduction_facade.h"

#include "src/dal/arrangement_dao.h"
#include "src/dal/product_dao.h"
#include "src/facade/user_facade.h"
void setReponse(DeduceResponse *response,
                const fcdeduction::util::ResponseEnum &respEnum) {
  response->set_status(respEnum.getStatus());
  response->set_code(respEnum.getCode());
  response->set_desc(respEnum.getDesc());
}
bool parameterCheck(grpc::ServerContext *context, const DeduceRequest *request,
                    DeduceResponse *response) {
  // 判断是否已经登录

  // 判断产品是否存在

  // 判断合约是否存在
  return false;
}
grpc::Status fcdeduction::facade::DeductionFacadeImpl::CreateDeductionService(
    grpc::ServerContext *context, const DeduceRequest *request,
    DeduceResponse *response) {
  // 判断是否已经登录
  // 判断产品是否存在
  // 判断合约是否存在
  if (parameterCheck(context, request, response)) {
    return grpc::Status::OK;
  }

  // 判断合约-产品-用户绑定关系是否存在.

  // 新增绑定关系

  return grpc::Status::OK;
}

grpc::Status fcdeduction::facade::DeductionFacadeImpl::CloseDeductionService(
    grpc::ServerContext *context, const DeduceRequest *request,
    DeduceResponse *response) {
  // 判断是否已经登录

  // 判断产品是否存在

  // 判断合约是否存在

  // 判断合约-产品-用户绑定关系是否存在.

  // 删除合约-产品-用户绑定关系

  return grpc::Status::OK;
}
grpc::Status
fcdeduction::facade::DeductionFacadeImpl::QueryDeductionListByUserIdAndArType(
    grpc::ServerContext *context, const DeductionListQueryRequest *request,
    DeductionListQueryResponse *response) {
  // 判断是否已经登录

  // 判断合约是否存在

  // 查询合约-产品-用户绑定关系
  return grpc::Status::OK;
}