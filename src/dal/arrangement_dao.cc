#include "arrangement_dao.h"

#include "arrangement.h"
model::DeAr dear;
bool fcdeduction::dao::ArrangementDao::arExist(
    sqlpp::mysql::connection &connection, const std::string &tntInstId,
    const std::string &arNo) {
  return connection(
             sqlpp::select(exists(select(dear.arNumber)
                                      .from(dear)
                                      .where(dear.tntInstId == tntInstId and
                                             dear.arNumber == arNo))))
      .front()
      .exists;
}