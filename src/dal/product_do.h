#ifndef DAL_PRODUCT_DO_H
#define DAL_PRODUCT_DO_H
#include <chrono>
#include <string>
namespace fcdeduction {
namespace dataobject {
struct Product {
    std::string tntInstId;
    std::string pdCode;
    std::string pdName;
    std::string pdDesc;
    std::string pdOrgName;
    std::string memo;
    std::chrono::time_point<std::chrono::system_clock> gmtCreate;
    std::chrono::time_point<std::chrono::system_clock> gmtModified;
};
}  // namespace dataobject
}  // namespace fcdeduction
#endif