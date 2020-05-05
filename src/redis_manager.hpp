#ifndef REDIS_MANAGER_HPP
#define REDIS_MANAGER_HPP
#include <string>
#include <hiredis/hiredis.h>
// 使用RAII管理Redis资源
class RedisManager {
public:
  explicit RedisManager(const std::string &hostname, const int port) {
    context = redisConnect(hostname.c_str(), port);
  }
  ~RedisManager() {
    redisFree(context);
  }
  std::string get(const std::string &key);

  void set(const std::string &key, const std::string &value);
private:
  redisContext *context;
};

#endif
