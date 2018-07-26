#ifndef SIGNABLE_H
#define SIGNABLE_H

#if __cplusplus < 201103L
    #error "use --std=c++11 option for compile."
#endif

#include <vector>

#include "../account/Account.h"
#include "../common/Address.h"
#include "../common/UIntBase.h"
#include "../crypto/Signature.h"
#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "../io/Serializable.h"

class Signable : public Serializable
{
protected:
  Signable() : Serializable() {}

public:
  virtual void deserializeUnsigned(BinaryReader *reader) = 0;
  virtual void serializeUnsigned(BinaryWriter *writer) = 0;

  std::vector<unsigned char> getHashData()
  {
    BinaryWriter writer;
    serializeUnsigned(&writer);
    std::vector<unsigned char> bytes;
    bytes = writer.toByteArray();
    return bytes;
  }

  std::vector<unsigned char> sign(Account account, SignatureScheme scheme,
                                  CurveName curve)
  {
    std::vector<unsigned char> hash_data;
    hash_data = Digest::hash256(Digest::sha256(getHashData()));
    return account.generateSignature(hash_data);
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