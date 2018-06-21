#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../common/Address.h"
#include "../crypto/KeyType.h"
#include "../crypto/Signature.h"
#include "../crypto/SignatureScheme.h"

#include <string>
#include <vector>

class Account {
private:
  EVP_PKEY *evp_key;
  EC_KEY *ec_key;
  std::string PrivateKey;
  std::string PublicKey;
  KeyType keyType;
  Address addressU160;
  SignatureScheme signatureScheme;
  CurveName curve_name;

public:
  Account() {
    evp_key = EVP_PKEY_new();
    ec_key = EC_KEY_new();
  }
  Account(SignatureScheme scheme) {
    evp_key = EVP_PKEY_new();
    ec_key = EC_KEY_new();
    addressU160 = Address::addressFromPubKey(serializePublicKey());
  }
  Account(std::vector<unsigned char> private_key,
          SignatureScheme scheme = SignatureScheme::SHA256withECDSA,
          CurveName curve_name = CurveName::p256) {
    evp_key = EVP_PKEY_new();
    ec_key = EC_KEY_new();
    signatureScheme = scheme;
    if (signatureScheme == SignatureScheme::SM3withSM2) {
      keyType = KeyType::SM2;
    } else if (signatureScheme == SignatureScheme::SHA256withECDSA) {
      keyType = KeyType::ECDSA;
    } else {
      throw "SignatureScheme Error!";
    }
    switch (signatureScheme) {
    case SignatureScheme::SHA256withECDSA: {
      std::string str_pri_key(private_key.begin(), private_key.end());
      Signature ec_sign(scheme, curve_name, str_pri_key);
      ec_key = ec_sign.get_EC_key();
      std::vector<unsigned char> uc_pub_key;
      uc_pub_key = serializePublicKey();
      addressU160 = Address::addressFromPubKey(uc_pub_key);
      break;
    }
    case SignatureScheme::SM3withSM2: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA224withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA384withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA512withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA3_224withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA3_256withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA3_384withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA3_512withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::RIPEMD160withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    default: { throw "Exception(ErrorCode.UnsupportedKeyType)"; }
    }
  }

  ~Account() {
    if (evp_key != NULL) {
      EVP_PKEY_free(evp_key);
    }
    // if (ec_key != NULL) {
    //   EC_KEY_free(ec_key);
    // }
    EVP_cleanup();
  }

  void setAccount(std::string private_key,
                  SignatureScheme scheme = SignatureScheme::SHA256withECDSA,
                  CurveName curve_name = CurveName::p256) {
    signatureScheme = scheme;
    if (signatureScheme == SignatureScheme::SM3withSM2) {
      keyType = KeyType::SM2;
    } else if (signatureScheme == SignatureScheme::SHA256withECDSA) {
      keyType = KeyType::ECDSA;
    } else {
      throw "SignatureScheme Error!";
    }
    switch (signatureScheme) {
    case SignatureScheme::SHA256withECDSA: {
      Signature ec_sign(scheme, curve_name, private_key);
      ec_key = ec_sign.get_EC_key();
      std::vector<unsigned char> uc_pub_key;
      uc_pub_key = serializePublicKey();
      addressU160 = Address::addressFromPubKey(uc_pub_key);
      break;
    }
    case SignatureScheme::SM3withSM2: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA224withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA384withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA512withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA3_224withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA3_256withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA3_384withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::SHA3_512withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    case SignatureScheme::RIPEMD160withECDSA: {
      throw "SignatureScheme Unsupport";
      break;
    }
    default: { throw "Exception(ErrorCode.UnsupportedKeyType)"; }
    }
  }

  Address getAddressU160() { return addressU160; }

  std::vector<unsigned char>
  generateSignature(std::string msg, SignatureScheme scheme, CurveName curve) {
    if (msg.empty()) {
      throw "ErrorCode.InvalidMessage";
    }
    if (PrivateKey.empty()) {
      throw "ErrorCode.WithoutPrivate";
    }

    Signature signature(signatureScheme, curve, PrivateKey, msg);
    std::vector<unsigned char> uc_vec = signature.toBytes();
    return uc_vec;
  }

  std::vector<unsigned char> generateSignature(std::vector<unsigned char> msg,
                                               SignatureScheme scheme,
                                               CurveName curve) {
    if (msg.empty()) {
      throw "ErrorCode.InvalidMessage";
    }
    if (PrivateKey.empty()) {
      throw "ErrorCode.WithoutPrivate";
    }
    std::string str_msg(msg.begin(), msg.end());
    Signature signature(signatureScheme, curve, PrivateKey, str_msg);
    std::vector<unsigned char> uc_vec = signature.toBytes();
    return uc_vec;
  }

  std::vector<unsigned char> serializePublicKey() const {
    std::vector<unsigned char> act_uc_vec;
    try {
      switch (keyType) {
      case KeyType::ECDSA: {
        Signature sig;
        std::vector<unsigned char> ec_q;
        ec_q = sig.get_EC_Q(ec_key);
        act_uc_vec.insert(act_uc_vec.end(), ec_q.begin(), ec_q.end());
        break;
      }
      case KeyType::SM2: {
        throw "Exception(KeyType::SM2)";
        break;
      }
      default: { throw "Exception(ErrorCode.UnknownKeyType)"; }
      }
    } catch (const char *e) {
      cerr << e << endl;
    }
    return act_uc_vec;
  }

  std::string serializePublicKey_str() const {
    std::vector<unsigned char> pubkey_vec;
    pubkey_vec = serializePublicKey();
    std::string str(pubkey_vec.begin(), pubkey_vec.end());
    return str;
  }

  bool verifySignature(std::vector<unsigned char> msg,
                       std::vector<Signature> signature) {
    return true;
  }
};

#endif