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

class AES
{
  private:
    static inline void set_padding(EVP_CIPHER_CTX *ctx, bool padding)
    {
        if (padding)
        {
            EVP_CIPHER_CTX_set_padding(ctx, 1);
        }
        else
        {
            EVP_CIPHER_CTX_set_padding(ctx, 0);
        }
    }

  public:
    static std::vector<unsigned char> generateKey(const std::string &password)
    {
        std::vector<unsigned char> passwordBytes(password.begin(), password.end());
        std::vector<unsigned char> passwordHash = Digest::hash256(passwordBytes);
        return passwordHash;
    }

    static std::vector<unsigned char>
    gcmEncrypt(const std::vector<unsigned char> &plaintext,
               const std::vector<unsigned char> &key,
               const std::vector<unsigned char> &iv, bool padding)
    {
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        EVP_CIPHER_CTX_init(ctx);
        if (ctx == NULL)
        {
            throw std::runtime_error("EVP_CIPHER_CTX_new() failed.");
        }
        set_padding(ctx, padding);
        /* check lengths */
        if (EVP_CIPHER_CTX_key_length(ctx) != AES_256_KEY_SIZE)
        {
            throw std::runtime_error(
                "EVP_CIPHER_CTX_key_length(ctx) != AES_256_KEY_SIZE");
        }
        if (EVP_CIPHER_CTX_iv_length(ctx) != AES_BLOCK_SIZE)
        {
            throw std::runtime_error(
                "EVP_CIPHER_CTX_iv_length(ctx) != AES_BLOCK_SIZE");
        }

        /* set key and IV */
        if (!EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key.data(),
                                iv.data()))
        {
            throw std::runtime_error("EVP_EncryptInit_ex() fail.");
        }
        /* Allow enough space in output buffer for additional block */
        int cipher_block_size = EVP_CIPHER_block_size(EVP_aes_256_gcm());
        int buf_size = 32;
        unsigned char out_buf[buf_size + cipher_block_size];

        int out_len;
        if (EVP_EncryptUpdate(ctx, out_buf, &out_len, plaintext.data(), buf_size) !=
            1)
        {
            EVP_CIPHER_CTX_cleanup(ctx);
            throw std::runtime_error("EVP_EncryptUpdate() fail.");
        }

        if (!EVP_EncryptFinal_ex(ctx, out_buf, &out_len))
        {
            EVP_CIPHER_CTX_cleanup(ctx);
            throw std::runtime_error("EVP_EncryptFinal_ex() fail");
        }
        std::vector<unsigned char> vec(out_buf, out_buf + out_len);
        return vec;
    }

    static std::vector<unsigned char>
    gcmDecrypt(const std::vector<unsigned char> &ciphertext,
               const std::vector<unsigned char> &key,
               const std::vector<unsigned char> &iv, bool padding)
    {
        /* Allow enough space in output buffer for additional block */
        int cipher_block_size = EVP_CIPHER_block_size(EVP_aes_256_gcm());

        EVP_CIPHER_CTX *ctx;
        ctx = EVP_CIPHER_CTX_new();
        EVP_CIPHER_CTX_init(ctx);
        if (ctx == NULL)
        {
            throw std::runtime_error("EVP_CIPHER_CTX_init() failed.");
        }
        set_padding(ctx, padding);

        /* set key and IV */
        if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, key.data(),
                               iv.data()) != 1)
        {
            throw std::runtime_error("EVP_DecryptInit_ex()");
        }

        int buf_size = (int)ciphertext.size();
        unsigned char out_buf[buf_size + cipher_block_size];

        int out_len;
        if (EVP_DecryptUpdate(ctx, out_buf, &out_len,
                              (const unsigned char *)ciphertext.data(),
                              ciphertext.size()) != 1)
        {
            EVP_CIPHER_CTX_cleanup(ctx);
            throw std::runtime_error("EVP_DecryptUpdate()");
        }

        if (EVP_DecryptFinal_ex(ctx, out_buf, &out_len) != 1)
        {
            EVP_CIPHER_CTX_cleanup(ctx);
            throw std::runtime_error("EVP_DecryptFinal_ex()");
        }
        std::vector<unsigned char> plaintext(out_buf, out_buf + out_len);
        return plaintext;
    }
};
#endif