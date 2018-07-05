#ifndef SIGNATURESCHEME_H
#define SIGNATURESCHEME_H

#include <string>

enum class SignatureScheme
{
  SHA224withECDSA,
  SHA256withECDSA,
  SHA384withECDSA,
  SHA512withECDSA,
  SHA3_224withECDSA,
  SHA3_256withECDSA,
  SHA3_384withECDSA,
  SHA3_512withECDSA,
  RIPEMD160withECDSA,
  SM3withSM2
};

static int ordinal(SignatureScheme scheme)
{
  int ret;
  switch (scheme)
  {
  case SignatureScheme::SHA224withECDSA:
    ret = 0;
    break;
  case SignatureScheme::SHA256withECDSA:
    ret = 1;
    break;
  case SignatureScheme::SHA384withECDSA:
    ret = 2;
    break;
  case SignatureScheme::SHA512withECDSA:
    ret = 3;
    break;
  case SignatureScheme::SHA3_224withECDSA:
    ret = 4;
    break;
  case SignatureScheme::SHA3_256withECDSA:
    ret = 5;
    break;
  case SignatureScheme::SHA3_384withECDSA:
    ret = 6;
    break;
  case SignatureScheme::SHA3_512withECDSA:
    ret = 7;
    break;
  case SignatureScheme::RIPEMD160withECDSA:
    ret = 8;
    break;
  case SignatureScheme::SM3withSM2:
    ret = 9;
    break;
  default:
    throw "SignatureScheme Error!";
    break;
  }
  return ret;
}

std::string toString(SignatureScheme scheme)
{
  std::string name;
  switch (scheme)
  {
  case SignatureScheme::SHA224withECDSA:
    name = "SHA224withECDSA";
    break;
  case SignatureScheme::SHA256withECDSA:
    name = "SHA256withECDSA";
    break;
  case SignatureScheme::SHA384withECDSA:
    name = "SHA384withECDSA";
    break;
  case SignatureScheme::SHA512withECDSA:
    name = "SHA5112withECDSA";
    break;
  case SignatureScheme::SHA3_224withECDSA:
    name = "SHA3_224withECDSA";
    break;
  case SignatureScheme::SHA3_256withECDSA:
    name = "SHA3_256withECDS";
    break;
  case SignatureScheme::SHA3_384withECDSA:
    name = "SHA3_384withECDSA";
    break;
  case SignatureScheme::SHA3_512withECDSA:
    name = "SHA3_512withECDS";
    break;
  case SignatureScheme::RIPEMD160withECDSA:
    name = "RIPEMD160withECDSA";
    break;
  case SignatureScheme::SM3withSM2:
    name = "SM3withSM2";
    break;
  default:
    throw "SignatureScheme Error!";
    break;
  }
  return name;
}

static SignatureScheme fromScheme(std::string name)
{
  SignatureScheme scheme;
  switch (name)
  {
  case "SHA224withECDSA":
    scheme = SignatureScheme::SHA224withECDSA;
    break;
  case "SHA256withECDSA":
    scheme = SignatureScheme::SHA256withECDSA;
    break;
  case "SHA384withECDSA":
    scheme = SignatureScheme::SHA384withECDSA;
    break;
  case "SHA5112withECDSA":
    scheme = SignatureScheme::SHA512withECDSA;
    break;
  case "SHA3_224withECDSA":
    scheme = SignatureScheme::SHA3_224withECDSA;
    break;
  case "SHA3_256withECDS":
    scheme = SignatureScheme::SHA3_256withECDSA;
    break;
  case "SHA3_384withECDSA":
    scheme = SignatureScheme::SHA3_384withECDSA;
    break;
  case "SHA3_512withECDS":
    scheme = SignatureScheme::SHA3_512withECDSA;
    break;
  case "RIPEMD160withECDSA":
    scheme = SignatureScheme::RIPEMD160withECDSA;
    break;
  case "SM3withSM2":
    scheme = SignatureScheme::SM3withSM2;
    break;
  default:
    throw "SignatureScheme Error!";
    break;
  }
  return scheme;
}

static SignatureScheme toSignatureScheme(unsigned char value)
{
  SignatureScheme scheme;
  switch (value)
  {
  case 0x00:
    SignatureScheme::SHA224withECDSA;
    break;
  case 0x01:
    scheme = SignatureScheme::SHA256withECDSA;
    break;
  case 0x02:
    scheme = SignatureScheme::SHA384withECDSA;
    break;
  case 0x03:
    scheme = SignatureScheme::SHA512withECDSA;
    break;
  case 0x04:
    scheme = SignatureScheme::SHA3_224withECDSA;
    break;
  case 0x05:
    scheme = SignatureScheme::SHA3_256withECDSA;
    break;
  case 0x06:
    scheme = SignatureScheme::SHA3_384withECDSA;
    break;
  case 0x07:
    scheme = SignatureScheme::SHA3_512withECDSA;
    break;
  case 0x08:
    scheme = SignatureScheme::RIPEMD160withECDSA;
    break;
  case 0x09:
    scheme = SignatureScheme::SM3withSM2;
    break;
  default:
    throw runtime_error("toSignatureScheme() Error: Unsupport SignatureScheme");
    break;
  }
  return scheme;
}

#endif // !SIGNATURESCHEME_H
