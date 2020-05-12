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

// TODO 目前的数据库连接管理其实是存在问题的, 将connection放置在dao内部,
// 新建一个dao就创建一个连接 然后在dao超出作用域之外, dao被销毁,
// connection也被销毁, 效率着实不高.
// 目前将其当成global variable 来规避效率问题.
static fcdeduction::dao::ArrangementDao arDao;

static fcdeduction::dao::ProductDao productDao;

static fcdeduction::dao::UserDao userDao;

static fcdeduction::dao::UserArRelDao arRelDao;

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
  std::optional<fcdeduction::dataobject::Arrangement> ar =
      arDao.selectByArNo(fcdeduction::util::getTntInstIdByEnv(), arNo);

  std::optional<fcdeduction::dataobject::Product> pd =
      productDao.selectByPdCode(fcdeduction::util::getTntInstIdByEnv(), pdCode);

  std::optional<fcdeduction::dataobject::User> user =
      userDao.selectByUserId(fcdeduction::util::getTntInstIdByEnv(), userId);

  fcdeduction::dataobject::UserArRel rel;
  fcdeduction::manager::SnowFlakeIdManager idManager(
      fcdeduction::util::DATA_CENTER_ID, fcdeduction::util::MACHINE_ID);
  rel.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  rel.relId = std::to_string(idManager.nextId());
  rel.arName = ar.value().arName;
  rel.arNo = ar.value().arNumber;
  rel.pdCode = pd.value().pdCode;
  rel.pdName = pd.value().pdName;
  rel.pdOrgName = pd.value().pdOrgName;
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
  if (!productDao.productExist(fcdeduction::util::getTntInstIdByEnv(),
                               request->pdcode())) {
    spdlog::info("end: 产品不存在, request.pdCode:{0}", request->pdcode());
    setReponse(response, fcdeduction::util::ResponseEnum::PRODUCT_NOT_EXIST);
    return false;
  }
  // 判断合约是否存在
  std::string arNo = request->arno();
  if (!arDao.arExist(fcdeduction::util::getTntInstIdByEnv(), arNo)) {
    spdlog::info("end: 合约不存在, request.arno:{0}", request->arno());
    setReponse(response,
               fcdeduction::util::ResponseEnum::ARRANGEMENT_NOT_EXIST);
    return false;
  }
  return true;
}
bool userArRelExist(grpc::ServerContext *context, const DeduceRequest *request,
                    DeduceResponse *response) {
  std::string arNo = request->arno();
  // 判断合约-产品-用户绑定关系是否存在.
  return arRelDao.userArRelExist(fcdeduction::util::getTntInstIdByEnv(), arNo,
                                 request->pdcode(), request->userid());
}

grpc::Status fcdeduction::facade::DeductionFacadeImpl::CreateDeductionService(
    grpc::ServerContext *context, const DeduceRequest *request,
    DeduceResponse *response) {
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  spdlog::info(
      "start: 开通服务, request.token:{0}, request.userId:{1}, "
      "request.pdCode:{2}, "
      "request.ArNo:{3}",
      request->token(), request->userid(), request->pdcode(), request->arno());
  if (!parameterCheck(context, request, response)) {
    return grpc::Status::OK;
  }

  if (userArRelExist(context, request, response)) {
    spdlog::warn(
        "end: 用户-合约-产品绑定关系已存在, request.token:{0}, "
        "request.userId:{1}, "
        "request.pdCode:{2}, "
        "request.ArNo:{3}",
        request->token(), request->userid(), request->pdcode(),
        request->arno());
    setReponse(response,
               fcdeduction::util::ResponseEnum::PRODUCT_DUPLICATE_BIND);
    return grpc::Status::OK;
  }

  // 新增绑定关系
  std::string arNo = request->arno();
  fcdeduction::dataobject::UserArRel rel =
      generateRel(arNo, request->pdcode(), request->userid());
  arRelDao.addUserArRel(fcdeduction::util::getTntInstIdByEnv(), rel);
  setReponse(response, fcdeduction::util::ResponseEnum::SUCCESS);

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
          .count();
  spdlog::info(
      "end: 开通服务成功, request.token:{0}, request.userId:{1}, "
      "request.pdCode:{2}, "
      "request.ArNo{3}, 耗时:{4}ms",
      request->token(), request->userid(), request->pdcode(), request->arno(),
      elapsed);
  return grpc::Status::OK;
}

