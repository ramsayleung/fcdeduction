#include "user_ar_rel_dao.h"

#include <chrono>
#include <optional>

#include "src/util/rel_status_enum.h"
model::DeUserArRel derel;
void fcdeduction::dao::UserArRelDao::addUserArRel(sqlpp::mysql::connection &connection,
                                                  const std::string &tntInstId,
                                                  const fcdeduction::dataobject::Arrangement &ar,
                                                  const fcdeduction::dataobject::Product &prod,
                                                  const fcdeduction::dataobject::User &user) {
    connection(sqlpp::insert_into(derel).set(
        derel.tntInstId = tntInstId,
        derel.arName = ar.arName,
        derel.arNo = ar.arNumber,
        derel.pdCode = prod.pdCode,
        derel.pdName = prod.pdName,
        derel.userId = user.userId,
        derel.relStatus = fcdeduction::util::RelStatusEnum::ACTIVE,
        derel.memo = "",
        derel.gmtCreate = std::chrono::system_clock::now(),
        derel.gmtModified = std::chrono::system_clock::now()));
}
bool fcdeduction::dao::UserArRelDao::userArRelExist(sqlpp::mysql::connection &connection,
                                                    const std::string &tntInstId,
                                                    const std::string &arNo,
                                                    const std::string &pdCode,
                                                    const std::string &userId) {
    return this->selectByUserIdArNoAndPdCode(connection, tntInstId, arNo, pdCode, userId).has_value();
}

std::optional<fcdeduction::dataobject::UserArRel> fcdeduction::dao::UserArRelDao::selectByUserIdArNoAndPdCode(sqlpp::mysql::connection &connection,
                                                                                                              const std::string &tntInstId,
                                                                                                              const std::string &arNo,
                                                                                                              const std::string &pdCode,
                                                                                                              const std::string &userId) {
    for (auto const &row : connection(sqlpp::select(all_of(derel))
                                          .from(derel)
                                          .where(derel.tntInstId == tntInstId and
                                                 derel.arNo == arNo and
                                                 derel.pdCode == pdCode and
                                                 derel.userId == userId))) {
        fcdeduction::dataobject::UserArRel rel;

        rel.tntInstId = row.tntInstId;
        rel.relId = row.relId;
        rel.userId = row.userId;
        rel.relStatus = row.relStatus;
        rel.pdCode = row.pdCode;
        rel.pdName = row.pdName;
        rel.arName = row.arName;
        rel.arNo = row.arNo;
        rel.propretyValues = row.propertyValues;
        rel.memo = row.memo;
        return std::optional<fcdeduction::dataobject::UserArRel>{rel};
    }

    return std::nullopt;
}