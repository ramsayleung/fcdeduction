#ifndef DAL_USER_AR_REL_DAO_H
#define DAL_USER_AR_REL_DAO_H
#include <sqlpp11/mysql/mysql.h>
#include <sqlpp11/sqlpp11.h>

#include <string>

#include "arrangement_do.h"
#include "product_do.h"
#include "user_do.h"
#include "user_ar_rel.h"
#include "user_ar_rel_do.h"
namespace fcdeduction {
namespace dao {
class UserArRelDao {
   public:
    // 新增一条用户-合约-产品绑定关系记录.
    void addUserArRel(sqlpp::mysql::connection &connection,
                      const std::string &tntInstId,
                      const fcdeduction::dataobject::Arrangement &ar,
                      const fcdeduction::dataobject::Product &prod,
                      const fcdeduction::dataobject::User &user);
    // 判断用户-合约-产品绑定关系是否存在.
    bool userArRelExist(sqlpp::mysql::connection &connection, const std::string &tntInstId, const std::string &arNo, const std::string &pdCode, const std::string &userId);

    // 通过唯一键用户-合约-产品查询关系, 为空则返回std::nullopt;
    std::optional<fcdeduction::dataobject::UserArRel> selectByUserIdArNoAndPdCode(sqlpp::mysql::connection &connection, const std::string &tntInstId, const std::string &arNo, const std::string &pdCode, const std::string &userId);
};
}  // namespace dao
}  // namespace fcdeduction
#endif