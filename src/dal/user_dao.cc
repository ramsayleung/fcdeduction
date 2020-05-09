#include "user_dao.h"
model::DeUser deuser = {};
bool fcdeduction::dao::UserDao::userExist(sqlpp::mysql::connection &connection,
                                          const std::string &tntInstId,
                                          const std::string &userId) {
  return selectByUserId(connection, tntInstId, userId).has_value();
}
std::optional<fcdeduction::dataobject::User> selectByUserId(
    sqlpp::mysql::connection &connection, const std::string &tntInstId,
    const std::string &userId) {
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