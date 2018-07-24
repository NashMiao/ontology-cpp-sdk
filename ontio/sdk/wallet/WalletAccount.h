#ifndef WALLET_ACCOUNT_H
#define WALLET_ACCOUNT_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>

#include <nlohmann/json.hpp>

#include "../../common/Helper.h"

class WalletAccount
{
private:
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
  nlohmann::json extra;

public:
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

  nlohmann::json getExtra() { return extra; }

  void setExtra(nlohmann::json extra) { extra = extra; }

  std::string getKey() { return key; }

  void setKey(std::string key) { key = key; }

  void setEncAlg(std::string encAlg) { encAlg = encAlg; }
  std::string getEncAlg() { return encAlg; }

  void setHash(std::string hash) { hash = hash; }
  std::string getHash() { return hash; }

  std::vector<unsigned char> getSalt() { return Helper:: }
  void setSalt(const std::vector<unsigned char> &salt)
  {
    salt = Helper::this.salt = new String(Base64.getEncoder().encode(salt));
  }

  @Override std::string toString()
  {
    return JSON.toJSONString(this);
  }
};

#endif // !WALLET_ACCOUNT_H