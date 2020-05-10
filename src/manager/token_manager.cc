#include "token_manager.h"

#include <optional>
void fcdeduction::manager::TokenManager::addUserToken(
    const std::string& tokenId, const std::string& userId) {
    // 设置token-userId 关系, 实际项目中, 更常用的是设置token-userInfo,
    // 将用户信息序列化后保存到redis 然后通过token即可查询到完整用户信息,
    // 无需查库.
    redisManager.set(tokenId, userId);
    // 然后设置userId-token关系, 如果之前已经有用户用同一个账户登录,
    // 那么userId-token的绑定关系就会存在 然后已存在再set,
    // 就会把原来的userId-token 覆盖掉, 就相当于将原来的登录设备踢出.
    redisManager.set(userId, tokenId);
}
bool fcdeduction::manager::TokenManager::checkUserToken(
    const std::string& tokenId) {
    std::optional<std::string> foundUserId = redisManager.get(tokenId);
    if (!foundUserId.has_value()) {
        return false;
    }
    std::optional<std::string> foundTokenId = redisManager.get(*foundUserId);
    return foundTokenId.has_value() && foundTokenId.value() == tokenId;
}