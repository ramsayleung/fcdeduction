#ifndef DAL_PRODUCT_DAO_H
#define DAL_PRODUCT_DAO_H

#include <optional>
#include <string>

#include "base_dao.h"
#include "product.h"
#include "product_do.h"
namespace fcdeduction {
namespace dao {
class ProductDao : public fcdeduction::dao::BaseDao {
 public:
  using BaseDao::BaseDao;
  // 通过产品码判断产品是否存在.
  bool productExist(const std::string& tntInstId, const std::string& pdCode);
  // 通过主键查询产品信息, 为空则返回 std::nullopt
  std::optional<fcdeduction::dataobject::Product> selectByPdCode(
      const std::string& tntInstId, const std::string& pdCode);
  // 通过主键产品码删除产品
  void deleteProductByPdCode(const std::string& tntInstId,
                             const std::string& pdCode);
  // 新增对应的产品
  void insertProduct(const fcdeduction::dataobject::Product& product);
};
}  // namespace dao
}  // namespace fcdeduction
#endif