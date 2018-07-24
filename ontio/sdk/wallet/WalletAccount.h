#ifndef WALLET_ACCOUNT_H
#define WALLET_ACCOUNT_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>

#include <nlohmann/json.hpp>

class WalletAccount
{
public:
  std::string label;
  std::string address;
  bool isDefault;
  bool lock;
  std::string algorithm;
  nlohmann::json parameters;
  std::string key;
  // @JSONField(name = "enc-alg")
  std::string encAlg;
  std::string hash;
  std::string signatureScheme;
  std::string passwordHash;
  // Object extra = null;
  WalletAccount()
  {
    label = "";
    address = "";
    isDefault = false;
    lock = false;
    algorithm = "";
    //    parameters = new HashMap();
    key = "";
    encAlg = "aes-256-ctr";
    hash = "sha256";
    signatureScheme = "SHA256withECDSA";
    passwordHash = "";
  }
};

#endif // !ACCOUNT_H