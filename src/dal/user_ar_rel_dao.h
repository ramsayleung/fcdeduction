#ifndef DAL_USER_AR_REL_DAO_H
#define DAL_USER_AR_REL_DAO_H
#include <string>
#include <vector>

#include "base_dao.h"
#include "user_ar_rel.h"
#include "user_ar_rel_do.h"
namespace fcdeduction {
namespace dao {
class UserArRelDao : public fcdeduction::dao::BaseDao {
 public:
  using BaseDao::BaseDao;
  // 新增一条用户-合约-产品绑定关系记录.
  void addUserArRel(const std::string &tntInstId,
                    const fcdeduction::dataobject::UserArRel &rel);
  // 判断用户-合约-产品绑定关系是否存在.
  bool userArRelExist(const std::string &tntInstId, const std::string &arNo,
                      const std::string &pdCode, const std::string &userId);

  // 通过唯一键用户-合约-产品查询关系, 为空则返回std::nullopt;
  std::optional<fcdeduction::dataobject::UserArRel> selectByUserIdArNoAndPdCode(
      const std::string &tntInstId, const std::string &arNo,
      const std::string &pdCode, const std::string &userId);

  // 通过唯一键用户Id-合约号-产品码查询合约关系
  void deleteByUserIdArNoAndPdCode(const std::string &tntInstId,
                                   const std::string &arNo,
                                   const std::string &pdCode,
                                   const std::string &userId);
  //  通过用户Id和合约号, 查询关系列表. 支持分页.
  std::vector<fcdeduction::dataobject::UserArRel> selectListByUserIdAndArNo(
      const std::string &tntInstId, const std::string &arNo,
      const std::string &userId, unsigned int pageIndex, unsigned int pageSize);
};
}  // namespace dao
}  // namespace fcdeduction
#endif