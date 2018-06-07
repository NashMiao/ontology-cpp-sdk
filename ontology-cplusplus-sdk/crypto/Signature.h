#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <openssl/evp.h>
#include <string>
#include <vector>

#include "./SignatureScheme.h"

class Signature {
private:
  SignatureScheme scheme;
  EVP_MD_CTX *md_ctx;
  std::vector<unsigned char> value;

public:
  Signature(SignatureScheme scheme, EVP_MD_CTX *md_ctx,
            std::vector<unsigned char> signature) {
    scheme = scheme;
    md_ctx = md_ctx;
    value = signature;
  }
};
#endif // SIGNATURE_H