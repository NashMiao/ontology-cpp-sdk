#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../common/Address.h"
#include "../crypto/Signature.h"
#include "../crypto/SignatureScheme.h"

#include <string>
#include <vector>

class Account {
private:
  std::string PrivateKey;
  std::string PublicKey;
  Address addressU160;
  SignatureScheme signatureScheme;

public:
  Account(SignatureScheme scheme) {
    addressU160 = Address.addressFromPubKey(serializePublicKey());
  }
  Address getAddressU160() { return addressU160; }

  std::vector<unsigned char> generateSignature(std::string msg, SignatureScheme scheme, CurveName curve) {
    if (msg.length == 0) {
      throw "ErrorCode.InvalidMessage";
    }
    if (PrivateKey == NULL) {
      throw "ErrorCode.WithoutPrivate";
    }

    Signature signature(signatureScheme, curve, PrivateKey, msg);
    std::vector<unsigned char> uc_vec = signature.toBytes();
    return uc_vec;
  }

  bool verifySignature(std::vector<unsigned char> msg, std::vector signature){
    
  }
};

#endif