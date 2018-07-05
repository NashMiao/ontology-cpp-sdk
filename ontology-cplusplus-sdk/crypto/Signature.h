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
      : scheme(_scheme, sm2_param(_sm2_param)), value(_value) {}

  // parse a serialized bytes to signature structure
  Signature(const std::vector<unsigned char> &data)
  {
    if (data.empty())
    {
      throw new SDKException(ErrorCode::ParamError);
    }
    if (data.size() < 2)
    {
      throw new runtime_error(ErrorCode::StrInvalidSignatureDataLen);
    }
    scheme = toSignatureScheme(data[0]);
    if (scheme == SignatureScheme::SM3withSM2)
    {
      size_t i = 0;
      size_t data_sz = data.size();
      while (i < data_sz && data[i] != 0)
      {
        i++;
      }
      if (i >= data_sz)
      {
        throw new runtime_error(ErrorCode::StrInvalidSignatureData);
      }
      sm2_param = new std::string(data.begin(), data.begin() + i);
      value.assign(data.begin() + i + 1, data.end());
    }
    else
    {
      value = data;
    }
  }

  SignatureScheme getScheme() { return scheme; }

  std::vector<unsigned char> getValue() { return value; }

  // serialize to byte array
  std::vector<unsigned char> toBytes()
  {
    std::vector<unsigned char> bytes;
    bytes.reserve(value.size() + 1);
    bytes.push_back((unsigned char)SignatureSchemeMethod::ordinal(scheme));
    if (scheme == SignatureScheme::SM3withSM2)
    {
      // adding the ID
      bytes.insert(bytes.end(), sm2_param.begin(), sm2_param.end());
      // padding a 0 as the terminator
      bytes.push_back((unsigned char)0);
    }
    bytes.insert(bytes.end(), value.begin(), value.end());
    return bytes;
  }
};

#endif