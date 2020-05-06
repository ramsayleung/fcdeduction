#ifndef DAL_ARRANGEMENT_DO_H
#define DAL_ARRANGEMENT_DO_H
#include <chrono>
#include <string>
namespace fcdeduction {
namespace dataobject {
struct Arrangement {
    std::string tntInstId;
    std::string arNumber;
    std::string arName;
    std::string arVersion;
    std::string properties;
    std::string memo;
    std::chrono::time_point<std::chrono::system_clock> gmtCreate;
    std::chrono::time_point<std::chrono::system_clock> gmtModified;
};
}  // namespace dataobject
}  // namespace fcdeduction
#endif