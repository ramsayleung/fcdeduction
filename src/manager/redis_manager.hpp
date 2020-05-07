#ifndef REDIS_MANAGER_HPP
#define REDIS_MANAGER_HPP
#include <hiredis/hiredis.h>

#include <optional>
#include <string>
namespace fcdeduction {
namespace manager {
static void destroy(redisContext *context){
    redisFree(context);
  }
class RedisManager {
   public:
    explicit RedisManager(const std::string &hostname, const int port){
        redisContext *context = redisConnect(hostname.c_str(), port);
        pcontext = std::unique_ptr<redisContext>(context);
    }

    RedisManager(const RedisManager& rhs): pcontext(new redisContext(*rhs.pcontext)){}

    // ~RedisManager() { redisFree(context); }
    // 获取指定key的对应的value, 如果为空, 返回nullptr
    std::optional<std::string> get(const std::string &key);

    // 设置key-value.
    void set(const std::string &key, const std::string &value);

    // 删除指定key-value
    void del(const std::string &key);

   private:
    std::unique_ptr<redisContext> pcontext;
};

}  // namespace manager
}  // namespace fcdeduction
// 使用RAII管理Redis资源
#endif
