#include "src/dal/identification_dao.h"

#include "gtest/gtest.h"
#include "src/dal/identification.h"
#include "src/manager/crypto_manager.h"
#include "src/manager/database_manager.hpp"
#include "src/util/constant.h"
#include "src/util/ident_type_enum.h"
TEST(DAOTEST, IDENT_EXIST_TEST) {
    fcdeduction::manager::CryptoManager cryptoManager;
    std::string salt = getenv("salt");
    fcdeduction::dataobject::Identification ident;
    const std::string userId = "userId0001";
    const std::string identKey = "xxx@gmail.com";
    const std::string identValue = "password";
    ident.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
    ident.identId = "identId00001";
    ident.userId = userId;
    ident.identType = fcdeduction::util::enumToString(
        fcdeduction::util::IdentTypeEnum::PASSWORD);
    ident.identKey = identKey;
    ident.identValue = cryptoManager.sha256(identValue, salt);
    fcdeduction::dao::IdentificationDao dao;
    dao.deleteIdent(fcdeduction::util::TEST_TNT_INST_ID, userId, identKey,
                    fcdeduction::util::enumToString(
                        fcdeduction::util::IdentTypeEnum::PASSWORD));
    dao.insertIdent(ident);
    std::string passwd = cryptoManager.sha256("password", salt);
    EXPECT_TRUE(dao.identMatch(fcdeduction::util::TEST_TNT_INST_ID, userId, identKey, passwd,
                               fcdeduction::util::IdentTypeEnum::PASSWORD));
    dao.deleteIdent(fcdeduction::util::TEST_TNT_INST_ID, userId, identKey,
                    fcdeduction::util::enumToString(
                        fcdeduction::util::IdentTypeEnum::PASSWORD));
}

TEST(DAOTEST, FIND_USER_TEST) {
    fcdeduction::manager::CryptoManager cryptoManager;
    std::string salt = getenv("salt");
    fcdeduction::dataobject::Identification ident;
    const std::string userId = "userId0001";
    const std::string identKey = "xxx@gmail.com";
    const std::string identValue = "password";
    ident.tntInstId = fcdeduction::util::TEST_TNT_INST_ID;
    ident.identId = "identId00001";
    ident.userId = userId;
    ident.identType = fcdeduction::util::enumToString(
        fcdeduction::util::IdentTypeEnum::PASSWORD);
    ident.identKey = identKey;
    ident.identValue = cryptoManager.sha256(identValue, salt);
    fcdeduction::dao::IdentificationDao dao;
    dao.deleteIdent(fcdeduction::util::TEST_TNT_INST_ID, userId, identKey,
                    fcdeduction::util::enumToString(
                        fcdeduction::util::IdentTypeEnum::PASSWORD));
    dao.insertIdent(ident);
    auto optionalUserId = dao.findUserIdByIdentKeyAndIdentType(fcdeduction::util::TEST_TNT_INST_ID, identKey, fcdeduction::util::IdentTypeEnum::PASSWORD);
    EXPECT_TRUE(optionalUserId.has_value());
    EXPECT_EQ(*optionalUserId, userId);
    dao.deleteIdent(fcdeduction::util::TEST_TNT_INST_ID, userId, identKey,
                    fcdeduction::util::enumToString(
                        fcdeduction::util::IdentTypeEnum::PASSWORD));
}