grpc::Status fcdeduction::facade::DeductionFacadeImpl::CloseDeductionService(
    grpc::ServerContext *context, const DeduceRequest *request,
    DeduceResponse *response) {
  std::chrono::steady_clock::time_point begin =
      std::chrono::steady_clock::now();
  spdlog::info(
      "start: 关闭服务, request.token:{0}, request.userId:{1}, "
      "request.pdCode:{2}, "
      "request.ArNo:{3}",
      request->token(), request->userid(), request->pdcode(), request->arno());
  fcdeduction::dao::UserArRelDao arRelDao;
  if (!parameterCheck(context, request, response)) {
    return grpc::Status::OK;
  }
  // 判断合约-产品-用户绑定关系是否存在.
  if (!userArRelExist(context, request, response)) {
    spdlog::warn(
        "end: 用户-合约-产品绑定关系未存在, request.token:{0}, "
        "request.userId:{1}, "
        "request.pdCode:{2}, "
        "request.ArNo:{3}",
        request->token(), request->userid(), request->pdcode(),
        request->arno());
    setReponse(response, fcdeduction::util::ResponseEnum::PRODUCT_NOT_BIND);
    return grpc::Status::OK;
  }

  // 删除合约-产品-用户绑定关系
  arRelDao.deleteByUserIdArNoAndPdCode(fcdeduction::util::getTntInstIdByEnv(),
                                       request->arno(), request->pdcode(),
                                       request->userid());
  setReponse(response, fcdeduction::util::ResponseEnum::SUCCESS);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
          .count();
  spdlog::info(
      "end: 关闭服务成功, request.token:{0}, request.userId:{1}, "
      "request.pdCode:{2}, "
      "request.ArNo:{3}, 耗时:{4}ms",
      request->token(), request->userid(), request->pdcode(), request->arno(),
      elapsed);
  return grpc::Status::OK;
}

grpc::Status
fcdeduction::facade::DeductionFacadeImpl::QueryDeductionListByUserIdAndArType(
    grpc::ServerContext *context, const DeductionListQueryRequest *request,
    DeductionListQueryResponse *response) {
  // TODO 实际项目中, 查询数据通常都是查询缓存, 在增/删操作同步缓存.
  // 本次数据查询都是直接查库的.
  auto begin = std::chrono::steady_clock::now();
  spdlog::info(
      "start: 查询服务列表, request.token:{0}, request.userId:{1},request.ArNo "
      "{2} ",
      request->token(), request->userid(), request->arno());

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
  if (!arDao.arExist(fcdeduction::util::getTntInstIdByEnv(), arNo)) {
    setReponse(response,
               fcdeduction::util::ResponseEnum::ARRANGEMENT_NOT_EXIST);
    return grpc::Status::OK;
  }
  // TODO 这个怎么做空值校验?
  unsigned int pageIndex = request->pageindex();
  unsigned int pageSize = request->pagesize();
  std::vector<fcdeduction::dataobject::UserArRel> lists =
      arRelDao.selectListByUserIdAndArNo(fcdeduction::util::getTntInstIdByEnv(),
                                         request->arno(), request->userid(),
                                         pageIndex, pageSize);
  for (auto const &rel : lists) {
    SimpliedProductInfo *info = response->add_simpliedproductinfo();
    info->set_productcode(rel.pdCode);
    info->set_productname(rel.pdName);
    info->set_proudctorgname(rel.pdOrgName);
  }
  setReponse(response, fcdeduction::util::ResponseEnum::SUCCESS);

  auto end = std::chrono::steady_clock::now();
  auto elapsed =
      std::chrono::duration_cast<std::chrono::milliseconds>(end - begin)
          .count();
  spdlog::info(
      "end: 查询服务列表, request.token:{0}, request.userId:{1},request.ArNo "
      "{2}, 耗时:{3}ms",
      request->token(), request->userid(), request->arno(), elapsed);
  // 查询合约-产品-用户绑定关系
  return grpc::Status::OK;
}