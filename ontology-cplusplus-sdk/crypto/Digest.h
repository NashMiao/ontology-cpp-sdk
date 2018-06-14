#ifndef DIGEST_H
#define DIGEST_H

#include <openssl/sha.h>
#include <vector>

class Digest {
public:
  std::vector<unsigned char> hash256(std::vector<unsigned char> &value) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256_ctx;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, &value, value.size());
    SHA256_Final(hash, &sha256);
    std::vector<unsigned char> uc_vec;
    uc_vec.assign(hash);
    return uc_vec;
  }
};
#endif