#ifndef DAL_ARRANGEMENT_DAO_H
#define DAL_ARRANGEMENT_DAO_H
#include <optional>
#include <string>

#include "arrangement.h"
#include "arrangement_do.h"
#include "base_dao.h"
namespace fcdeduction {
namespace dao {
class ArrangementDao : public fcdeduction::dao::BaseDao {
 public:
  using BaseDao::BaseDao;
  // 通过合约号判断合约是否存在.
  bool arExist(const std::string &tntInstId, const std::string &arNo);
  // 通过合约号查询合约信息, 为空则返回 std::nullopt.
  std::optional<fcdeduction::dataobject::Arrangement> selectByArNo(
      const std::string &tntInstId, const std::string &arNo);
  // 插入合约
  void insertAr(fcdeduction::dataobject::Arrangement &ar);
  // 通过主键合约号删除指定合约
  void deleteAr(const std::string &tntInstId, const std::string &arNo);
};
}  // namespace dao
}  // namespace fcdeduction
#endif