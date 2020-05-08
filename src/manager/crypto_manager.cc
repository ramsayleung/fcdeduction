#include "crypto_manager.h"

// #include <openssl/rand.h>

#include <cstdint>
std::string fcdeduction::manager::CryptoManager::generateUUIDV4() {
  static char buffer[32];
  union {
    struct {
      uint32_t time_low;
      uint16_t time_mid;
      uint16_t time_hi_and_version;
      uint8_t clk_seq_hi_res;
      uint8_t clk_seq_low;
      uint8_t node[6];
    };
    uint8_t __rnd[16];
  } uuid;

  int rc = RAND_bytes(uuid.__rnd, sizeof(uuid));

  // Refer Section 4.2 of RFC-4122
  // https://tools.ietf.org/html/rfc4122#section-4.2
  uuid.clk_seq_hi_res = (uint8_t)((uuid.clk_seq_hi_res & 0x3F) | 0x80);
  uuid.time_hi_and_version =
      (uint16_t)((uuid.time_hi_and_version & 0x0FFF) | 0x4000);

  snprintf(buffer, 38, "%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x",
           uuid.time_low, uuid.time_mid, uuid.time_hi_and_version,
           uuid.clk_seq_hi_res, uuid.clk_seq_low, uuid.node[0], uuid.node[1],
           uuid.node[2], uuid.node[3], uuid.node[4], uuid.node[5]);
  if (rc == 1) {
    return std::string(buffer);
  } else {
    throw new std::runtime_error("生成v4uuid失败");
  }
}
std::string fcdeduction::manager::CryptoManager::sha256(
    const std::string& ptext, const std::string& salt) {
  std::string data = ptext + salt;
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data.c_str(), data.size());
  SHA256_Final(hash, &sha256);
  std::stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
  }
  return ss.str();
}