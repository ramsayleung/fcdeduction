#include "src/manager/snowflake_id_manager.h"

#include <cstdint>
#include <set>

#include "gtest/gtest.h"
TEST(MANAGER_TEST, NEXT_ID_TEST) {
    fcdeduction::manager::SnowFlakeIdManager idManager(1024, 1000);
    std::set<int64_t> idSet;
    for (int i = 0; i < 1000000; i++) {
        auto id = idManager.nextId();
        bool contains = idSet.find(id) != idSet.end();
        EXPECT_TRUE(!contains);
        idSet.insert(id);
    }
}