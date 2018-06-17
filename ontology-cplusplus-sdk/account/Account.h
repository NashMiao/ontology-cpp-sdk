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
  std::string PrivateKey;
  std::string PublicKey;
  KeyType keyType;
  Address addressU160;
  SignatureScheme signatureScheme;

public:
  Account() {}
  Account(SignatureScheme scheme) {
    evp_kep = EVP_PKEY_new();
    addressU160 = Address.addressFromPubKey(serializePublicKey());
  }
  Account(std::vector<unsigned char> prikey, SignatureScheme scheme) {
    signatureScheme = scheme;
    if (scheme == SignatureScheme::SM3withSM2) {
      keyType = KeyTyp::SM2;
    } else if (scheme == SignatureScheme::SHA256withECDSA) {
      keyType = KeyType::ECDSA;
    } else {
      throw "SignatureScheme Error!";
    }
    switch (scheme) {
    case SignatureScheme::SHA256withECDSA:
    case SignatureScheme::SM3withSM2:
      evp_kep = EVP_PKEY_new();
      addressU160 = Address.addressFromPubKey(serializePublicKey());
      break;
    default:
      throw "Exception(ErrorCode.UnsupportedKeyType)";
    }
  }

  ~Account() {
    if (ec_key != NULL) {
      EC_KEY_free(ec_key);
    }
    EVP_cleanup();
  }

  void setAccount(std::vector<unsigned char> prikey, SignatureScheme scheme) {
    signatureScheme = scheme;
    if (scheme == SignatureScheme::SM3withSM2) {
      keyType = KeyTyp::SM2;
    } else if (scheme == SignatureScheme::SHA256withECDSA) {
      keyType = KeyType::ECDSA;
    } else {
      throw "SignatureScheme Error!";
    }
    switch (scheme) {
    case SignatureScheme::SHA256withECDSA:
    case SignatureScheme::SM3withSM2:
      evp_kep = EVP_PKEY_new();
      addressU160 = Address.addressFromPubKey(serializePublicKey());
      break;
    default:
      throw "Exception(ErrorCode.UnsupportedKeyType)";
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

  std::vector<unsigned char> serializePublicKey() {
    std::vector<unsigned char> act_uc_vec;
    try {
      switch (KeyType) {
      case KeyType::ECDSA: {
        Signature sig;
        std::vector<unsigned char> ec_q;
        ec_q = sig.get_EC_Q(evp_key);
        act_uc_vec.insert(act_uc_vec.end(), ec_q.begin(), ec_q.end());
      } break;
      case KeyType::SM2:
        break;
      default:
        throw "Exception(ErrorCode.UnknownKeyType)";
      }
    } catch (const char *e) {
      cerr << e << endl;
    }
    return act_uc_vec;
  }

  bool verifySignature(std::vector<unsigned char> msg, std::vector signature) {
    return true;
  }
};

#endif