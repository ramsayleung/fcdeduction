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
  const std::string ptext = "password";
  std::string salt = getenv("salt");
  std::string hashed = cryptoManager.sha256(ptext, salt);
  std::cout << "hashed key: " << hashed << std::endl;
  std::cout << "original key: " << ptext << std::endl;
}
TEST(CRYPTO_TEST, UUIDV4_TEST) { generateUUIDV4Test(); }
TEST(CRYPTO_TEST, SHA256_TEST) { sha256Test(); }