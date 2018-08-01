#ifndef ECC_H
#define ECC_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <exception>
#include <string>
#include <vector>

#include <openssl/asn1.h>
#include <openssl/rand.h>
#include <openssl/bn.h>
#include <openssl/ec.h>

#include "Curve.h"
#include "ECDomainParameters.h"

#if defined(WIN32) || defined(_WIN64)
#pragma comment(lib, "libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
#endif

class ECC
{
public:
  ECDomainParameters *secp256r1;
  ECDomainParameters *sm2p256v1;

  ECC()
  {
    secp256r1 = new ECDomainParameters(CurveName::p256);
    sm2p256v1 = new ECDomainParameters(CurveName::SM2P256V1);
  }

  static std::vector<unsigned char> generateKey(int len)
  {
    unsigned char key[len];
    if (RAND_bytes(key, len) != 1)
    {
      throw std::runtime_error("BAND_bytes() fail.");
    }
    return std::vector<unsigned char>(key, key + len);
  }

  static std::vector<unsigned char> generateKey()
  {
    return generateKey(32);
  }
};

#endif