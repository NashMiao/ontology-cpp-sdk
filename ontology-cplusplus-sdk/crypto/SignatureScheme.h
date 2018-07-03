#ifndef SIGNATURESCHEME_H
#define SIGNATURESCHEME_H

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

#endif // !SIGNATURESCHEME_H
