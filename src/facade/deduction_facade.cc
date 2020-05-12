#include "deduction_facade.h"

#include <chrono>
#include <cstdint>
#include <map>

#include "spdlog/spdlog.h"
#include "src/dal/arrangement_dao.h"
#include "src/dal/product_dao.h"
#include "src/dal/user_ar_rel_dao.h"
#include "src/dal/user_ar_rel_do.h"
#include "src/dal/user_dao.h"
#include "src/facade/user_facade.h"
#include "src/manager/snowflake_id_manager.h"
#include "src/util/constant.h"
#include "src/util/rel_status_enum.h"
#include "src/util/response_enum.h"

void setReponse(DeduceResponse *response,
                const fcdeduction::util::ResponseEnum &respEnum) {
  response->set_status(respEnum.getStatus());
  response->set_code(respEnum.getCode());
  response->set_desc(respEnum.getDesc());
}
void setReponse(DeductionListQueryResponse *response,
                const fcdeduction::util::ResponseEnum &respEnum) {
  response->set_status(respEnum.getStatus());
  response->set_code(respEnum.getCode());
  response->set_desc(respEnum.getDesc());
}

fcdeduction::dataobject::UserArRel generateRel(const std::string &arNo,
                                               const std::string &pdCode,
                                               const std::string &userId) {
  // TODO 目前的数据库连接管理其实是存在问题的, 将connection放置在dao内部,
  // 新建一个dao就创建一个连接 然后在dao超出作用域之外, dao被销毁,
  // connection也被销毁, 效率着实不高.
  fcdeduction::dao::ArrangementDao arDao;
  fcdeduction::dao::ProductDao productDao;
  fcdeduction::dao::UserDao userDao;
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
  fcdeduction::dao::ArrangementDao arDao;
  fcdeduction::dao::ProductDao productDao;
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
                               request->pdcode())) {
    setReponse(response, fcdeduction::util::ResponseEnum::PRODUCT_NOT_EXIST);
    return false;
  }
  // 判断合约是否存在
  std::string arNo = request->arno();
  if (!arDao.arExist(fcdeduction::util::TNT_INST_ID, arNo)) {
    setReponse(response,
               fcdeduction::util::ResponseEnum::ARRANGEMENT_NOT_EXIST);
    return false;
  }
  return true;
}
bool userArRelExist(grpc::ServerContext *context, const DeduceRequest *request,
                    DeduceResponse *response) {
  fcdeduction::dao::UserArRelDao arRelDao;
  std::string arNo = request->arno();
  // 判断合约-产品-用户绑定关系是否存在.
  return arRelDao.userArRelExist(fcdeduction::util::TNT_INST_ID, arNo,
                                 request->pdcode(), request->userid());
}

grpc::Status fcdeduction::facade::DeductionFacadeImpl::CreateDeductionService(
    grpc::ServerContext *context, const DeduceRequest *request,
    DeduceResponse *response) {
  spdlog::info(
      "start: 开通服务, request.token:{0}, request.userId, request.pdCode, "
      "request.ArNo",
      request->token(), request->userid(), request->pdcode(), request->arno());
  fcdeduction::dao::UserArRelDao arRelDao;
  if (!parameterCheck(context, request, response)) {
    return grpc::Status::OK;
  }

  if (userArRelExist(context, request, response)) {
    setReponse(response,
               fcdeduction::util::ResponseEnum::PRODUCT_DUPLICATE_BIND);
    return grpc::Status::OK;
  }

  // 新增绑定关系
  std::string arNo = request->arno();
  fcdeduction::dataobject::UserArRel rel =
      generateRel(arNo, request->pdcode(), request->userid());
  arRelDao.addUserArRel(fcdeduction::util::TNT_INST_ID, rel);
  setReponse(response, fcdeduction::util::ResponseEnum::SUCCESS);

  return grpc::Status::OK;
}

grpc::Status fcdeduction::facade::DeductionFacadeImpl::CloseDeductionService(
    grpc::ServerContext *context, const DeduceRequest *request,
    DeduceResponse *response) {
  spdlog::info(
      "start: 关闭服务, request.token:{0}, request.userId:{1}, "
      "request.pdCode{2}, "
      "request.ArNo{3}",
      request->token(), request->userid(), request->pdcode(), request->arno());
  fcdeduction::dao::UserArRelDao arRelDao;
  if (!parameterCheck(context, request, response)) {
    return grpc::Status::OK;
  }
  // 判断合约-产品-用户绑定关系是否存在.
  if (!userArRelExist(context, request, response)) {
    setReponse(response, fcdeduction::util::ResponseEnum::PRODUCT_NOT_BIND);
    return grpc::Status::OK;
  }

  // 删除合约-产品-用户绑定关系
  arRelDao.deleteByUserIdArNoAndPdCode(fcdeduction::util::TNT_INST_ID,
                                       request->arno(), request->pdcode(),
                                       request->userid());
  return grpc::Status::OK;
}
grpc::Status
fcdeduction::facade::DeductionFacadeImpl::QueryDeductionListByUserIdAndArType(
    grpc::ServerContext *context, const DeductionListQueryRequest *request,
    DeductionListQueryResponse *response) {
  spdlog::info(
      "start: 查询服务列表, request.token:{0}, request.userId:{1},request.ArNo {2} ",
      request->token(),
      request->userid(), request->arno());
  fcdeduction::dao::ArrangementDao arDao;
  fcdeduction::dao::UserArRelDao arRelDao;

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
    return grpc::Status::OK;
  }

  // 判断合约是否存在
  std::string arNo = request->arno();
  if (!arDao.arExist(fcdeduction::util::TNT_INST_ID, arNo)) {
    setReponse(response,
               fcdeduction::util::ResponseEnum::ARRANGEMENT_NOT_EXIST);
    return grpc::Status::OK;
  }
  // TODO 这个值为空校验.
  unsigned int pageIndex = request->pageindex();
  unsigned int pageSize = request->pagesize();
  std::vector<fcdeduction::dataobject::UserArRel> lists =
      arRelDao.selectListByUserIdAndArNo(fcdeduction::util::TNT_INST_ID,
                                         request->arno(), request->userid(),
                                         pageIndex, pageSize);
  for (auto const &rel : lists) {
    SimpliedProductInfo *info = response->add_simpliedproductinfo();
    info->set_productcode(rel.pdCode);
    info->set_productname(rel.pdName);
    info->set_proudctorgname(rel.pdOrgName);
  }
  // 查询合约-产品-用户绑定关系
  return grpc::Status::OK;
}