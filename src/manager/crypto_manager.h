#ifndef MANAGER_CRYPTO_MANAGER_H
#define MANAGER_CRYPTO_MANAGER_H
#include <openssl/crypto.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
namespace fcdeduction {
namespace manager {
static const unsigned int KEY_SIZE = 32;
static const unsigned int BLOCK_SIZE = 16;

template <typename T>
struct zallocator {
 public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;

  pointer address(reference v) const { return &v; }
  const_pointer address(const_reference v) const { return &v; }

  pointer allocate(size_type n, const void* hint = 0) {
    if (n > std::numeric_limits<size_type>::max() / sizeof(T))
      throw std::bad_alloc();
    return static_cast<pointer>(::operator new(n * sizeof(value_type)));
  }

  void deallocate(pointer p, size_type n) {
    OPENSSL_cleanse(p, n * sizeof(T));
    ::operator delete(p);
  }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(T);
  }

  template <typename U>
  struct rebind {
    typedef zallocator<U> other;
  };

  void construct(pointer ptr, const T& val) {
    new (static_cast<T*>(ptr)) T(val);
  }

  void destroy(pointer ptr) { static_cast<T*>(ptr)->~T(); }

#if __cpluplus >= 201103L
  template <typename U, typename... Args>
  void construct(U* ptr, Args&&... args) {
    ::new (static_cast<void*>(ptr)) U(std::forward<Args>(args)...);
  }

  template <typename U>
  void destroy(U* ptr) {
    ptr->~U();
  }
#endif
};

typedef unsigned char byte;
typedef std::basic_string<char, std::char_traits<char>, zallocator<char> >
    secure_string;
using EVP_CIPHER_CTX_free_ptr =
    std::unique_ptr<EVP_CIPHER_CTX, decltype(&::EVP_CIPHER_CTX_free)>;
class CryptoManager {
 public:
  // 生成v4版本的UUID, 具体可见RFC-4122, 以字符串形式返回
  std::string generateUUIDV4();
  // aes 加解密代码修改自
  // https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption#C.2B.2B_Programs
  void aes_encrypt(const byte key[KEY_SIZE], const byte iv[BLOCK_SIZE],
                   const secure_string& ptext, secure_string& ctext);

  void aes_decrypt(const byte key[KEY_SIZE], const byte iv[BLOCK_SIZE],
                   const secure_string& ctext, secure_string& rtext);
};
}  // namespace manager
}  // namespace fcdeduction
#endif