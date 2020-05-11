#include "src/facade/deduction_facade.h"

#include "gtest/gtest.h"
#include "src/dal/arrangement_dao.h"
#include "src/dal/product_dao.h"
#include "src/dal/user_ar_rel_dao.h"
#include "src/dal/user_ar_rel_do.h"
#include "src/dal/user_dao.h"
#include "src/manager/snowflake_id_manager.h"
#include "src/manager/token_manager.h"
#include "src/proto/deduction.grpc.pb.h"
#include "src/util/constant.h"
#include "src/util/response_enum.h"

void insertUser() {
  fcdeduction::dao::UserDao userDao;
  fcdeduction::dataobject::User user;
  user.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  user.userId = "userId000";
  user.userType = "1";
  user.userName = "ramsay";
  user.gmtCreate = std::chrono::system_clock::now();
  user.gmtModified = std::chrono::system_clock::now();
  userDao.deleteUser(fcdeduction::util::TEST_TNT_INST_ID, user.userId);
  userDao.insertUser(user);
}
void deleteUser() {
  fcdeduction::dao::UserDao userDao;
  fcdeduction::dataobject::User user;
  user.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  user.userId = "userId000";
  user.userType = "1";
  user.userName = "ramsay";
  user.gmtCreate = std::chrono::system_clock::now();
  user.gmtModified = std::chrono::system_clock::now();
  userDao.deleteUser(fcdeduction::util::TEST_TNT_INST_ID, user.userId);
}

void insertProduct() {
  fcdeduction::dataobject::Product product;
  product.gmtCreate = std::chrono::system_clock::now();
  product.gmtModified = std::chrono::system_clock::now();
  product.memo = "备注";
  product.pdName = "测试产品";
  product.pdDesc = "测试产品描述";
  product.pdOrgName = "主体信息";
  product.pdCode = "pdcode00001";
  product.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;

  fcdeduction::dao::ProductDao productDao;
  productDao.deleteProductByPdCode(product.tntInstId, product.pdCode);
  productDao.insertProduct(product);
}

void insertAr() {
  fcdeduction::dataobject::Arrangement ar;
  ar.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  ar.arName = "测试合约";
  ar.arNumber = "ar000001";
  ar.arVersion = "1";
  ar.memo = "备注";
  ar.properties = R"([{"name":"签约账号", "key":"account","value":"零钱"}])";
  fcdeduction::dao::ArrangementDao dao;
  dao.deleteAr(ar.tntInstId, ar.arNumber);
  dao.insertAr(ar);
}

void deleteAr() {
  fcdeduction::dataobject::Arrangement ar;
  ar.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  ar.arName = "测试合约";
  ar.arNumber = "ar000001";
  ar.arVersion = "1";
  ar.memo = "备注";
  ar.properties = R"([{"name":"签约账号", "key":"account","value":"零钱"}])";
  fcdeduction::dao::ArrangementDao dao;
  dao.deleteAr(ar.tntInstId, ar.arNumber);
}

void deleteProduct() {
  fcdeduction::dataobject::Arrangement ar;
  ar.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  ar.arName = "测试合约";
  ar.arNumber = "ar000001";
  ar.arVersion = "1";
  ar.memo = "备注";
  ar.properties = R"([{"name":"签约账号", "key":"account","value":"零钱"}])";
  fcdeduction::dao::ArrangementDao dao;
  dao.deleteAr(ar.tntInstId, ar.arNumber);
}
void insertUserArRel() {
  fcdeduction::dataobject::UserArRel rel;
  rel.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  rel.pdCode = "pdcode00001";
  rel.relId = "00000001";
  rel.pdName = "测试";
  rel.userId = "userId000";
  rel.relStatus = "1";
  rel.pdOrgName = "测试机构";
  rel.arName = "扣费合约";
  rel.arNo = "ar000001";
  rel.gmtCreate = std::chrono::system_clock::now();
  rel.gmtModified = std::chrono::system_clock::now();
  fcdeduction::dao::UserArRelDao relDao;
  relDao.deleteByUserIdArNoAndPdCode(rel.tntInstId, rel.arNo, rel.pdCode,
                                     rel.userId);
  relDao.addUserArRel(rel.tntInstId, rel);
}
void deleteUserArRel() {
  fcdeduction::dataobject::UserArRel rel;
  rel.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
  rel.pdCode = "pdcode00001";
  rel.relId = "00000001";
  rel.pdName = "测试";
  rel.userId = "userId000";
  rel.relStatus = "1";
  rel.pdOrgName = "测试机构";
  rel.arName = "扣费合约";
  rel.arNo = "ar000001";
  rel.gmtCreate = std::chrono::system_clock::now();
  rel.gmtModified = std::chrono::system_clock::now();
  fcdeduction::dao::UserArRelDao relDao;
  relDao.deleteByUserIdArNoAndPdCode(rel.tntInstId, rel.arNo, rel.pdCode,
                                     rel.userId);
}

