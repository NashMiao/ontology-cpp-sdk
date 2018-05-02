#ifndef AES_H
#define AES_H

#include <openssl/err.h>
#include <openssl/evp.h>
#include <string>
using namespace std;

enum AEAD_mode { AES_CTR, AES_GCM };

class AES {
private:
  EVP_PKEY *pkey;

public:
  bool auth_encry(std::string msg, std::string &enc_msg,
                  AEAD_mode mode = AES_CTR);
  bool auth_decry(std::string msg, std::string &dec_msg,
                  AEAD_mode mode = AES_CTR);
};
#endif