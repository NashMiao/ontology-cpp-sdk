#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <stdexcept>
#include <string>
#include <vector>

#include "../common/Address.h"
#include "../crypto/KeyType.h"
#include "../crypto/Signature.h"
#include "../crypto/SignatureHandler.h"
#include "../crypto/SignatureScheme.h"

class Account
{
private:
  std::string curveParams;
  std::string privateKey;
  std::string publicKey;
  KeyType keyType;
  Address addressU160;
  SignatureScheme signatureScheme;
  CurveName curve_name;
  std::string sm2Param;

private:
  void parsePublicKey(const std::vector<unsigned char> &data)
  {
    if (data.size() == 0)
    {
      throw runtime_error(ErrorCode::StrNullInput);
    }
    if (data.size() < 2)
    {
      throw runtime_error(ErrorCode::StrInvalidData);
    }
    if (data.size() == 33)
    {
      keyType = KeyType::ECDSA;
    }
    else if (data.size() == 35)
    {
      keyType = keyTypeFromLabel(data[0]);
    }
    switch (keyType)
    {
    case KeyType::ECDSA:
    {
      curveParams = CurveNameMethod::toString(CurveName::p256);
      break;
    }
    case KeyType::SM2:
      break;
    default:
      break;
    }
  }

public:
  Account() {}

  Account(SignatureScheme scheme)
  {
    addressU160 = Address::addressFromPubKey(serializePublicKey());
  }

  explicit Account(std::string private_key,
                   SignatureScheme scheme = SignatureScheme::SHA256withECDSA,
                   CurveName _curve_name = CurveName::p256,
                   std::string sm2_param = "")
      : privateKey(private_key), signatureScheme(scheme),
        curve_name(_curve_name), sm2Param(sm2_param)
  {
    signatureScheme = scheme;
    if (signatureScheme == SignatureScheme::SM3withSM2)
    {
      keyType = KeyType::SM2;
    }
    else if (signatureScheme == SignatureScheme::SHA256withECDSA)
    {
      keyType = KeyType::ECDSA;
    }
    else
    {
      throw std::runtime_error("SignatureScheme Error!");
    }
    switch (signatureScheme)
    {
    case SignatureScheme::SHA256withECDSA:
    {
      privateKey = private_key;
      publicKey = Signature::EC_get_pubkey_by_prikey(privateKey, curve_name);
      // ec_key = ec_sign.get_EC_key();
      std::vector<unsigned char> uc_pub_key;
      uc_pub_key = serializePublicKey();
      addressU160 = Address::addressFromPubKey(uc_pub_key);
      break;
    }
    case SignatureScheme::SM3withSM2:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA224withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA384withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA512withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_224withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_256withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_384withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_512withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::RIPEMD160withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    default:
    {
      throw "Exception(ErrorCode.UnsupportedKeyType)";
    }
    }
  }

  // construct an account from a serialized pubic key or private key
  Account(bool fromPrivate, std::vector<unsigned char> pubkey)
  {
    if (fromPrivate)
    {
      // parsePrivateKey(data);
    }
    else
    {
      parsePublicKey(pubkey);
    }
  }

  ~Account() {}

  Account operator=(Account &acct)
  {
    this->curveParams = acct.curveParams;
    this->privateKey = acct.privateKey;
    this->publicKey = acct.publicKey;
    this->keyType = acct.keyType;
    this->addressU160 = acct.addressU160;
    this->signatureScheme = acct.signatureScheme;
    this->curve_name = acct.curve_name;
    this->sm2Param = acct.sm2Param;
    return *this;
  }

  Account *operator=(Account *acct)
  {
    this->curveParams = acct->curveParams;
    this->privateKey = acct->privateKey;
    this->publicKey = acct->publicKey;
    this->keyType = acct->keyType;
    this->addressU160 = acct->addressU160;
    this->signatureScheme = acct->signatureScheme;
    this->curve_name = acct->curve_name;
    this->sm2Param = acct->sm2Param;
    return this;
  }

  void setAccount(std::string private_key,
                  SignatureScheme scheme = SignatureScheme::SHA256withECDSA,
                  CurveName curve_name = CurveName::p256)
  {
    signatureScheme = scheme;
    if (signatureScheme == SignatureScheme::SM3withSM2)
    {
      keyType = KeyType::SM2;
    }
    else if (signatureScheme == SignatureScheme::SHA256withECDSA)
    {
      keyType = KeyType::ECDSA;
    }
    else
    {
      throw "SignatureScheme Error!";
    }
    switch (signatureScheme)
    {
    case SignatureScheme::SHA256withECDSA:
    {
      privateKey = private_key;
      publicKey = Signature::EC_get_pubkey_by_prikey(privateKey, curve_name);
      std::vector<unsigned char> uc_pub_key;
      uc_pub_key = serializePublicKey();
      addressU160 = Address::addressFromPubKey(uc_pub_key);
      break;
    }
    case SignatureScheme::SM3withSM2:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA224withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA384withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA512withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_224withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_256withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_384withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_512withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::RIPEMD160withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    default:
    {
      throw "Exception(ErrorCode.UnsupportedKeyType)";
    }
    }
  }

  Address getAddressU160() { return addressU160; }

  std::vector<unsigned char> generateSignature(std::vector<unsigned char> msg)
  {
    if (msg.empty())
    {
      throw new runtime_error(ErrorCode::StrInvalidMessage);
    }
    if (privateKey.empty())
    {
      throw new runtime_error(ErrorCode::StrWithoutPrivate);
    }
    if (signatureScheme == SignatureScheme::SM3withSM2)
    {
      if (sm2Param.empty())
      {
        sm2Param = "1234567812345678";
      }
    }
    SignatureHandler sign_handler(KeyType, signatureScheme);
    sign_handler.generateSignature(privateKey, msg, sm2Param);

    std::string str_msg(msg.begin(), msg.end());
    Signature signature(signatureScheme, curve_name, privateKey);
    signature.EC_sign(str_msg);
    std::vector<unsigned char> uc_vec = signature.toBytes();
    return uc_vec;
  }

  std::vector<unsigned char> serializePublicKey() const
  {
    std::vector<unsigned char> act_uc_vec;
    switch (keyType)
    {
    case KeyType::ECDSA:
    {
      act_uc_vec.insert(act_uc_vec.end(), publicKey.begin(), publicKey.end());
      break;
    }
    case KeyType::SM2:
    {
      throw "Exception(KeyType::SM2)";
      break;
    }
    default:
    {
      throw runtime_error(ErrorCode::StrUnknownKeyType);
    }
    }

    return act_uc_vec;
  }

  std::string serializePublicKey_str() const { return publicKey; }

  bool verifySignature(std::vector<unsigned char> msg,
                       std::vector<Signature> signature)
  {
    return true;
  }
};

#endif