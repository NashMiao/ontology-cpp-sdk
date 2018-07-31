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
#include <openssl/rand.h>

#include "../common/Helper.h"
#include "Digest.h"

class AES
{
  private:
    static inline void setPadding(EVP_CIPHER_CTX *ctx, bool padding)
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

    static inline void checkArgument(const std::vector<unsigned char> &key,
                                     const std::vector<unsigned char> &iv,
                                     const EVP_CIPHER *cipher)
    {
        if (key.size() != EVP_CIPHER_key_length(cipher) ||
            iv.size() != EVP_CIPHER_iv_length(cipher))
        {
            throw std::runtime_error("IllegalArgumentException");
        }
    }

  public:
    static std::vector<unsigned char> generateKey(const std::string &password)
    {
        std::vector<unsigned char> passwordBytes(password.begin(), password.end());
        std::vector<unsigned char> passwordHash = Digest::hash256(passwordBytes);
        return passwordHash;
    }

    static std::vector<unsigned char> generateKey()
    {
        unsigned char key[AES_256_KEY_SIZE];
        if (RAND_bytes(key, AES_256_KEY_SIZE) != 1)
        {
            throw std::runtime_error("BAND_bytes() fail.");
        }
        return std::vector<unsigned char>(key, key + AES_256_KEY_SIZE);
        ;
    }

    static std::vector<unsigned char> generateIv()
    {
        unsigned char iv[AES_BLOCK_SIZE];
        if (RAND_bytes(iv, AES_BLOCK_SIZE) != 1)
        {
            throw std::runtime_error("BAND_bytes() fail.");
        }
        return std::vector<unsigned char>(iv, iv + AES_BLOCK_SIZE);
        ;
    }

