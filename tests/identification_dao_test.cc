#include "src/dal/identification_dao.h"

#include "gtest/gtest.h"
#include "src/dal/identification.h"
#include "src/manager/crypto_manager.h"
#include "src/manager/database_manager.hpp"
#include "src/util/ident_type_enum.h"
model::DeIdent ident;
namespace mysql = sqlpp::mysql;
void testInsertIdent(mysql::connection &connection,
                     const std::string &tntInstId, const std::string &userId,
                     const std::string &identKey,
                     const std::string &identValue) {
  connection(sqlpp::insert_into(ident).set(
      ident.tntInstId = tntInstId, ident.userId = userId,
      ident.identType = fcdeduction::util::enumToString(
          fcdeduction::util::IdentTypeEnum::PASSWORD),
      ident.identKey = identKey, ident.identValue = identValue,
      ident.identId = "identId00001",
      ident.gmtCreate = std::chrono::system_clock::now(),
      ident.gmtModified = std::chrono::system_clock::now()));
}
void testDeleteIdent(mysql::connection &connection,
                     const std::string &tntInstId, const std::string &userId,
                     const std::string &identKey,
                     const std::string &identValue) {
  connection(sqlpp::remove_from(ident).where(
      ident.tntInstId == tntInstId and ident.userId == userId and
      ident.identType == fcdeduction::util::enumToString(
                             fcdeduction::util::IdentTypeEnum::PASSWORD) and
      ident.identKey == identKey and ident.identValue == identValue));
}
TEST(DAOTEST, IDENT_EXIST_TEST) {
  fcdeduction::manager::DatabaseManager dbManager(
      "127.0.0.1", getenv("mysql_database"), getenv("mysql_user"),
      getenv("mysql_password"));
  auto connection = dbManager.getConnection();
  const std::string tntInstId = "A0000001";
  const std::string userId = "userId0001";
  const std::string identKey = "xxx@gmail.com";
  const std::string identValue = "password";
  fcdeduction::manager::CryptoManager cryptoManager;
  std::string salt = getenv("salt");
  testDeleteIdent(*connection, tntInstId, userId, identKey,
                  cryptoManager.sha256(identValue, salt));
  testInsertIdent(*connection, tntInstId, userId, identKey,
                  cryptoManager.sha256(identValue, salt));
  fcdeduction::dao::IdentificationDao dao;
  std::string passwd = cryptoManager.sha256("password", salt);
  EXPECT_TRUE(dao.identMatch(*connection, tntInstId, userId, identKey, passwd,
                             fcdeduction::util::IdentTypeEnum::PASSWORD));
  testDeleteIdent(*connection, tntInstId, userId, identKey, passwd);
}