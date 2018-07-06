#ifndef SIGNATUREHANDLER_H
#define SIGNATUREHANDLER_H

#include <ostream>
#include <stdexcept>
#include <vector>

#include <openssl/bio.h>
#include <openssl/conf.h>
#include <openssl/ec.h>    // for EC_GROUP_new_by_curve_name, EC_GROUP_free, EC_KEY_new, EC_KEY_set_group, EC_KEY_generate_key, EC_KEY_free
#include <openssl/ecdsa.h> // for ECDSA_do_sign, ECDSA_do_verify
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

#include "../common/ErrorCode.h"
#include "KeyType.h"
#include "SignatureScheme.h"

class SignatureHandler
{
private:
  KeyType keyType;
  SignatureScheme signScheme;
  CurveName curveName;
  EVP_MD_CTX *md_ctx;

protected:
  void md_ctx_sign_init()
  {
    switch (keyType)
    {
    case KeyType::ECDSA:
      switch (signScheme)
      {
      case SignatureScheme::SHA224withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha224(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      case SignatureScheme::SHA256withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha256(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      case SignatureScheme::SHA384withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha384(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      case SignatureScheme::SHA512withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha512(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      case SignatureScheme::SHA3_224withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_224(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      case SignatureScheme::SHA3_256withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_256(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      case SignatureScheme::SHA3_384withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_384(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      case SignatureScheme::SHA3_512withECDSA:
        if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_512(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      case SignatureScheme::RIPEMD160withECDSA:
        if (!(EVP_DigestInit_ex(md_ctx, EVP_ripemd160(), NULL)))
        {
          throw runtime_error("EVP_MD_CTX_init Error! EVP_DigestInit_ex fail!");
        }
        break;
      default:
        throw runtime_error("EVP_MD_CTX_init Error! Unsupport type");
      }
      break;
    case KeyType::SM2:
      throw runtime_error(
          "EVP_MD_CTX_init Error! Unsupport type: KeyType::SM2");
      break;
    case KeyType::EDDSA:
      throw runtime_error(
          "EVP_MD_CTX_init Error! Unsupport type: KeyType::EDDSA");
      break;
    default:
      throw runtime_error("EVP_MD_CTX_init Error! Unsupport type");
    }
  }

  void md_ctx_veri_init()
  {
    switch (keyType)
    {
    case KeyType::ECDSA:
    {
      switch (signScheme)
      {
      case SignatureScheme::SHA224withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha224(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      case SignatureScheme::SHA256withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha256(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      case SignatureScheme::SHA384withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha384(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      case SignatureScheme::SHA512withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha512(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      case SignatureScheme::SHA3_224withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_224(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      case SignatureScheme::SHA3_256withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_256(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      case SignatureScheme::SHA3_384withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_384(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      case SignatureScheme::SHA3_512withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_512(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      case SignatureScheme::RIPEMD160withECDSA:
        if (!(EVP_VerifyInit_ex(md_ctx, EVP_ripemd160(), NULL)))
        {
          throw runtime_error("EVP_VerifyInit_ex() failed.");
        }
        break;
      default:
        throw runtime_error("EVP_MD_CTX_init Error! Unsupport type");
      }
    case KeyType::SM2:
      throw runtime_error(
          "EVP_MD_CTX_init Error! Unsupport type: KeyType::SM2");
      break;
    case KeyType::EDDSA:
      throw runtime_error(
          "EVP_MD_CTX_init Error! Unsupport type: KeyType::EDDSA");
      break;
    default:
      throw runtime_error("EVP_MD_CTX_init Error! Unsupport type");
    }
    }
  }

  std::string Signature::EC_set_public_key(const std::string &str_public_key,
                                           EC_KEY *ec_key)
  {
    if (ec_key == NULL)
    {
      throw std::runtime_error("EC_KEY is NULL");
    }

    EC_GROUP *group;
    group = EC_GROUP_new_by_curve_name(get_curve_nid(curve_name));
    if (group == NULL)
    {
      throw std::runtime_error("EC_GROUP_new_by_curve_name() failed.");
    }

    EC_POINT *pub;
    pub = EC_POINT_new(group);
    pub = EC_POINT_hex2point(group, str_public_key.c_str(), NULL, NULL);

    if (EC_KEY_set_public_key(ec_key, pub) != 1)
    {
      EC_KEY_free(ec_key);
      EC_GROUP_free(group);
      return false;
    }
    return true;
  }

  std::string
  Signature::EC_set_private_key(const std::string &str_private_key)
  {
    EC_GROUP *group;
    group = EC_GROUP_new_by_curve_name(get_curve_nid(curve_name));
    if (group == NULL)
    {
      return false;
    }

    if (ec_key == NULL)
    {
      EC_GROUP_free(group);
      return false;
    }
    BIGNUM *prv = BN_new();
    BN_hex2bn(&prv, str_private_key.c_str());
    if (EC_KEY_set_private_key(ec_key, prv) != 1)
    {
      EC_KEY_free(ec_key);
      EC_GROUP_free(group);
      return false;
    }
    return true;
  }

public:
  SignatureHandler(KeyType _type, SignatureScheme _scheme, CurveName _curve)
      : keyType(_type), signScheme(_scheme), curveName(_curve)
  {
    md_ctx = EVP_MD_CTX_new();
    if (md_ctx == NULL)
    {
      throw runtime_error("EVP_MD_CTX_new() failed.");
    }
  }

  ~SignatureHandler() { EVP_MD_CTX_free(md_ctx); }

  std::vector<unsigned char> generateSignature(const std::string &privateKey,
                                               std::vector<unsigned char> msg,
                                               std::string sm2_param)
  {
    try
    {
      md_ctx_sign_init();
    }
    catch (const std::runtime_error &err)
    {
      std::cerr << err.what() << std::endl;
    }
    std::string str_msg(msg.begin(), msg.end());
    if (EVP_SignUpdate(md_ctx, (unsigned char *)str_msg.c_str(),
                       str_msg.length()) != 1)
    {
      throw runtime_error("EVP_SignUpdate() failed.");
    }
    unsigned int slen = 0;
    char *uc_sign_dgst = (char *)malloc(EVP_MAX_MD_SIZE);

    EVP_PKEY *evp_pkey;

    while (slen != strlen(uc_sign_dgst))
    {
      if (EVP_SignFinal(md_ctx, (unsigned char *)uc_sign_dgst, &slen,
                        evp_pkey) != 1)
      {
        throw runtime_error("EVP_SignFinal() failed.");
      }
    }
    std::vector<unsigned char> vec_sign_dgst(
        uc_sign_dgst, uc_sign_dgst + strlen(uc_sign_dgst));
    return vec_sign_dgsts;
  }

  std::vector<unsigned char> generateSignature(std::string privateKey,
                                               std::vector<unsigned char> msg,
                                               CurveName curve_name,
                                               std::string sm2_param)
  {
    BIGNUM *prv = BN_new();
    BN_hex2bn(&prv, privateKey.c_str());

    EC_KEY *ec_key;
    ec_key =
        EC_KEY_new_by_curve_name(CurveNameMethod::get_curve_nid(curve_name));
    if (ec_key == NULL)
    {
      throw runtime_error(ErrorCode::StrResultIsNull);
    }

    EC_KEY_set_private_key(ec_key, prv);
    EC_POINT *pub;

    const EC_GROUP *group;
    group =
        EC_GROUP_new_by_curve_name(CurveNameMethod::get_curve_nid(curve_name));
    pub = EC_POINT_new(group);

    BN_CTX *bn_ctx;
    bn_ctx = BN_CTX_new();
    if (EC_POINT_mul(group, pub, prv, NULL, NULL, bn_ctx) != 1)
    {
      throw runtime_error(ErrorCode::StrDataSignatureErr);
    }
    if (EC_KEY_set_public_key(ec_key, pub) != 1)
    {
      EC_KEY_free(ec_key);
      throw runtime_error(ErrorCode::StrDataSignatureErr);
    }
    return true;
  }

  bool verifySignature(EVP_PKEY *evp_pkey, std::vector<unsigned char> msg,
                       std::vector<unsigned char> sig)
  {
    try
    {
      md_ctx_veri_init();
    }
    catch (const std::runtime_error &err)
    {
      std::cerr << err.what() << std::endl;
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