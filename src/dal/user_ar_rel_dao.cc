#include "user_ar_rel_dao.h"

#include <chrono>
#include <optional>

#include "src/util/rel_status_enum.h"
model::DeUserArRel derel;
void fcdeduction::dao::UserArRelDao::addUserArRel(
    const std::string &tntInstId,
    const fcdeduction::dataobject::UserArRel &rel) {
  sqlpp::mysql::connection &connection = *pconnection;
  connection(sqlpp::insert_into(derel).set(
      derel.tntInstId = rel.tntInstId,
      derel.relId = rel.relId,
      derel.arName = rel.arName,
      derel.arNo = rel.arNo,
      derel.pdCode = rel.pdCode,
      derel.pdName = rel.pdName, 
      derel.userId = rel.userId,
      derel.relStatus = rel.relStatus,
      derel.memo = rel.memo, 
      derel.propertyValues = rel.propretyValues,
      derel.gmtCreate = rel.gmtCreate,
      derel.gmtModified = rel.gmtModified));
}
bool fcdeduction::dao::UserArRelDao::userArRelExist(
    const std::string &tntInstId, const std::string &arNo,
    const std::string &pdCode, const std::string &userId) {
  return this->selectByUserIdArNoAndPdCode(tntInstId, arNo, pdCode, userId)
      .has_value();
}

std::optional<fcdeduction::dataobject::UserArRel>
fcdeduction::dao::UserArRelDao::selectByUserIdArNoAndPdCode(
    const std::string &tntInstId, const std::string &arNo,
    const std::string &pdCode, const std::string &userId) {
  sqlpp::mysql::connection &connection = *pconnection;
  for (auto const &row : connection(
           sqlpp::select(all_of(derel))
               .from(derel)
               .where(derel.tntInstId == tntInstId and derel.arNo == arNo and
                      derel.pdCode == pdCode and derel.userId == userId))) {
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