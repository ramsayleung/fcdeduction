#ifndef DAL_USER_DO_H
#define DAL_USER_DO_H
#include <chrono>
#include <string>
namespace fcdeduction {
namespace dataobject {
struct User {
    std::string tntInstId;
    std::string userId;
    std::string userName;
    std::string userType;
    std::chrono::time_point<std::chrono::system_clock> gmtCreate;
    std::chrono::time_point<std::chrono::system_clock> gmtModified;
};
}  // namespace dataobject
}  // namespace fcdeduction
#endif