#include "user_dao.h"
  #include "spdlog/spdlog.h"
#include <iostream>
model::DeUser deuser = {};
bool fcdeduction::dao::UserDao::userExist(const std::string &tntInstId,
                                          const std::string &userId) {
  sqlpp::mysql::connection &connection = *pconnection;

  return selectByUserId(tntInstId, userId).has_value();
}
std::optional<fcdeduction::dataobject::User>
fcdeduction::dao::UserDao::selectByUserId(const std::string &tntInstId,
                                          const std::string &userId) {
  sqlpp::mysql::connection &connection = *pconnection;
  for (auto const &row :
       connection(sqlpp::select(all_of(deuser))
                      .from(deuser)
                      .where(deuser.userId == userId and
                             deuser.tntInstId == tntInstId))) {
    fcdeduction::dataobject::User user;
    user.tntInstId = row.tntInstId;
    user.userId = row.userId;
    user.userName = row.userName;
    user.userType = row.userType;
    spdlog::info("用户查询成功, userId:{0}, userName: {1}", user.userId,user.userName);
    return std::optional<fcdeduction::dataobject::User>{user};
  }
    spdlog::info("用户查询不存在, userId:{0}", userId);
  return std::nullopt;
}
void fcdeduction::dao::UserDao::insertUser(
    fcdeduction::dataobject::User &user) {
  sqlpp::mysql::connection &connection = *pconnection;
  connection(sqlpp::insert_into(deuser).set(
      deuser.userId = user.userId, deuser.tntInstId = user.tntInstId,
      deuser.userName = user.userName, deuser.userType = user.userType,
      deuser.gmtCreate = user.gmtCreate,
      deuser.gmtModified = user.gmtModified));
}

void fcdeduction::dao::UserDao::deleteUser(const std::string &tntInstId,
                                           const std::string &userId) {
  sqlpp::mysql::connection &connection = *pconnection;
  connection(sqlpp::remove_from(deuser).where(deuser.userId == userId and
                                              deuser.tntInstId == tntInstId));
}