#include "src/manager/snowflake_id_manager.h"

#include <cstdint>
#include <iostream>
#include <set>
#include <thread>

#include "gtest/gtest.h"
std::set<int64_t> idSet;
void test(fcdeduction::manager::SnowFlakeIdManager &idManager) {
  for (int i = 0; i < 1000000; i++) {
    auto id = idManager.nextId();
    bool contains = idSet.find(id) != idSet.end();
    EXPECT_TRUE(!contains);
    idSet.insert(id);
    std::cout << "id from thread: " << id << '\n';
  }
}

TEST(MANAGER_TEST, NEXT_ID_TEST) {
  fcdeduction::manager::SnowFlakeIdManager idManager(1024, 1000);
  std::thread t1(test, std::ref(idManager));
  for (int i = 0; i < 1000000; i++) {
    auto id = idManager.nextId();
    bool contains = idSet.find(id) != idSet.end();
    EXPECT_TRUE(!contains);
    idSet.insert(id);
    std::cout << "id: " << id << '\n';
  }
  t1.join();
}