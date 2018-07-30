#ifndef DIGEST_H
#define DIGEST_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <vector>

#include <openssl/ripemd.h>
#include <openssl/sha.h>

#if defined(WIN32) || defined(_WIN64)
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
#endif

class Digest
{
public:
  static std::vector<unsigned char>
  sha256(const std::vector<unsigned char> &value)
  {
    unsigned char sha256_uc[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256_ctx);
    SHA256_Update(&sha256_ctx, (unsigned char *)(&value[0]), value.size());
    SHA256_Final(sha256_uc, &sha256_ctx);
    std::vector<unsigned char> uc_vec(&sha256_uc[0],
                                      &sha256_uc[SHA256_DIGEST_LENGTH]);
    return uc_vec;
  }

  static std::vector<unsigned char>
  sha256(const std::vector<unsigned char> &value, int offset, int length)
  {
    if (offset + length > int(value.size()))
    {
      throw "Error offset and length";
    }
    std::vector<unsigned char> array;
    array = value;
    if (offset != 0 || length != int(value.size()))
    {
      array.clear();
      array.assign(value.begin() + offset, value.begin() + offset + length);
    }
    return sha256(array);
  }

  static std::vector<unsigned char>
  ripemd160(std::vector<unsigned char> &value)
  {
    unsigned char ripemd160_uc[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160_CTX ripemd160_ctx;
    RIPEMD160_Init(&ripemd160_ctx);
    RIPEMD160_Update(&ripemd160_ctx, (unsigned char *)(&value[0]),
                     value.size());
    RIPEMD160_Final(ripemd160_uc, &ripemd160_ctx);
    std::vector<unsigned char> uc_vec;
    uc_vec.assign(&ripemd160_uc[0], &ripemd160_uc[RIPEMD160_DIGEST_LENGTH]);
    return uc_vec;
  }

  static std::vector<unsigned char>
  hash160(const std::vector<unsigned char> &value)
  {
    std::vector<unsigned char> sha256_vec;
    sha256_vec = sha256(value);
    return ripemd160(sha256_vec);
  }

  static std::vector<unsigned char>
  hash256(const std::vector<unsigned char> &value)
  {
    std::vector<unsigned char> sha256_vec;
    sha256_vec = sha256(value);
    return sha256(sha256_vec);
  }

  static std::vector<unsigned char>
  hash256(const std::vector<unsigned char> &value, int offset, int length)
  {
    std::vector<unsigned char> sha256_vec;
    sha256_vec = sha256(value, offset, length);
    return sha256(sha256_vec);
  }
};
#endif