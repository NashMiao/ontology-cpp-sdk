#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../common/Address.h"
#include "../crypto/Sign.h"
#include "../crypto/SignatureScheme.h"

class Account {
private:
  EVP_PKEY *PrivateKey;
  EVP_PKEY *PublicKey;
  Address addressU160;
  SignatureScheme signatureScheme;

public:
  Account(SignatureScheme scheme) {
    addressU160 = Address.addressFromPubKey(serializePublicKey());
  }
  Address getAddressU160() { return addressU160; }
};

#endif