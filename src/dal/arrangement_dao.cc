#include "arrangement_dao.h"

model::DeAr dear;
bool fcdeduction::dao::ArrangementDao::arExist(
    sqlpp::mysql::connection &connection, const std::string &tntInstId,
    const std::string &arNo) {
  return selectByArNo(connection, tntInstId, arNo).has_value();
}
std::optional<fcdeduction::dataobject::Arrangement>
fcdeduction::dao::ArrangementDao::selectByArNo(
    sqlpp::mysql::connection &connection, const std::string &tntInstId,
    const std::string &arNo) {
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