#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../crypto/Curve.h"
#include "../crypto/SignatureScheme.h"


class Account {
private:
  EVP_PKEY *PrivateKey;
  EVP_PKEY *PublicKey;
};

#endif