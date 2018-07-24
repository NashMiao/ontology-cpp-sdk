#ifndef CRYPTO_AES_H
#define CRYPTO_AES_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

/* 32 byte key (256 bit key) */
#define AES_256_KEY_SIZE 32
/* 16 byte block size (128 bits) */
#define AES_BLOCK_SIZE 16

#include <stdexcept>
#include <string>
#include <vector>

#include <openssl/evp.h>

#include "../common/Helper.h"
#include "Digest.h"

typedef struct
{
    /* Key to use for encrpytion and decryption */
    unsigned char key[AES_256_KEY_SIZE];
    /* Initialization Vector */
    unsigned char iv[AES_BLOCK_SIZE];
    const EVP_CIPHER *cipher_type;
} cipher_params_t;

class AESHandler
{
  private:
  public:
    static std::vector<unsigned char> generateKey(std::string password)
    {
        std::vector<unsigned char> passwordBytes;
        passwordBytes = Helper::hexStringToByte(password);
        std::vector<unsigned char> passwordHash = Digest::hash256(passwordBytes);
        return passwordHash;
    }
};
#endif