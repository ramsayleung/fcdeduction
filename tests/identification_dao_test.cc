#include "src/dal/identification_dao.h"

#include "gtest/gtest.h"
#include "src/dal/identification.h"
#include "src/manager/crypto_manager.h"
#include "src/util/config.h"
#include "src/util/constant.h"
#include "src/util/ident_type_enum.h"
TEST(IDENT_DAOTEST, IDENT_EXIST_TEST) {
  using namespace fcdeduction::util;
  fcdeduction::manager::CryptoManager cryptoManager;
  std::string salt = getEnvironmentVariableOrDefault("salt", "111111");
  fcdeduction::dataobject::Identification ident;
  const std::string userId = "userId0001";
  const std::string identKey = "xxx@gmail.com";
  const std::string identValue = "password";
  ident.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  ident.identId = "identId00001";
  ident.userId = userId;
  ident.identType = fcdeduction::util::enumToString(
      fcdeduction::util::IdentTypeEnum::PASSWORD);
  ident.identKey = identKey;
  ident.identValue = cryptoManager.sha256(identValue, salt);
  fcdeduction::dao::IdentificationDao dao;
  dao.deleteIdent(fcdeduction::util::getTntInstIdByEnv(), userId, identKey,
                  fcdeduction::util::enumToString(
                      fcdeduction::util::IdentTypeEnum::PASSWORD));
  dao.insertIdent(ident);
  std::string passwd = cryptoManager.sha256("password", salt);
  EXPECT_TRUE(dao.identMatch(fcdeduction::util::getTntInstIdByEnv(), userId,
                             identKey, passwd,
                             fcdeduction::util::IdentTypeEnum::PASSWORD));
  dao.deleteIdent(fcdeduction::util::getTntInstIdByEnv(), userId, identKey,
                  fcdeduction::util::enumToString(
                      fcdeduction::util::IdentTypeEnum::PASSWORD));
}

TEST(IDENT_DAOTEST, FIND_USER_TEST) {
  using namespace fcdeduction::util;
  fcdeduction::manager::CryptoManager cryptoManager;
  std::string salt = getEnvironmentVariableOrDefault("salt", "111111");
  fcdeduction::dataobject::Identification ident;
  const std::string userId = "userId0001";
  const std::string identKey = "xxx@gmail.com";
  const std::string identValue = "password";
  ident.tntInstId = fcdeduction::util::getTntInstIdByEnv();
  ident.identId = "identId00001";
  ident.userId = userId;
  ident.identType = fcdeduction::util::enumToString(
      fcdeduction::util::IdentTypeEnum::PASSWORD);
  ident.identKey = identKey;
  ident.identValue = cryptoManager.sha256(identValue, salt);
  fcdeduction::dao::IdentificationDao dao;
  dao.deleteIdent(fcdeduction::util::getTntInstIdByEnv(), userId, identKey,
                  fcdeduction::util::enumToString(
                      fcdeduction::util::IdentTypeEnum::PASSWORD));
  dao.insertIdent(ident);
  auto optionalUserId = dao.findUserIdByIdentKeyAndIdentType(
      fcdeduction::util::getTntInstIdByEnv(), identKey,
      fcdeduction::util::IdentTypeEnum::PASSWORD);
  EXPECT_TRUE(optionalUserId.has_value());
  EXPECT_EQ(*optionalUserId, userId);
  dao.deleteIdent(fcdeduction::util::getTntInstIdByEnv(), userId, identKey,
                  fcdeduction::util::enumToString(
                      fcdeduction::util::IdentTypeEnum::PASSWORD));
}