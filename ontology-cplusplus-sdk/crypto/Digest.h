#ifndef DIGEST_H
#define DIGEST_H

#include <openssl/ripemd.h>
#include <openssl/sha.h>
#include <vector>

class Digest
{
public:
  std::vector<unsigned char> sha256(std::vector<unsigned char> &value)
  {
    unsigned char hash256_uc[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, &value, value.size());
    SHA256_Final(hash256_uc, &sha256);
    std::vector<unsigned char> uc_vec;
    uc_vec.assign(hash256_uc);
    return uc_vec;
  }

  std::vector<unsigned char> ripemd160(std::vector<unsigned char> &value)
  {
    unsigned char ripemd160_uc[RIPEMD160_DIGEST_LENGTH];
    RIPEMD160_CTX *ripemd160_ctx;
    RIPEMD160_Init(&ripemd160_ctx);
    RIPEMD160_Update(&ripemd160_ctx, &value, value.size());
    RIPEMD160_Final(ripemd160_uc, &ripemd160_ctx);
    std::vector<unsigned char> uc_vec;
    uc_vec.assign(ripemd160_uc);
    return uc_vec;
  }

  std::vector<unsigned char> hash160(std::vector<unsigned char> &value)
  {
    return ripemd160(sha256(value));
  }

  std::vector<unsigned char> hash256(std::vector<unsigned char> &value){
    return sha256(sha256(value));
  }
};
#endif