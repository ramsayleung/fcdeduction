#include "arrangement_dao.h"

model::DeAr dear;
bool fcdeduction::dao::ArrangementDao::arExist(const std::string &tntInstId,
                                               const std::string &arNo) {
  return selectByArNo(tntInstId, arNo).has_value();
}
std::optional<fcdeduction::dataobject::Arrangement>
fcdeduction::dao::ArrangementDao::selectByArNo(const std::string &tntInstId,
                                               const std::string &arNo) {
  sqlpp::mysql::connection &connection = *pconnection;
  for (auto const &row : connection(
           sqlpp::select(all_of(dear))
               .from(dear)
               .where(dear.tntInstId == tntInstId and dear.arNumber == arNo))) {
    fcdeduction::dataobject::Arrangement ar;
    ar.tntInstId = row.tntInstId;
    ar.arNumber = row.arNumber;
    ar.arName = row.arName;
    ar.arVersion = row.arVersion;
    ar.properties = row.properties;
    ar.memo = row.memo;
    return std::optional<fcdeduction::dataobject::Arrangement>{ar};
  }
  return std::nullopt;
}

void fcdeduction::dao::ArrangementDao::insertAr(
    fcdeduction::dataobject::Arrangement &ar) {
  sqlpp::mysql::connection &connection = *pconnection;
  connection(sqlpp::insert_into(dear).set(
      dear.tntInstId = ar.tntInstId, dear.arName = ar.arName,
      dear.arNumber = ar.arNumber, dear.arVersion = ar.arVersion,
      dear.memo = ar.memo, dear.properties = ar.properties,
      dear.gmtCreate = ar.gmtCreate, dear.gmtModified = ar.gmtModified));
}

void fcdeduction::dao::ArrangementDao::deleteAr(const std::string &tntInstId,
                                                const std::string &arNo) {
  sqlpp::mysql::connection &connection = *pconnection;
  connection(sqlpp::remove_from(dear).where(dear.arNumber == arNo and
                                            dear.tntInstId == tntInstId));
}