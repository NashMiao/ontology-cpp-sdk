#ifndef SIGNATUREHANDLER_H
#define SIGNATUREHANDLER_H

#include <openssl/bio.h>
#include <openssl/conf.h>
#include <openssl/ec.h>    // for EC_GROUP_new_by_curve_name, EC_GROUP_free, EC_KEY_new, EC_KEY_set_group, EC_KEY_generate_key, EC_KEY_free
#include <openssl/ecdsa.h> // for ECDSA_do_sign, ECDSA_do_verify
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#include "KeyType.h"
#include "SignatureScheme.h"

#include <ostream>
#include <vector>

class SignatureHandler
{
private:
  KeyType key_type;
  SignatureScheme sign_scheme;
  EVP_MD_CTX *md_ctx;

protected:
  void md_ctx_sign_init()
  {
    switch (key_type)
    {
    case KeyType::ECDSA:
      switch (sign_scheme)
      {
      case SignatureScheme::SHA224withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha224(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      case SignatureScheme::SHA256withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha256(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      case SignatureScheme::SHA384withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha384(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      case SignatureScheme::SHA512withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha512(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      case SignatureScheme::SHA3_224withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_224(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      case SignatureScheme::SHA3_256withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_256(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      case SignatureScheme::SHA3_384withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_384(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      case SignatureScheme::SHA3_512withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_512(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      case SignatureScheme::RIPEMD160withECDSA:
        if (!(EVP_DigestInit_ex(md_ctx, EVP_ripemd160(), NULL)))
        {
          throw "EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!";
        }
        break;
      default:
        throw "EVP_MD_CTX_init Error! Unsupport type";
      }
      break;
    case KeyType::SM2:
      throw "EVP_MD_CTX_init Error! Unsupport type: KeyType::SM2";
      break;
    case KeyType::EDDSA:
      throw "EVP_MD_CTX_init Error! Unsupport type: KeyType::EDDSA";
      break;
    default:
      throw "EVP_MD_CTX_init Error! Unsupport type";
    }
  }

  void md_ctx_veri_init()
  {
    switch (key_type)
    {
      switch (sign_scheme)
      {
      case SignatureScheme::SHA224withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha224(), NULL)))
        {
          return false;
        }
        break;
      case SignatureScheme::SHA256withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha256(), NULL)))
        {
          return false;
        }
        break;
      case SignatureScheme::SHA384withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha384(), NULL)))
        {
          return false;
        }
        break;
      case SignatureScheme::SHA512withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha512(), NULL)))
        {
          return false;
        }
        break;
      case SignatureScheme::SHA3_224withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_224(), NULL)))
        {
          return false;
        }
        break;
      case SignatureScheme::SHA3_256withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_256(), NULL)))
        {
          return false;
        }
        break;
      case SignatureScheme::SHA3_384withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_384(), NULL)))
        {
          return false;
        }
        break;
      case SignatureScheme::SHA3_512withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_512(), NULL)))
        {
          return false;
        }
        break;
      case SignatureScheme::RIPEMD160withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_ripemd160(), NULL)))
        {
          return false;
        }
        break;
      default:
        throw "EVP_MD_CTX_init Error! Unsupport type";
      }
    case KeyType::SM2:
      throw "EVP_MD_CTX_init Error! Unsupport type: KeyType::SM2";
      break;
    case KeyType::EDDSA:
      throw "EVP_MD_CTX_init Error! Unsupport type: KeyType::EDDSA";
      break;
    default:
      throw "EVP_MD_CTX_init Error! Unsupport type";
    }
  }

public:
  SignatureHandler(KeyType _type, SignatureScheme _scheme)
      : _type(type), _scheme(scheme)
  {
    md_ctx = EVP_MD_CTX_new();
    if (md_ctx == NULL)
    {
      throw "EVP_MD_CTX_new() error";
    }
  }

  ~SignatureHandler() { EVP_MD_CTX_free(md_ctx); }

  std::vector<unsigned char> generateSignature(EVP_PKEY *evp_pkey,
                                               std::vector<unsigned char> msg, std::string sm2_param)
  {
    try
    {
      md_ctx_sign_init();
    }
    catch (const char *err)
    {
      std::cerr << err << std::endl;
    }
    std::string str_msg(msg.begin(), msg.end());
    if (EVP_SignUpdate(md_ctx, (unsigned char *)str_msg.c_str(),
                       str_msg.length()) != 1)
    {
      throw "EVP_SignUpdate() error!";
    }
    unsigned int slen = 0;
    char *uc_sign_dgst = (char *)malloc(EVP_MAX_MD_SIZE);
    while (slen != strlen(uc_sign_dgst))
    {
      if (EVP_SignFinal(md_ctx, (unsigned char *)uc_sign_dgst, &slen, evp_pkey) !=
          1)
      {
        throw "EVP_SignFinal() error!";
      }
    }
    std::vector<unsigned char> vec_sign_dgst(
        uc_sign_dgst, uc_sign_dgst + strlen(uc_sign_dgst));
    return vec_sign_dgsts;
  }

  bool verifySignature(EVP_PKEY *evp_pkey, std::vector<unsigned char> msg,
                       std::vector<unsigned char> sig)
  {
    try
    {
      md_ctx_veri_init();
    }
    catch (const char *err)
    {
      std::cerr << err << std::endl;
    }
    std::string str_msg(msg.begin(), msg.end());

    if (EVP_VerifyUpdate(md_ctx, (unsigned char *)str_msg.c_str(),
                         str_msg.length()) != 1)
    {
      return false;
    }
    int ret;
    ret = EVP_VerifyFinal(md_ctx, (unsigned char *)str_sign_dgst.c_str(),
                          str_sign_dgst.length(), evp_pkey);

    if (ret != 1)
    {
      return false;
    }
    return true;
  }
};

#endif