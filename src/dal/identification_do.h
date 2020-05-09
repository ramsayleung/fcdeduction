#ifndef DAL_IDENTIFICATION_DO_H
#define DAL_IDENTIFICATION_DO_H
#include <chrono>
#include <string>
namespace fcdeduction {
namespace dataobject {
struct Identification {
  std::string tntInstId;
  std::string identId;
  std::string userId;
  std::string identType;
  std::string identKey;
  std::string identValue;
  std::chrono::time_point<std::chrono::system_clock> gmtCreate;
  std::chrono::time_point<std::chrono::system_clock> gmtModified;
};
}  // namespace dataobject

}  // namespace fcdeduction
#endif