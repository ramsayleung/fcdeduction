#include "product_dao.h"
model::DeProd deprod = {};
bool fcdeduction::dao::ProductDao::productExist(
    sqlpp::mysql::connection& connection, const std::string& tntInstId,
    const std::string& pdCode) {
  return selectByPdCode(connection, tntInstId, pdCode).has_value();
}
std::optional<fcdeduction::dataobject::Product>
fcdeduction::dao::ProductDao::selectByPdCode(
    sqlpp::mysql::connection& connection, const std::string& tntInstId,
    const std::string& pdCode) {
  for (auto const& row : connection(sqlpp::select(all_of(deprod))
                                        .from(deprod)
                                        .where(deprod.tntInstId == tntInstId and
                                               deprod.pdCode == pdCode))) {
    fcdeduction::dataobject::Product product;
    product.tntInstId = row.tntInstId;
    product.pdCode = row.pdCode;
    product.pdName = row.pdName;
    product.pdDesc = row.pdDesc;
    product.pdOrgName = row.pdOrgName;
    product.memo = row.memo;
    return std::optional<fcdeduction::dataobject::Product>{product};
  }
  return std::nullopt;
}