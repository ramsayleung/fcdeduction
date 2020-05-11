#ifndef MANAGER_TOKEN_MANAGER_HPP
#define MANAGER_TOKEN_MANAGER_HPP
#include <optional>
#include <string>

#include "redis_manager.hpp"
namespace fcdeduction {
namespace manager {
class TokenManager {
 public:
  explicit TokenManager() {}
  // 设置token-userId 关系, 实际项目中, 更常用的是设置token-userInfo,
  // 将用户信息序列化后保存到redis 然后通过token即可查询到完整用户信息,
  // 无需查库.
  void addUserToken(const std::string& tokenId, const std::string& userId);

  // 判断用户登录态是否有效.
  bool checkUserToken(const std::string& tokenId);

  // 通过tokenId获取用户信息
  std::optional<std::string> getUserInfoByTokenId(const std::string& tokenId);

 private:
  RedisManager redisManager;
};
}  // namespace manager
}  // namespace fcdeduction
#endif