#ifndef DAL_USER_AR_REL_H
#define DAL_USER_AR_REL_H
#include <chrono>
#include <string>
namespace fcdeduction {
namespace dataobject {
struct UserArRel {
    std::string tntInstId;
    std::string relId;
    std::string userId;
    std::string relStatus;
    std::string pdCode;
    std::string pdName;
    std::string pdOrgName;
    std::string arName;
    std::string arNo;
    std::string propretyValues;
    std::string memo;
    std::chrono::time_point<std::chrono::system_clock> gmtCreate;
    std::chrono::time_point<std::chrono::system_clock> gmtModified;
};
}  // namespace dataobject
}  // namespace fcdeduction
#endif