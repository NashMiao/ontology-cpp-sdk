#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
#include <unordered_map>

class Account {
public:
  std::string label;
  std::string address;
  bool isDefault;
  bool lock;
  std::string algorithm;
  std::unordered_map<int, int> parameters;
  std::string key;
  // @JSONField(name = "enc-alg")
  std::string encAlg;
  std::string hash;
  std::string signatureScheme;
  std::string passwordHash;
  // Object extra = null;
  Account() {
    label = "";
    address = "";
    isDefault = false;
    lock = false;
    algorithm = "";
    //    parameters = new HashMap();
    key = "";
    // @JSONField(name = "enc-alg")
    encAlg = "aes-256-ctr";
    hash = "sha256";
    signatureScheme = "SHA256withECDSA";
    passwordHash = "";
  }
};

#endif // !ACCOUNT_H