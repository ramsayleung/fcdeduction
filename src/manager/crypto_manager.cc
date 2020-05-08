#include "crypto_manager.h"

#include <openssl/crypto.h>
#include <openssl/rand.h>

#include <cstdint>
#include <iostream>
using namespace fcdeduction::manager;
std::string CryptoManager::generateUUIDV4() {
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
void CryptoManager::aes_encrypt(const byte key[KEY_SIZE],
                                const byte iv[BLOCK_SIZE],
                                const secure_string& ptext,
                                secure_string& ctext) {
  EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
  int rc = EVP_EncryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
  if (rc != 1) throw std::runtime_error("EVP_EncryptInit_ex failed");

  // Recovered text expands upto BLOCK_SIZE
  ctext.resize(ptext.size() + BLOCK_SIZE);
  int out_len1 = (int)ctext.size();

  rc = EVP_EncryptUpdate(ctx.get(), (byte*)&ctext[0], &out_len1,
                         (const byte*)&ptext[0], (int)ptext.size());
  if (rc != 1) throw std::runtime_error("EVP_EncryptUpdate failed");

  int out_len2 = (int)ctext.size() - out_len1;
  rc = EVP_EncryptFinal_ex(ctx.get(), (byte*)&ctext[0] + out_len1, &out_len2);
  if (rc != 1) throw std::runtime_error("EVP_EncryptFinal_ex failed");

  // Set cipher text size now that we know it
  ctext.resize(out_len1 + out_len2);
}
void CryptoManager::aes_decrypt(const byte key[KEY_SIZE],
                                const byte iv[BLOCK_SIZE],
                                const secure_string& ctext,
                                secure_string& rtext) {
  EVP_CIPHER_CTX_free_ptr ctx(EVP_CIPHER_CTX_new(), ::EVP_CIPHER_CTX_free);
  int rc = EVP_DecryptInit_ex(ctx.get(), EVP_aes_256_cbc(), NULL, key, iv);
  if (rc != 1) throw std::runtime_error("EVP_DecryptInit_ex failed");

  // Recovered text contracts upto BLOCK_SIZE
  rtext.resize(ctext.size());
  int out_len1 = (int)rtext.size();

  rc = EVP_DecryptUpdate(ctx.get(), (byte*)&rtext[0], &out_len1,
                         (const byte*)&ctext[0], (int)ctext.size());
  if (rc != 1) throw std::runtime_error("EVP_DecryptUpdate failed");

  int out_len2 = (int)rtext.size() - out_len1;
  rc = EVP_DecryptFinal_ex(ctx.get(), (byte*)&rtext[0] + out_len1, &out_len2);
  if (rc != 1) throw std::runtime_error("EVP_DecryptFinal_ex failed");

  // Set recovered text size now that we know it
  rtext.resize(out_len1 + out_len2);
}