#include "src/manager/redis_manager.hpp"

#include <iostream>

#include "gtest/gtest.h"

TEST(RedisManagerGet, ReturnHello) {
  fcdeduction::manager::RedisManager redisManager("127.0.0.1", 6379);
  redisManager.del("hello");
  redisManager.set("hello", "202005051647");
  auto value = redisManager.get("hello");
  std::cout << "value: " << value << '\n';
  EXPECT_EQ(value, "202005051647");
}
