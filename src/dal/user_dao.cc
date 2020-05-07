#include "user_dao.h"

#include "user.h"
model::DeUser deuser = {};
bool fcdeduction::dao::UserDao::userExist(sqlpp::mysql::connection &connection,
                                          const std::string &tntInstId,
                                          const std::string &userId) {
  return connection(
             sqlpp::select(exists(select(deuser.userId)
                                      .from(deuser)
                                      .where(deuser.userId == userId and
                                             deuser.tntInstId == tntInstId))))

      .front()
      .exists;
}