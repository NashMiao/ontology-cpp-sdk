#ifndef WALLET_ACCOUNTPARAM_H
#define WALLET_ACCOUNTPARAM_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>

#include <nlohmann/json.hpp>

#include "../../common/Helper.h"

class AccountParame
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
  std::string salt;
  std::string hash;
  std::string signatureScheme;
  std::string passwordHash;
  nlohmann::json extra;

public:
  AccountParame()
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

  std::vector<unsigned char> getSalt()
  {
    std::string str_salt = Helper::base64Decode(salt, false);
    return std::vector<unsigned char>(str_salt.begin(), str_salt.end());
  }
  void setSalt(const std::vector<unsigned char> &vec_salt) { salt = Helper::base64Encode(vec_salt, false); }

  std::string toString()
  {
    nlohmann::json j;
    j["label"] = label;
    j["address"] = address;
    j["isDefault"] = isDefault;
    j["lock"] = lock;
    j["algorithm"] = algorithm;
    j["parameters"] = parameters;
    j["key"] = key;
    j["enc-alg"] = encAlg;
    j["salt"] = salt;
    j["hash"] = hash;
    j["signatureScheme"] = signatureScheme;
    j["extra"] = extra;
    return j.dump();
  }
};

#endif // !WALLET_ACCOUNT_H