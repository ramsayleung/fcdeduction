#include "deduction.grpc.pb.h"
#include <iostream>
#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>

using deduction::DeductionFacade;
using deduction::DeduceRequest;
using deduction::DeduceResponse;
class DeductionFacadeImpl final: public DeductionFacade::Service{
    public:
    grpc::Status CreateDeductionService(grpc::ServerContext *context, const DeduceRequest *request, DeduceResponse *response)override{
       // 判断是否已经登录  

       // 判断产品是否存在

       // 判断合约是否存在

       // 判断合约-产品-用户绑定关系是否存在.

       // 新增绑定关系

       return grpc::Status::OK;
    }
};