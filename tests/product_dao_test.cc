#include "src/dal/product_dao.h"

#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/product.h"
#include "src/manager/database_manager.hpp"
model::DeProd deprod = {};
namespace mysql = sqlpp::mysql;
void testInsertProduct(mysql::connection& connection,
                       const std::string& tntInstId,
                       const std::string& pdCode) {
  connection(sqlpp::insert_into(deprod).set(
      deprod.pdCode = pdCode, deprod.tntInstId = tntInstId,
      deprod.pdName = "测试产品", deprod.pdDesc = "测试产品描述",
      deprod.memo = "备注", deprod.pdOrgName = "主体信息",
      deprod.gmtCreate = std::chrono::system_clock::now(),
      deprod.gmtModified = std::chrono::system_clock::now()));
}

void testDeleteProduct(mysql::connection& connection,
                       const std::string& tntInstId,
                       const std::string& pdCode) {
  connection(sqlpp::remove_from(deprod).where(deprod.tntInstId == tntInstId and
                                              deprod.pdCode == pdCode));
}

TEST(DAOTEST, PRODUCTEXISTTEST) {
  const std::string pdCode = "pdCode1000";
  const std::string tntInstId = "A0000001";
  fcdeduction::manager::DatabaseManager dbManager(
      "127.0.0.1", getenv("mysql_database"), getenv("mysql_user"),
      getenv("mysql_password"));
  auto connection = dbManager.getConnection();
  testDeleteProduct(*connection, tntInstId, pdCode);
  testInsertProduct(*connection, tntInstId, pdCode);
  fcdeduction::dao::ProductDao productDao;
  EXPECT_TRUE(productDao.productExist(*connection, tntInstId, pdCode));
  testDeleteProduct(*connection, tntInstId, pdCode);
}