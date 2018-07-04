#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <string>
#include <vector>

#include <openssl/ec.h>
#include <openssl/sm2.h>

#include "SignatureScheme.h"

class Signature
{
private:
  SignatureScheme scheme;
  std::string sm2_param;
  std::vector<unsigned char> value;

public:
  Signature(SignatureScheme _scheme, const std::string &_sm2_param,
            const std::vector<unsigned char> &_value)
      : _scheme(scheme), _sm2_param(sm2_param), _value(value) {}

  // parse a serialized bytes to signature structure
  Signature(const std::vector<unsigned char> &data)
  {
    if (data.empty())
    {
      throw new SDKException(ErrorCode.ParamError);
    }
    if (data.size() < 2)
    {
      throw new Exception(ErrorCode.InvalidSignatureDataLen);
    }
    scheme=
  }
};

#endif