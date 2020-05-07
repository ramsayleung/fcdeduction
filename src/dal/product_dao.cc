#include "product_dao.h"

#include "product.h"
model::DeProd deprod = {};
bool fcdeduction::dao::ProductDao::productExist(
    sqlpp::mysql::connection &connection, const std::string &tntInstId,
    const std::string &pdCode) {
  return connection(
             sqlpp::select(exists(select(deprod.pdCode)
                                      .from(deprod)
                                      .where(deprod.tntInstId == tntInstId and
                                             deprod.pdCode == pdCode))))
      .front()
      .exists;
}