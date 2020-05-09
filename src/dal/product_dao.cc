#include "product_dao.h"
model::DeProd deprod = {};
bool fcdeduction::dao::ProductDao::productExist(const std::string& tntInstId,
                                                const std::string& pdCode) {
  return selectByPdCode(tntInstId, pdCode).has_value();
}
std::optional<fcdeduction::dataobject::Product>
fcdeduction::dao::ProductDao::selectByPdCode(const std::string& tntInstId,
                                             const std::string& pdCode) {
  sqlpp::mysql::connection& connection = *pconnection;
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

void fcdeduction::dao::ProductDao::deleteProductByPdCode(
    const std::string& tntInstId, const std::string& pdCode) {
  sqlpp::mysql::connection& connection = *pconnection;
  connection(sqlpp::remove_from(deprod).where(deprod.tntInstId == tntInstId and
                                              deprod.pdCode == pdCode));
}
void fcdeduction::dao::ProductDao::insertProduct(
    const fcdeduction::dataobject::Product& product) {
  sqlpp::mysql::connection& connection = *pconnection;
  connection(sqlpp::insert_into(deprod).set(
      deprod.pdCode = product.pdCode, deprod.tntInstId = product.tntInstId,
      deprod.pdName = product.pdName, deprod.pdDesc = product.pdDesc,
      deprod.memo = product.memo, deprod.pdOrgName = product.pdOrgName,
      deprod.gmtCreate = product.gmtCreate,
      deprod.gmtModified = product.gmtModified));
}