#ifndef MANAGER_TOKEN_MANAGER_HPP
#define MANAGER_TOKEN_MANAGER_HPP
#include "redis_manager.hpp"
namespace fcdeduction {
namespace manager {
class TokenManager {
   public:
    explicit TokenManager() {}
    void addUserToken(const std::string& tokenId, const std::string& userId);
    bool checkUserToken(const std::string& tokenId);

   private:
    RedisManager redisManager;
};
}  // namespace manager
}  // namespace fcdeduction
#endif