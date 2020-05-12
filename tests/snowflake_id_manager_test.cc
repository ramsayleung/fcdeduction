#include "src/manager/snowflake_id_manager.h"

#include <cstdint>
#include <set>
#include <thread>

#include "gtest/gtest.h"
std::set<int64_t> idSet;
void test(fcdeduction::manager::SnowFlakeIdManager &idManager) {
  for (int i = 0; i < 1000; i++) {
    auto id = idManager.nextId();
    bool contains = idSet.find(id) != idSet.end();
    EXPECT_TRUE(!contains);
    idSet.insert(id);
  }
}

TEST(MANAGER_TEST, NEXT_ID_TEST) {
  fcdeduction::manager::SnowFlakeIdManager idManager(10, 4);
  // std::thread t1(test, std::ref(idManager));
  // 生成100万个Id, 判断其不重复
  for (int i = 0; i < 1000000; i++) {
    auto id = idManager.nextId();
    bool contains = idSet.find(id) != idSet.end();
    EXPECT_TRUE(!contains);
    idSet.insert(id);
  }
  // t1.join();
}