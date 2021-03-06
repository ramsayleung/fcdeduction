#include "snowflake_id_manager.h"
uint64_t fcdeduction::manager::SnowFlakeIdManager::nextId() {
  std::unique_lock<std::mutex> lock(mutex_);
  uint64_t currStmp = getNewstmp();
  if (currStmp < lastStmp) {
    spdlog::error("Clock moved backwards.  Refusing to generate id");
    throw std::runtime_error("Clock moved backwards.  Refusing to generate id");
  }

  if (currStmp == lastStmp) {
    sequence = (sequence + 1) & max_sequence_num_;
    if (sequence == 0) {
      currStmp = getNextMill();
    }
  } else {
    sequence = 0;
  }
  lastStmp = currStmp;
  return (currStmp - start_stmp_) << timestmp_left |
         datacenterId << datacenter_left | machineId << machine_left | sequence;
}