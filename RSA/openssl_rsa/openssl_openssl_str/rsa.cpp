// rsa.cpp
// g++ rsa.cpp -o rsa -lcrypto & ./rsa
#include "rsa.h"

bool Rsa::Key2Str(const RSA *key, std::string &str) {
  BIO *bio = BIO_new(BIO_s_mem());
  RSA_print(bio, key, 0);
  BUF_MEM *mem = NULL;
  BIO_get_mem_ptr(bio, &mem);
  BIO_free_all(bio);
  if (mem && mem->data && mem->length) {
    str.assign(mem->data, mem->length);
    return true;
  }
  return false;
}

bool Rsa::KeyGen(int kBits, unsigned long kExp) {
  RSA *rsa = RSA_generate_key(kBits, kExp, NULL, NULL);
  RsaPubKey = RSAPublicKey_dup(rsa);
  RsaPriKey = RSAPrivateKey_dup(rsa);
  if (RsaPubKey == NULL || RsaPriKey == NULL) {
    return false;
  }
  RSA_free(rsa);
  return true;
}

bool Rsa::RsaPubKeyEnc(const std::string &strData, std::string &strRet) {
  int flen = RSA_size(RsaPubKey);
  // RSA_PKCS1_OAEP_PADDING
  flen -= 2;
  char *pEncode = new char[flen + 1];

  cout << "RsaPubKeyEnc:\n";
  RSA_print_fp(stdout, RsaPubKey, 0);
  printf("\n\n");

  int ret = RSA_public_encrypt(
      strData.length(), (const unsigned char *)strData.c_str(),
      (unsigned char *)pEncode, RsaPubKey, RSA_PKCS1_OAEP_PADDING);
  if (ret <= 0) {
    cout << ret << endl;
    return false;
  }
  strRet = std::string(pEncode, ret);
  delete[] pEncode;
  CRYPTO_cleanup_all_ex_data();
  return true;
}

bool Rsa::RsaPubKeyEnc(const std::string &strData, std::string &strRet,
                       const RSA *PubKey) {
  int flen = RSA_size(PubKey);
  // RSA_PKCS1_OAEP_PADDING
  flen -= 2;
  char *pEncode = new char[flen + 1];

  int ret = RSA_public_encrypt(
      strData.length(), (const unsigned char *)strData.c_str(),
      (unsigned char *)pEncode, (RSA *)PubKey, RSA_PKCS1_OAEP_PADDING);
  if (ret <= 0) {
    return false;
  }
  strRet = std::string(pEncode, ret);
  delete[] pEncode;
  CRYPTO_cleanup_all_ex_data();
  return true;
}

bool Rsa::RsaPriKeyDec(const std::string &strData, std::string &strRet) {
  int flen = RSA_size(RsaPubKey);
  // RSA_PKCS1_OAEP_PADDING
  flen -= 2;
  char *pEncode = new char[flen + 1];
  int ret = RSA_private_decrypt(
      strData.length(), (const unsigned char *)strData.c_str(),
      (unsigned char *)pEncode, RsaPriKey, RSA_PKCS1_OAEP_PADDING);
  if (ret < 0) {
    return false;
  }
  strRet = std::string(pEncode, ret);
  delete[] pEncode;
  CRYPTO_cleanup_all_ex_data();
  return true;
}

bool Rsa::RsaPriKeyDec(const std::string &strData, std::string &strRet,
                       const RSA *PriKey) {
  int flen = RSA_size(PriKey);
  // RSA_PKCS1_OAEP_PADDING
  flen -= 2;
  char *pEncode = new char[flen + 1];
  int ret = RSA_private_decrypt(
      strData.length(), (const unsigned char *)strData.c_str(),
      (unsigned char *)pEncode, (RSA *)PriKey, RSA_PKCS1_OAEP_PADDING);
  if (ret < 0) {
    return false;
  }
  strRet = std::string(pEncode, ret);
  delete[] pEncode;
  CRYPTO_cleanup_all_ex_data();
  return true;
}

bool Rsa::RsaSign(const std::string &msg, std::string &sign_digest,
                  unsigned int &siglen, int type) {
  string digest;
  unsigned char *sigret;
  if (type == NID_sha256) {
    sigret = new unsigned char[256];
  }
  int ret = RSA_sign(type, (const unsigned char *)msg.c_str(), msg.length(),
                     sigret, &siglen, RsaPriKey);
  if (ret != 1) {
    return false;
  }
  sign_digest = std::string(reinterpret_cast<char *>(sigret));
  cout << "siglen: " << siglen << endl;
  cout << "sign_digest.length(): " << sign_digest.length() << endl;
  delete[] sigret;
  return true;
}

bool Rsa::RsaSign(const std::string &msg, std::string &sign_digest,
                  unsigned int &siglen, RSA *PriKey, int type) {
  string digest;
  unsigned char *sigret;
  if (type == NID_sha256) {
    sigret = new unsigned char[256];
  }
  int ret = RSA_sign(type, (unsigned char *)msg.c_str(), msg.length(), sigret,
                     &siglen, PriKey);
  if (ret != 1) {
    return false;
  }
  sign_digest = std::string(reinterpret_cast<char *>(sigret));
  delete[] sigret;
  return true;
}

bool Rsa::RsaVeri(const std::string &msg, const std::string &sign_digest,
                  const unsigned int &siglen, int type) {
  string digest, veri_digest;
  int ret;
  cout << "RsaVeri(const std::string &msg, const std::string &sign_digest, "
          "const unsigned int &siglen, int type):\n"
       << "siglen: " << siglen << endl;
  ret = RSA_verify(type, (unsigned char *)msg.c_str(), msg.length(),
                   (unsigned char *)sign_digest.c_str(), siglen, RsaPubKey);
  if (ret != 1) {
    return false;
  }
  return true;
}

bool Rsa::RsaVeri(const std::string &msg, const std::string &sign_digest,
                  const unsigned int &siglen, const RSA *PubKey, int type) {
  string digest, veri_digest;
  int ret;
  ret = RSA_verify(type, (unsigned char *)msg.c_str(), msg.length(),
                   (unsigned char *)sign_digest.c_str(), siglen, (RSA *)PubKey);
  if (ret != 1) {
    return false;
  }
  return true;
}
