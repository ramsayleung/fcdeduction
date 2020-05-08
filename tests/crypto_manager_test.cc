#include "src/manager/crypto_manager.h"

#include <iostream>

#include "gtest/gtest.h"
void generateUUIDV4Test() {
  fcdeduction::manager::CryptoManager cryptoManager;
  const std::string uuid = cryptoManager.generateUUIDV4();
  std::cout << "uuid: " << uuid << '\n';
}
void sha256Test() {
  using namespace fcdeduction::manager;
  CryptoManager cryptoManager;
  const std::string ptext = "The quick brown fox jumps over the lazy dog";
  std::string salt = getenv("salt");
  std::string hashed = cryptoManager.sha256(ptext, salt);
  std::cout << "hashed key: " << hashed << '\n';
  std::cout << "original key: " << ptext << '\n';
}
int main() {
  generateUUIDV4Test();
  sha256Test();
}