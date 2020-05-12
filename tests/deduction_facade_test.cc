#include "src/facade/deduction_facade.h"

#include "gtest/gtest.h"
#include "src/dal/arrangement_dao.h"
#include "src/dal/product_dao.h"
#include "src/dal/user_ar_rel_dao.h"
#include "src/dal/user_ar_rel_do.h"
#include "src/dal/user_dao.h"
#include "src/manager/redis_manager.h"
#include "src/manager/snowflake_id_manager.h"
#include "src/manager/token_manager.h"
#include "src/proto/deduction.grpc.pb.h"
#include "src/util/constant.h"
#include "src/util/response_enum.h"

static fcdeduction::dao::UserArRelDao relDao;

static fcdeduction::dao::UserDao userDao;

static fcdeduction::dao::ArrangementDao arDao;

static fcdeduction::dao::ProductDao productDao;

static fcdeduction::manager::RedisManager redisManager;

static fcdeduction::manager::SnowFlakeIdManager idManager(12, 24);

static fcdeduction::manager::TokenManager tokenManager;

static fcdeduction::facade::DeductionFacadeImpl service;

void insertUser(const std::string& userId) {
  fcdeduction::dataobject::User user;
  user.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  user.userId = userId;
  user.userType = "1";
  user.userName = "ramsay";
  user.gmtCreate = std::chrono::system_clock::now();
  user.gmtModified = std::chrono::system_clock::now();
  userDao.deleteUser(fcdeduction::util::getTntInstIdByEnv(), user.userId);
  userDao.insertUser(user);
}

void deleteUser(const std::string& userId) {
  userDao.deleteUser(fcdeduction::util::getTntInstIdByEnv(), userId);
}

void insertProduct(const std::string& pdCode) {
  fcdeduction::dataobject::Product product;
  product.gmtCreate = std::chrono::system_clock::now();
  product.gmtModified = std::chrono::system_clock::now();
  product.memo = "memo";
  product.pdName = "test product";
  product.pdDesc = "test product desc";
  product.pdOrgName = "org of test product";
  product.pdCode = pdCode;
  product.tntInstId = fcdeduction::util::getTntInstIdByEnv();

  productDao.insertProduct(product);
}

void deleteProduct(const std::string& pdCode) {
  productDao.deleteProductByPdCode(fcdeduction::util::getTntInstIdByEnv(),
                                   pdCode);
}

void insertAr(const std::string& arNo) {
  fcdeduction::dataobject::Arrangement ar;
  ar.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  ar.arName = "test ar";
  ar.arNumber = arNo;
  ar.arVersion = "1";
  ar.memo = "desc";
  ar.properties = R"([{"name":"signValue", "key":"account","value":"change"}])";
  arDao.deleteAr(ar.tntInstId, ar.arNumber);
  arDao.insertAr(ar);
}

void deleteAr(const std::string& arNo) {
  fcdeduction::dataobject::Arrangement ar;
  ar.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  ar.arName = "ar name";
  ar.arNumber = arNo;
  ar.arVersion = "1";
  ar.memo = "remark";
  ar.properties =
      R"([{"name":"sign account", "key":"account","value":"change"}])";
  arDao.deleteAr(ar.tntInstId, ar.arNumber);
}

void insertUserArRel(const std::string& arNo, const std::string& pdCode,
                     const std::string& userId) {
  fcdeduction::dataobject::UserArRel rel;
  rel.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  rel.pdCode = pdCode;
  rel.relId = idManager.nextId();
  rel.pdName = "test product";
  rel.userId = userId;
  rel.relStatus = "1";
  rel.pdOrgName = "org of test product";
  rel.arName = "deduction ar";
  rel.arNo = arNo;
  rel.gmtCreate = std::chrono::system_clock::now();
  rel.gmtModified = std::chrono::system_clock::now();
  relDao.addUserArRel(rel.tntInstId, rel);
}

void deleteUserArRel(const std::string& arNo, const std::string& pdCode,
                     const std::string& userId) {
  relDao.deleteByUserIdArNoAndPdCode(fcdeduction::util::getTntInstIdByEnv(),
                                     arNo, pdCode, userId);
}

