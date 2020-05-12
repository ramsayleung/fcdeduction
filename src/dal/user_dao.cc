#include "user_dao.h"

#include <iostream>

#include "spdlog/spdlog.h"
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
    return std::optional<fcdeduction::dataobject::User>{user};
  }
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