    static int encrypt(const std::vector<unsigned char> &plaintext,
                const std::vector<unsigned char> &aad,
                const std::vector<unsigned char> &key,
                const std::vector<unsigned char> &iv,
                std::vector<unsigned char> &ciphertext,
                std::vector<unsigned char> &tag)
    {

        EVP_CIPHER_CTX *ctx;

        int len;

        int ciphertext_len;

        /* Create and initialise the context */
        if (!(ctx = EVP_CIPHER_CTX_new()))
        {
            throw std::runtime_error("Error");
        }

        /* Initialise the encryption operation. */
        if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), NULL, NULL, NULL))
        {
            throw std::runtime_error("Error");
        }

        /* Set IV length if default 12 bytes (96 bits) is not appropriate */
        if (1 !=
            EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, iv.size(), NULL))
        {
            throw std::runtime_error("Error");
        }
        std::cout << EVP_CIPHER_CTX_iv_length(ctx) << std::endl;

        /* Initialise key and IV */
        if (1 != EVP_EncryptInit_ex(ctx, NULL, NULL, key.data(), iv.data()))
        {
            throw std::runtime_error("Error");
        }

        /* Provide any AAD data. This can be called zero or more times as
     * required
     */
        if (1 != EVP_EncryptUpdate(ctx, NULL, &len, aad.data(), aad.size()))
        {
            throw std::runtime_error("Error");
        }

        /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
        if (1 != EVP_EncryptUpdate(ctx, ciphertext.data(), &len, plaintext.data(),
                                   plaintext.size()))
        {
            throw std::runtime_error("Error");
        }
        ciphertext_len = len;

        /* Finalise the encryption. Normally ciphertext bytes may be written at
     * this stage, but this does not occur in GCM mode
     */
        if (1 != EVP_EncryptFinal_ex(ctx, ciphertext.data() + len, &len))
        {
            throw std::runtime_error("Error");
        }
        ciphertext_len += len;

        /* Get the tag */
        if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, 16, tag.data()))
        {
            throw std::runtime_error("Error");
        }

        /* Clean up */
        EVP_CIPHER_CTX_free(ctx);

        return ciphertext_len;
    }

    static std::vector<unsigned char>
    gcmEncrypt(const std::vector<unsigned char> &plaintext,
               const std::vector<unsigned char> &key,
               const std::vector<unsigned char> &iv, bool padding)
    {
        // checkArgument(key, iv, EVP_aes_256_gcm());
        EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
        EVP_CIPHER_CTX_init(ctx);
        if (ctx == nullptr)
        {
            throw std::runtime_error("EVP_CIPHER_CTX_new() failed.");
        }

        /* Initialise the encryption operation. */
        if (1 !=
            EVP_EncryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, nullptr, nullptr))
        {
            throw std::runtime_error("EVP_EncryptInit_ex() fail.");
        }
        /* Set IV length if default 12 bytes (96 bits) is not appropriate */
        if (1 != EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_IVLEN, 16, nullptr))
        {
            throw std::runtime_error("EVP_CIPHER_CTX_ctrl() fail.");
        }
        std::cout << EVP_CIPHER_CTX_iv_length(ctx) << std::endl;

        setPadding(ctx, padding);
        /* set key and IV */
        if (1 != EVP_EncryptInit_ex(ctx, nullptr, nullptr, key.data(), iv.data()))
        {
            throw std::runtime_error("EVP_EncryptInit_ex() fail.");
        }
        /* check lengths */
        if (EVP_CIPHER_CTX_key_length(ctx) !=
            EVP_CIPHER_key_length(EVP_aes_256_gcm()))
        {
            throw std::runtime_error(
                "EVP_CIPHER_CTX_key_length(ctx) != AES_256_KEY_SIZE");
        }
        if (EVP_CIPHER_CTX_iv_length(ctx) !=
            EVP_CIPHER_iv_length(EVP_aes_256_gcm()))
        {
            throw std::runtime_error(
                "EVP_CIPHER_CTX_iv_length(ctx) != AES_BLOCK_SIZE");
        }
        /* Allow enough space in output buffer for additional block */
        int cipher_block_size = EVP_CIPHER_block_size(EVP_aes_256_gcm());
        unsigned char out_buf[(int)plaintext.size() + cipher_block_size];

        int out_len;
        if (EVP_EncryptUpdate(ctx, out_buf, &out_len, plaintext.data(),
                              plaintext.size()) != 1)
        {
            EVP_CIPHER_CTX_cleanup(ctx);
            throw std::runtime_error("EVP_EncryptUpdate() fail.");
        }

        if (1 != EVP_EncryptFinal_ex(ctx, out_buf, &out_len))
        {
            EVP_CIPHER_CTX_cleanup(ctx);
            throw std::runtime_error("EVP_EncryptFinal_ex() fail");
        }
        std::cout << out_buf << std::endl;
        std::vector<unsigned char> vec(out_buf, out_buf + (int)plaintext.size() +
                                                    cipher_block_size);
        return vec;
    }

    static std::vector<unsigned char>
    gcmDecrypt(const std::vector<unsigned char> &ciphertext,
               const std::vector<unsigned char> &key,
               const std::vector<unsigned char> &iv, bool padding)
    {
        checkArgument(key, iv, EVP_aes_256_gcm());

        EVP_CIPHER_CTX *ctx;
        ctx = EVP_CIPHER_CTX_new();
        EVP_CIPHER_CTX_init(ctx);
        if (ctx == nullptr)
        {
            throw std::runtime_error("EVP_CIPHER_CTX_init() failed.");
        }
        setPadding(ctx, padding);

        /* set key and IV */
        if (EVP_DecryptInit_ex(ctx, EVP_aes_256_gcm(), nullptr, key.data(),
                               iv.data()) != 1)
        {
            throw std::runtime_error("EVP_DecryptInit_ex()");
        }

        /* Allow enough space in output buffer for additional block */
        int buf_size = (int)ciphertext.size();
        int cipher_block_size = EVP_CIPHER_block_size(EVP_aes_256_gcm());
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