#ifndef MANAGER_SNOWFLAKE_ID_MANAGER_H
#define MANAGER_SNOWFLAKE_ID_MANAGER_H
// 参考于 https://github.com/sniper00/snowflake-cpp/blob/master/snowflake.hpp
namespace fcdeduction {
namespace manager {
#include <stdint.h>
#include <sys/time.h>

#include <mutex>
#include <stdexcept>

class SnowFlakeIdManager {
   private:
    static const uint64_t start_stmp_ = 1480166465631;
    static const uint64_t sequence_bit_ = 12;
    static const uint64_t machine_bit_ = 5;
    static const uint64_t datacenter_bit_ = 5;

    static const uint64_t max_datacenter_num_ = -1 ^ (uint64_t(-1) << datacenter_bit_);
    static const uint64_t max_machine_num_ = -1 ^ (uint64_t(-1) << machine_bit_);
    static const uint64_t max_sequence_num_ = -1 ^ (uint64_t(-1) << sequence_bit_);

    static const uint64_t machine_left = sequence_bit_;
    static const uint64_t datacenter_left = sequence_bit_ + machine_bit_;
    static const uint64_t timestmp_left = sequence_bit_ + machine_bit_ + datacenter_bit_;

    uint64_t datacenterId;
    uint64_t machineId;
    uint64_t sequence;
    uint64_t lastStmp;

    std::mutex mutex_;

    uint64_t getNextMill() {
        uint64_t mill = getNewstmp();
        while (mill <= lastStmp) {
            mill = getNewstmp();
        }
        return mill;
    }

    uint64_t getNewstmp() {
        struct timeval tv;
        gettimeofday(&tv, NULL);

        uint64_t time = tv.tv_usec;
        time /= 1000;
        time += (tv.tv_sec * 1000);
        return time;
    }

   public:
    SnowFlakeIdManager(int datacenter_Id, int machine_Id) {
        if ((uint64_t)datacenter_Id > max_datacenter_num_ || datacenter_Id < 0) {
            // LLOG(ERRO) << "datacenterId can't be greater than max_datacenter_num_ or less than 0";
            exit(0);
        }
        if ((uint64_t)machine_Id > max_machine_num_ || machine_Id < 0) {
            // LLOG(ERRO) << "machineId can't be greater than max_machine_num_or less than 0";
            exit(0);
        }
        datacenterId = datacenter_Id;
        machineId = machine_Id;
        sequence = 0L;
        lastStmp = 0L;
    }

    uint64_t nextId();
};

}  // namespace manager
}  // namespace fcdeduction
#endif