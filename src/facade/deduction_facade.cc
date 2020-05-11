#include "deduction_facade.h"

#include <chrono>
#include <map>

#include "src/dal/arrangement_dao.h"
#include "src/dal/product_dao.h"
#include "src/dal/user_ar_rel_dao.h"
#include "src/dal/user_ar_rel_do.h"
#include "src/dal/user_dao.h"
#include "src/facade/user_facade.h"
#include "src/manager/snowflake_id_manager.h"
#include "src/util/ar_code_enum.h"
#include "src/util/constant.h"
#include "src/util/rel_status_enum.h"
#include "src/util/response_enum.h"
fcdeduction::dao::UserArRelDao arRelDao;
fcdeduction::dao::ArrangementDao arDao;
fcdeduction::dao::ProductDao productDao;
fcdeduction::dao::UserDao userDao;
void setReponse(DeduceResponse *response,
                const fcdeduction::util::ResponseEnum &respEnum) {
  response->set_status(respEnum.getStatus());
  response->set_code(respEnum.getCode());
  response->set_desc(respEnum.getDesc());
}

fcdeduction::dataobject::UserArRel generateRel(const std::string &arNo,
                                               const std::string &pdCode,
                                               const std::string &userId) {
  std::optional<fcdeduction::dataobject::Arrangement> ar =
      arDao.selectByArNo(fcdeduction::util::TNT_INST_ID, arNo);

  std::optional<fcdeduction::dataobject::Product> pd =
      productDao.selectByPdCode(fcdeduction::util::TNT_INST_ID, pdCode);
  std::optional<fcdeduction::dataobject::User> user =
      userDao.selectByUserId(fcdeduction::util::TNT_INST_ID, userId);
  fcdeduction::dataobject::UserArRel rel;
  fcdeduction::manager::SnowFlakeIdManager idManager(
      fcdeduction::util::DATA_CENTER_ID, fcdeduction::util::MACHINE_ID);
  rel.tntInstId = fcdeduction::util::TNT_INST_ID;
  rel.relId = idManager.nextId();
  rel.arName = ar.value().arName;
  rel.arNo = ar.value().arNumber;
  rel.pdCode = pd.value().pdCode;
  rel.pdName = pd.value().pdName;
  rel.userId = user.value().userId;
  rel.relStatus =
      fcdeduction::util::enumToString(fcdeduction::util::RelStatusEnum::ACTIVE);
  rel.gmtCreate = std::chrono::system_clock::now();
  rel.gmtModified = std::chrono::system_clock::now();
  return rel;
}

// 进行必要的参数校验, false代表校验失败, true代表校验成功
bool parameterCheck(grpc::ServerContext *context, const DeduceRequest *request,
                    DeduceResponse *response) {
  // 判断是否已经登录
  fcdeduction::facade::UserFacadeImpl userService;
  LoginSessionValidateRequest validateRequest;
  validateRequest.set_token(request->token());
  LoginSessionValidateResponse validateResponse;
  userService.validateLoginSession(context, &validateRequest,
                                   &validateResponse);
  if (validateResponse.status() !=
      fcdeduction::util::ResponseEnum::SUCCESS.getStatus()) {
    setReponse(response, fcdeduction::util::ResponseEnum::USER_NOT_LOGIN);
    return false;
  }
  // 判断产品是否存在
  if (!productDao.productExist(fcdeduction::util::TNT_INST_ID,
                               request->productcode())) {
    setReponse(response, fcdeduction::util::ResponseEnum::PRODUCT_NOT_EXIST);
    return false;
  }
  // 判断合约是否存在
  std::map<std::string, std::string> enumMap =
      fcdeduction::util::ArCodeEnum::enumMap();
  if (enumMap.find(request->arrangementtype()) == enumMap.end()) {
    setReponse(response,
               fcdeduction::util::ResponseEnum::ARRANGEMENT_NOT_EXIST);
    return false;
  }
  std::string arNo = enumMap[request->arrangementtype()];
  if (!arDao.arExist(fcdeduction::util::TNT_INST_ID, arNo)) {
    setReponse(response,
               fcdeduction::util::ResponseEnum::ARRANGEMENT_NOT_EXIST);
    return false;
  }
  return true;
}
bool userArRelExist(grpc::ServerContext *context, const DeduceRequest *request,
                    DeduceResponse *response) {
  std::map<std::string, std::string> enumMap =
      fcdeduction::util::ArCodeEnum::enumMap();
  std::string arNo = enumMap[request->arrangementtype()];
  // 判断合约-产品-用户绑定关系是否存在.
  return arRelDao.userArRelExist(fcdeduction::util::TNT_INST_ID, arNo,
                                 request->productcode(), request->userid());
}

grpc::Status fcdeduction::facade::DeductionFacadeImpl::CreateDeductionService(
    grpc::ServerContext *context, const DeduceRequest *request,
    DeduceResponse *response) {
  if (!parameterCheck(context, request, response)) {
    return grpc::Status::OK;
  }

  if (userArRelExist(context, request, response)) {
    setReponse(response,
               fcdeduction::util::ResponseEnum::PRODUCT_DUPLICATE_BIND);
    return grpc::Status::OK;
  }

  // 新增绑定关系
  std::map<std::string, std::string> enumMap =
      fcdeduction::util::ArCodeEnum::enumMap();
  std::string arNo = enumMap[request->arrangementtype()];
  fcdeduction::dataobject::UserArRel rel =
      generateRel(arNo, request->productcode(), request->userid());
  arRelDao.addUserArRel(fcdeduction::util::TNT_INST_ID, rel);
  setReponse(response, fcdeduction::util::ResponseEnum::SUCCESS);

  return grpc::Status::OK;
}

grpc::Status fcdeduction::facade::DeductionFacadeImpl::CloseDeductionService(
    grpc::ServerContext *context, const DeduceRequest *request,
    DeduceResponse *response) {
  if (!parameterCheck(context, request, response)) {
    return grpc::Status::OK;
  }
  // 判断合约-产品-用户绑定关系是否存在.
  if (!userArRelExist(context, request, response)) {
    setReponse(response, fcdeduction::util::ResponseEnum::PRODUCT_NOT_BIND);
    return grpc::Status::OK;
  }
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