#include "src/dal/arrangement_dao.h"

#include <iostream>

#include "gtest/gtest.h"
#include "src/dal/arrangement.h"
#include "src/dal/arrangement_do.h"
TEST(DAOTEST, ARRANGEMENT_EXIST_TEST) {
  // int main() {
  const std::string arNo = "202005072212";
  const std::string tntInstId = "A0000001";
  fcdeduction::dataobject::Arrangement ar;
  ar.arNumber = arNo;
  ar.tntInstId = tntInstId;
  ar.arName = "testar";
  ar.arNumber = arNo;
  ar.arVersion = "1";
  ar.memo = "memo";
  ar.properties = R"([{"name":"name", "key":"account","value":"change"}])";
  fcdeduction::dao::ArrangementDao dao;
  dao.deleteAr(tntInstId, arNo);
  dao.insertAr(ar);
  EXPECT_TRUE(dao.arExist(tntInstId, arNo));
  dao.deleteAr(tntInstId, arNo);
}