#ifndef DAL_PRODUCT_DAO_H
#define DAL_PRODUCT_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>
#include "product_do.h"
#include <memory>
#include <string>
#include <optional>
namespace fcdeduction {
namespace dao {
class ProductDao {
 public:
  // 通过产品码判断产品是否存在.
  bool productExist(sqlpp::mysql::connection& connection,
                    const std::string& tntInstId, const std::string& pdCode);
  // 通过主键查询产品信息, 为空则返回 std::nullopt
  std::optional<fcdeduction::dataobject::Product> selectByPdCode(sqlpp::mysql::connection& connection,
                    const std::string& tntInstId, const std::string& pdCode);
};
}  // namespace dao
}  // namespace fcdeduction
#endif