void deleteTokenValue(const std::string& token) { redisManager.del(token); }

TEST(FACADE_TEST, CREATE_SERVICE_TEST) {
  using namespace fcdeduction::facade;
  using namespace fcdeduction::util;
  const std::string userId = std::to_string(idManager.nextId());
  const std::string pdCode = std::to_string(idManager.nextId());
  const std::string arNo = std::to_string(idManager.nextId());

  DeduceRequest request;
  DeduceResponse response;
  grpc::ServerContext context;
  const std::string token = std::to_string(idManager.nextId());
  request.set_arno(arNo);
  request.set_pdcode(pdCode);
  request.set_userid(userId);
  request.set_token(token);
  // 用户未登录
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::USER_NOT_LOGIN.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::USER_NOT_LOGIN.getStatus());

  // 设置token
  insertUser(userId);
  tokenManager.addUserToken(token, request.userid());

  // 产品不存在.
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::PRODUCT_NOT_EXIST.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::PRODUCT_NOT_EXIST.getStatus());

  insertProduct(pdCode);

  //合约不存在
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::ARRANGEMENT_NOT_EXIST.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::ARRANGEMENT_NOT_EXIST.getStatus());
  insertAr(arNo);

  insertUserArRel(arNo, pdCode, userId);
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::PRODUCT_DUPLICATE_BIND.getCode());
  EXPECT_EQ(response.status(),
            ResponseEnum::PRODUCT_DUPLICATE_BIND.getStatus());

  deleteUserArRel(arNo, pdCode, userId);
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::SUCCESS.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::SUCCESS.getStatus());
  EXPECT_TRUE(relDao.userArRelExist(fcdeduction::util::getTntInstIdByEnv(),
                                    request.arno(), request.pdcode(),
                                    request.userid()));
  deleteTokenValue(token);
  deleteTokenValue(request.userid());
  deleteProduct(pdCode);
  deleteUser(userId);
  deleteUserArRel(arNo, pdCode, userId);
  deleteAr(arNo);
}

TEST(FACADE_TEST, CLOSE_SERVICE_TEST) {
  using namespace fcdeduction::util;
  const std::string userId = std::to_string(idManager.nextId());
  const std::string pdCode = std::to_string(idManager.nextId());
  const std::string arNo = std::to_string(idManager.nextId());
  DeduceRequest request;
  DeduceResponse response;
  grpc::ServerContext context;
  const std::string token = std::to_string(idManager.nextId());
  request.set_arno(arNo);
  request.set_pdcode(pdCode);
  request.set_userid(userId);
  request.set_token(token);
  // 用户未登录
  service.CloseDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::USER_NOT_LOGIN.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::USER_NOT_LOGIN.getStatus());

  // 设置token
  insertUser(userId);
  tokenManager.addUserToken(token, request.userid());

  // 产品不存在.
  service.CloseDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::PRODUCT_NOT_EXIST.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::PRODUCT_NOT_EXIST.getStatus());

  insertProduct(pdCode);

  //合约不存在
  service.CloseDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::ARRANGEMENT_NOT_EXIST.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::ARRANGEMENT_NOT_EXIST.getStatus());

  // 用户-合约-产品关系不存在
  insertAr(arNo);
  service.CloseDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::PRODUCT_NOT_BIND.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::PRODUCT_NOT_BIND.getStatus());

  // 正常请求
  insertUserArRel(arNo, pdCode, userId);
  EXPECT_TRUE(relDao.userArRelExist(fcdeduction::util::getTntInstIdByEnv(),
                                    request.arno(), request.pdcode(),
                                    request.userid()));
  spdlog::info("开始正常请求");
  service.CloseDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::SUCCESS.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::SUCCESS.getStatus());

  EXPECT_TRUE(!relDao.userArRelExist(fcdeduction::util::getTntInstIdByEnv(),
                                     request.arno(), request.pdcode(),
                                     request.userid()));
  deleteTokenValue(token);
  deleteTokenValue(request.userid());

  deleteProduct(pdCode);
  deleteUser(userId);
  deleteUserArRel(arNo, pdCode, userId);
  deleteAr(arNo);
}
