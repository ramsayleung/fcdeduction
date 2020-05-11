#include "src/manager/token_manager.h"

#include <iostream>

#include "gtest/gtest.h"
#include "src/manager/redis_manager.hpp"
void testToken() {
  fcdeduction::manager::TokenManager tokenManager;
  const std::string tokenId1 = "token202005071429";
  const std::string tokenId2 = "token302005071429";
  const std::string userId = "userId001";
  tokenManager.addUserToken(tokenId1, userId);
  EXPECT_TRUE(tokenManager.checkUserToken(tokenId1));
  tokenManager.addUserToken(tokenId2, userId);
  EXPECT_FALSE(tokenManager.checkUserToken(tokenId1));
  EXPECT_TRUE(tokenManager.checkUserToken(tokenId2));
}
int main() { testToken(); }