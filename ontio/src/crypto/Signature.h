#ifndef SIGNATURE_H
#define SIGNATURE_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <stdexcept>
#include <string>
#include <vector>

#include <openssl/ec.h>

#include "../common/ErrorCode.h"
#include "../sdk/exception/SDKException.h"
#include "Curve.h"
#include "SignatureScheme.h"

class Signature
{
private:
  SignatureScheme scheme;
  std::vector<unsigned char> value;
  std::string sm2_param;

public:
  Signature(SignatureScheme _scheme,
            const std::vector<unsigned char> &signature,
            const std::string &_sm2_param)
      : scheme(_scheme), value(signature), sm2_param(_sm2_param) {}

  // parse a serialized bytes to signature structure
  Signature(const std::vector<unsigned char> &data)
  {
    if (data.empty())
    {
      throw new SDKException(ErrorCode::ParamError);
    }
    if (data.size() < 2)
    {
      throw std::runtime_error(ErrorCode::StrInvalidSignatureDataLen);
    }
    scheme = SignatureSchemeMethod::toSignatureScheme(data[0]);
    if (scheme == SignatureScheme::SM3withSM2)
    {
      size_t i = 0;
      size_t data_sz = data.size();
      while (i < data_sz && data[i] != 0)
      {
        i++;
      }
      if (i >= data_sz)
      {
        throw std::runtime_error(ErrorCode::StrInvalidSignatureData);
      }
      sm2_param = std::string(data.begin(), data.begin() + i);
      value.assign(data.begin() + i + 1, data.end());
    }
    else
    {
      value = data;
    }
  }

  SignatureScheme getScheme() { return scheme; }

  std::vector<unsigned char> getValue() { return value; }

  // serialize to byte array
  std::vector<unsigned char> toBytes()
  {
    std::vector<unsigned char> bytes;
    bytes.reserve(value.size() + 1);
    bytes.push_back((unsigned char)SignatureSchemeMethod::ordinal(scheme));
    if (scheme == SignatureScheme::SM3withSM2)
    {
      // adding the ID
      bytes.insert(bytes.end(), sm2_param.begin(), sm2_param.end());
      // padding a 0 as the terminator
      bytes.push_back((unsigned char)0);
    }
    bytes.insert(bytes.end(), value.begin(), value.end());
    return bytes;
  }

  static std::string EC_get_pubkey_by_prikey(
      const std::string &str_private_key, CurveName curve_name,
      point_conversion_form_t from = POINT_CONVERSION_COMPRESSED)
  {
    BIGNUM *prv = BN_new();
    BN_hex2bn(&prv, str_private_key.c_str());
    EC_KEY *ec_key;
    ec_key =
        EC_KEY_new_by_curve_name(CurveNameMethod::get_curve_nid(curve_name));
    if (ec_key == NULL)
    {
      throw std::runtime_error("EC_KEY_new_by_curve_name() failed!");
    }
    const EC_GROUP *group;
    group =
        EC_GROUP_new_by_curve_name(CurveNameMethod::get_curve_nid(curve_name));
    EC_KEY_set_private_key(ec_key, prv);

    EC_POINT *pub;
    pub = EC_POINT_new(group);

    BN_CTX *bn_ctx;
    bn_ctx = BN_CTX_new();
    if (EC_POINT_mul(group, pub, prv, NULL, NULL, bn_ctx) != 1)
    {
      throw std::runtime_error("EC_POINT_mul() failed!");
    }
    if (EC_KEY_set_public_key(ec_key, pub) != 1)
    {
      EC_KEY_free(ec_key);
      throw std::runtime_error("EC_KEY_set_public_key() failed!");
    }
    std::string publicKey;
    publicKey = EC_POINT_point2hex(group, pub, from, bn_ctx);
    return publicKey;
  }
};

#endif