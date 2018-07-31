#ifndef ONTIO_ACCOUNT_ACCOUNT_H
#define ONTIO_ACCOUNT_ACCOUNT_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <stdexcept>
#include <string>
#include <vector>

#include "../common/Address.h"
#include "../common/Helper.h"
#include "../crypto/AES.h"
#include "../crypto/KeyType.h"
#include "../crypto/ScryptHandler.h"
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
  CurveName curveName;
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
      keyType = KeyTypeMethod::fromLabel(data[0]);
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
      : privateKey(private_key),
        signatureScheme(scheme),
        curveName(_curve_name),
        sm2Param(sm2_param)
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
      publicKey = Signature::EC_get_pubkey_by_prikey(privateKey, curveName);
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
    this->curveName = acct.curveName;
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
    this->curveName = acct->curveName;
    this->sm2Param = acct->sm2Param;
    return this;
  }

  bool equals(const Account &acct)
  {
    return this->addressU160.equals(acct.addressU160);
  }

  void setAccount(std::string private_key,
                  SignatureScheme scheme = SignatureScheme::SHA256withECDSA,
                  CurveName curveName = CurveName::p256)
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
      publicKey = Signature::EC_get_pubkey_by_prikey(privateKey, curveName);
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

  Address getAddressU160() const { return addressU160; }

  SignatureScheme getSignatureScheme() { return signatureScheme; }

  CurveName getCurveName() { return curveName; }

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
    std::vector<unsigned char> sign_data;
    SignatureHandler sign_handler(keyType, signatureScheme, curveName);
    sign_data = sign_handler.generateSignature(privateKey, msg, sm2Param);
    Signature signature(signatureScheme, sign_data, sm2Param);
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
      act_uc_vec = Helper::hexStringToByte(publicKey);
      break;
    }
    case KeyType::SM2:
    {
      throw std::runtime_error("Exception(KeyType::SM2)");
      break;
    }
    default:
    {
      throw runtime_error(ErrorCode::StrUnknownKeyType);
    }
    }

    return act_uc_vec;
  }

  std::vector<unsigned char> serializePrivateKey()
  {
    std::vector<unsigned char> act_uc_vec;
    switch (keyType)
    {
    case KeyType::ECDSA:
    case KeyType::SM2:
      act_uc_vec = Helper::hexStringToByte(publicKey);
      break;
    default:
      throw new std::runtime_error(ErrorCode::StrUnknownKeyType);
    }
    return act_uc_vec;
  }

  std::string serializePublicKey_str() const { return publicKey; }

  bool verifySignature(std::vector<unsigned char> msg,
                       std::vector<Signature> signature)
  {
    return true;
  }

  std::string exportWif()
  {
    std::vector<unsigned char> data;
    data[0] = (unsigned char)0x80;
    std::vector<unsigned char> prikey = serializePrivateKey();
    data.insert(data.end(), prikey.begin(), prikey.end());
    data[33] = (unsigned char)0x01;
    std::vector<unsigned char> checksum =
        Digest::hash256(data, 0, (int)data.size() - 4);
    data.insert(data.end(), checksum.begin(), checksum.begin() + 4);
    std::string wif = Helper::EncodeBase58(data);
    return wif;
  }

  std::string exportGcmEncryptedPrikey(const std::string &password,
                                       const std::vector<unsigned char> &salt,
                                       const int n)
  {
    int r = 8;
    int p = 8;
    int dkLen = 64;
    if (salt.size() != 16)
    {
      throw new SDKException(ErrorCode::ParamError);
    }
    std::vector<unsigned char> derivedkey;
    derivedkey = ScryptHandler::scrypt(password, salt, n, r, p, dkLen);
    std::vector<unsigned char> aes_iv(derivedkey.begin(),
                                      derivedkey.begin() + 12);
    std::vector<unsigned char> aes_key(derivedkey.begin() + 32,
                                       derivedkey.begin() + 64);
    // AES/GCM/NoPadding
    std::vector<unsigned char> encryptedkey =
        AES::gcmEncrypt(serializePrivateKey(), aes_key, aes_iv, false);
    return Helper::base64Encode(encryptedkey, false);
  }

  static std::string getGcmDecodedPrivateKey(
      const std::string &encryptedPriKey, std::string password,
      std::string address, const std::vector<unsigned char> &salt, int n,
      SignatureScheme scheme)
  {
    if (encryptedPriKey.length() == 0)
    {
      throw new SDKException(ErrorCode::EncryptedPriKeyError);
    }
    if (salt.size() != 16)
    {
      throw new SDKException(ErrorCode::ParamError);
    }
    // AES/GCM/NoPadding
    std::string encryptedkey = Helper::base64Decode(encryptedPriKey, false);
    int r = 8;
    int p = 8;
    int dkLen = 64;
    std::vector<unsigned char> derivedkey;
    derivedkey = ScryptHandler::scrypt(password, salt, n, r, p, dkLen);
    std::vector<unsigned char> aes_iv(derivedkey.begin(),
                                      derivedkey.begin() + 12);
    std::vector<unsigned char> aes_key(derivedkey.begin() + 32,
                                       derivedkey.begin() + 64);
                                  

    std::vector<unsigned char> rawkey;
//    try
//    {
//      SecretKeySpec skeySpec = new SecretKeySpec(derivedhalf2, "AES");
//      Cipher cipher = Cipher.getInstance("AES/GCM/NoPadding");
//      cipher.init(Cipher.DECRYPT_MODE, skeySpec, new GCMParameterSpec(128, iv));
//      cipher.updateAAD(address.getBytes());
//      rawkey = cipher.doFinal(encryptedkey);
//    }
//    catch (Exception e)
//    {
//      e.printStackTrace();
//      throw new SDKException(ErrorCode.encryptedPriKeyAddressPasswordErr);
//    }
//    Account account = new Account(rawkey, scheme);
//    if (!address.equals(account.getAddressU160().toBase58()))
//    {
//      throw new SDKException(ErrorCode::encryptedPriKeyAddressPasswordErr);
//    }
    return Helper::toHexString(rawkey);
  }
};

#endif