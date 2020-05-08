#ifndef MANAGER_CRYPTO_MANAGER_H
#define MANAGER_CRYPTO_MANAGER_H
#include <openssl/sha.h>
#include <openssl/rand.h>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace fcdeduction {
namespace manager {
class CryptoManager {
 public:
  // 生成v4版本的UUID, 具体可见RFC-4122, 以字符串形式返回
  std::string generateUUIDV4();
  // 使用sha256 进行hash.
  std::string sha256(const std::string &ptext, const std::string &salt);
};
}  // namespace manager
}  // namespace fcdeduction
#endif