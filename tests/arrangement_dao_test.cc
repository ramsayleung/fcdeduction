#include "src/dal/arrangement_dao.h"

#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/arrangement.h"
#include "src/manager/database_manager.hpp"
model::DeAr dear = {};
namespace mysql = sqlpp::mysql;
void testInsertAr(mysql::connection& connection, const std::string& tntInstId,
                  const std::string& arNo) {
  connection(sqlpp::insert_into(dear).set(
      dear.tntInstId = tntInstId, dear.arName = "测试合约",
      dear.arNumber = arNo, dear.arVersion = "1", dear.memo = "备注",
      dear.properties =
          R"([{"name":"签约账号", "key":"account","value":"零钱"}])",
      dear.gmtCreate = std::chrono::system_clock::now(),
      dear.gmtModified = std::chrono::system_clock::now()));
}
void testDeleteAr(mysql::connection& connection, const std::string& tntInstId,
                  const std::string& arNo) {
  connection(sqlpp::remove_from(dear).where(dear.arNumber == arNo and
                                            dear.tntInstId == tntInstId));
}
TEST(DAOTEST, ARRANGEMENT_EXIST_TEST) {
  const std::string arNo = "202005072212";
  const std::string tntInstId = "A0000001";
  fcdeduction::manager::DatabaseManager dbManager(
      "127.0.0.1", getenv("mysql_database"), getenv("mysql_user"),
      getenv("mysql_password"));
  auto connection = dbManager.getConnection();
  testDeleteAr(*connection, tntInstId, arNo);
  testInsertAr(*connection, tntInstId, arNo);
  fcdeduction::dao::ArrangementDao dao;
  EXPECT_TRUE(dao.arExist(*connection, tntInstId, arNo));
  testDeleteAr(*connection, tntInstId, arNo);
}