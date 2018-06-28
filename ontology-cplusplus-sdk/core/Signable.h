#ifndef SIGNABLE_H
#define SIGNABLE_H

#include "../account/Account.h"
#include "../crypto/Signature.h"
#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "../io/Serializable.h"

#include <vector>

class Signable
{
public:
  Signable() {}
  virtual void deserializeUnsigned(BinaryReader *reader){};
  virtual void serializeUnsigned(BinaryWriter *writer){};
  
  std::vector<unsigned char> getHashData()
  {
    BinaryWriter writer;
    serializeUnsigned(&writer);
    return writer.toByteArray();
  }

  std::vector<unsigned char> sign(Account account, SignatureScheme scheme,
                                  CurveName curve)
  {
    return account.generateSignature(getHashData(), scheme, curve);
  }

  std::string sign_str(Account account, SignatureScheme scheme,
                       CurveName curve)
  {
    std::vector<unsigned char> vec;
    vec = sign(account, scheme, curve);
    std::string str(vec.begin(), vec.end());
    return str;
  }
  // bool verifySignature(Account account, std::vector<unsigned char> data,
  //                      std::vector<unsigned char> signature) {
  //   return account.verifySignature(data, signature);
  // }
};

#endif