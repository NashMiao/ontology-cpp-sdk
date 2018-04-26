#include <openssl/bio.h>
#include <openssl/err.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Rsa {
private:
  int KeyLen;
  RSA *RsaPubKey;
  RSA *RsaPriKey;

public:
  ~Rsa() {
    RSA_free(RsaPubKey);
    RSA_free(RsaPriKey);
  }
  RSA *GetPubKey() { return RsaPubKey; }
  RSA *GetPriKey() { return RsaPriKey; }
  bool Key2Str(const RSA *key, std::string &str);
  bool KeyGen(int kBits = 2048, unsigned long kExp = RSA_F4);
  bool RsaPubKeyEnc(const std::string &strData, std::string &strRet);
  bool RsaPubKeyEnc(const std::string &strData, std::string &strRet,
                    const RSA *PubKey);
  bool RsaPriKeyDec(const std::string &strData, std::string &strRet);
  bool RsaPriKeyDec(const std::string &strData, std::string &strRet,
                    const RSA *PriKey);
  bool RsaSign(const std::string &msg, std::string &sign_digest,
               unsigned int &siglen, RSA *PriKey, int type = NID_sha256);
  bool RsaSign(const std::string &msg, std::string &sign_digest,
               unsigned int &siglen, int type = NID_sha256);
  bool RsaVeri(const std::string &msg, const std::string &sign_digest,
               const unsigned int &siglen, int type = NID_sha256);
  bool RsaVeri(const std::string &msg, const std::string &sign_digest,
               const unsigned int &siglen, const RSA *PubKey, int type = NID_sha256);
};
