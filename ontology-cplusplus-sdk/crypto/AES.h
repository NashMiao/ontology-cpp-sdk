#ifndef AES_H
#define AES_H

/* 32 byte key (256 bit key) */
#define AES_256_KEY_SIZE 32
/* 16 byte block size (128 bits) */
#define AES_BLOCK_SIZE 16

#include <iostream>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <string.h>
#include <string>

using namespace std;

enum AEAD_mode { AES_CTR, AES_GCM };

typedef struct {
  /* Key to use for encrpytion and decryption */
  unsigned char key[AES_256_KEY_SIZE];
  /* Initialization Vector */
  unsigned char iv[AES_BLOCK_SIZE];
  const EVP_CIPHER *cipher_type;
} cipher_params_t;

class AES {
private:
  cipher_params_t *params;
  bool set_key(const unsigned char *k);
  bool set_iv(const unsigned char *v);
  bool set_mode(AEAD_mode mode);

public:
  AES() { params = (cipher_params_t *)malloc(sizeof(cipher_params_t)); }
  ~AES() { free(params); }
  bool params_init(AEAD_mode mode = AES_CTR);
  unsigned char *get_key() { return params->key; }
  unsigned char *get_iv() { return params->iv; }
  bool set_params(const unsigned char *k, const unsigned char *v,
                  const AEAD_mode mode = AES_CTR);
  bool auth_encry(const unsigned char *msg, unsigned char *enc_msg);
  bool auth_decry(std::string msg, std::string &dec_msg);
};
#endif