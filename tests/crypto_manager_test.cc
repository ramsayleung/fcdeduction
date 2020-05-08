#include "src/manager/crypto_manager.h"

#include <iostream>

#include "gtest/gtest.h"
void generateUUIDV4Test() {
  fcdeduction::manager::CryptoManager cryptoManager;
  const std::string uuid = cryptoManager.generateUUIDV4();
  std::cout << "uuid: " << uuid << '\n';
}
void aesEncryptDecryptTest() {
  using namespace fcdeduction::manager;
  CryptoManager cryptoManager;
  unsigned char *key = (unsigned char *)getenv("aes_key");
  unsigned char *iv = (unsigned char *)getenv("aes_salt");
  const secure_string ptext = "The quick brown fox jumps over the lazy dog";
  secure_string ctext, rtext;
  cryptoManager.aes_encrypt(key, iv, ptext, ctext);
  cryptoManager.aes_decrypt(key, iv, ctext, rtext);
  std::cout << "encrypted key: " << ctext << '\n';
  std::cout << "original key: " << rtext << '\n';
  EXPECT_EQ(rtext, ptext);
}
int main() {
  generateUUIDV4Test();
  aesEncryptDecryptTest();
}