TEST(FACADE_TEST, CREATE_SERVICE_TEST) {
  using namespace fcdeduction::manager;
  using namespace fcdeduction::facade;
  using namespace fcdeduction::util;
  DeductionFacadeImpl service;
  DeduceRequest request;
  DeduceResponse response;
  grpc::ServerContext context;
  SnowFlakeIdManager idManager(123, 321);
  const std::string token = std::to_string(idManager.nextId());
  request.set_arno("ar000001");
  request.set_pdcode("pdcode00001");
  request.set_userid("userId000");
  request.set_token(token);
  // 用户未登录
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::USER_NOT_LOGIN.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::USER_NOT_LOGIN.getStatus());

  // 设置token
  TokenManager tokenManager;
  insertUser();
  tokenManager.addUserToken(token, request.userid());

  // 产品不存在.
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::PRODUCT_NOT_EXIST.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::PRODUCT_NOT_EXIST.getStatus());

  insertProduct();

  //合约不存在
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::ARRANGEMENT_NOT_EXIST.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::ARRANGEMENT_NOT_EXIST.getStatus());
  insertAr();

  insertUserArRel();
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::PRODUCT_DUPLICATE_BIND.getCode());
  EXPECT_EQ(response.status(),
            ResponseEnum::PRODUCT_DUPLICATE_BIND.getStatus());
  deleteUserArRel();
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::SUCCESS.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::SUCCESS.getStatus());
  fcdeduction::dao::UserArRelDao relDao;
  EXPECT_TRUE(relDao.userArRelExist(fcdeduction::util::TEST_TNT_INST_ID,
                                    request.arno(), request.pdcode(),
                                    request.userid()));
  deleteProduct();
  deleteUser();
  deleteUserArRel();
  deleteAr();
}

TEST(FACADE_TEST, CLOSE_SERVICE_TEST) {
  using namespace fcdeduction::manager;
  using namespace fcdeduction::facade;
  using namespace fcdeduction::util;
  DeductionFacadeImpl service;
  DeduceRequest request;
  DeduceResponse response;
  grpc::ServerContext context;
  SnowFlakeIdManager idManager(123, 321);
  const std::string token = std::to_string(idManager.nextId());
  request.set_arno("ar000001");
  request.set_pdcode("pdcode00001");
  request.set_userid("userId000");
  request.set_token(token);
  // 用户未登录
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::USER_NOT_LOGIN.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::USER_NOT_LOGIN.getStatus());

  // 设置token
  TokenManager tokenManager;
  insertUser();
  tokenManager.addUserToken(token, request.userid());

  // 产品不存在.
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::PRODUCT_NOT_EXIST.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::PRODUCT_NOT_EXIST.getStatus());

  insertProduct();

  //合约不存在
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::ARRANGEMENT_NOT_EXIST.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::ARRANGEMENT_NOT_EXIST.getStatus());
  insertAr();

  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::PRODUCT_NOT_BIND.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::PRODUCT_NOT_BIND.getStatus());

  insertUserArRel();
  service.CreateDeductionService(&context, &request, &response);
  EXPECT_EQ(response.code(), ResponseEnum::SUCCESS.getCode());
  EXPECT_EQ(response.status(), ResponseEnum::SUCCESS.getStatus());

  fcdeduction::dao::UserArRelDao relDao;
  EXPECT_TRUE(!relDao.userArRelExist(fcdeduction::util::TEST_TNT_INST_ID,
                                     request.arno(), request.pdcode(),
                                     request.userid()));
  deleteProduct();
  deleteUser();
  deleteUserArRel();
  deleteAr();
}
