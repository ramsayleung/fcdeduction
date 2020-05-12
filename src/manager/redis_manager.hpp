#ifndef REDIS_MANAGER_HPP
#define REDIS_MANAGER_HPP
#include <hiredis/hiredis.h>

#include <memory>
#include <optional>
#include <string>

#include "src/util/config.h"
namespace fcdeduction {
namespace manager {
class RedisManager {
 public:
  explicit RedisManager(const std::string &hostname, const int port) {
    redisContext *context = redisConnect(hostname.c_str(), port);
    pcontext = std::unique_ptr<redisContext>(context);
  }
  explicit RedisManager() {
    using namespace fcdeduction::util;
    std::string hostname =
        getEnvironmentVariableOrDefault("redis_host", "127.0.0.1");
    redisContext *context = redisConnect(hostname.c_str(), 6379);
    pcontext = std::unique_ptr<redisContext>(context);
  }

  RedisManager(const RedisManager &rhs)
      : pcontext(new redisContext(*rhs.pcontext)) {}

  // ~RedisManager() { redisFree(context); }
  // 获取指定key的对应的value, 如果为空, 返回std::nullopt
  std::optional<std::string> get(const std::string &key);

  // 设置key-value.
  void set(const std::string &key, const std::string &value);

  // 删除指定key-value
  void del(const std::string &key);

 private:
  // TODO redisContext是否有对应的析构函数, 是否应该给unique_ptr增加一个deleter.
  std::unique_ptr<redisContext> pcontext;
};

}  // namespace manager
}  // namespace fcdeduction
// 使用RAII管理Redis资源
#endif
