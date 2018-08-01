#ifndef WALLET_H
#define WALLET_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>
#include <list>

#include <nlohmann/json.hpp>

#include "Identity.h"
#include "ScryptParam.h"
#include "AccountParam.h"

class Wallet
{
private:
  std::string name;
  std::string version;
  std::string createTime;
  std::string defaultOntid;
  std::string defaultAccountAddress;
  ScryptParam scryptParam;
  nlohmann::json extra;
  std::list<Identity> identities;
  std::list<AccountParame> accounts;

public:
  Wallet()
  {
    name = "com.github.ontio";
    version = "1.0";
  }

      nlohmann::json getExtra() {
        return extra;
    }

    void setExtra(nlohmann::json extra) {
        extra = extra;
    }

    std::string getName() {
        return name;
    }

    void setName(std::string name) {
        name = name;
    }

    std::string getDefaultOntid() {
        return defaultOntid;
    }

    void setDefaultOntid(std::string defaultOntid) {
        defaultOntid = defaultOntid;
    }

    std::string getCreateTime() {
        return createTime;
    }

    void setCreateTime(std::string createTime) {
        createTime = createTime;
    }

    std::string getDefaultAccountAddress() {
        return defaultAccountAddress;
    }

    void setDefaultAccountAddress(std::string defaultAccountAddress) {
        defaultAccountAddress = defaultAccountAddress;
    }

    std::string getVersion() {
        return version;
    }

    void setVersion(std::string version) {
        version = version;
    }

    ScryptParam getScrypt() {
        return scryptParam;
    }

    void setScrypt(ScryptParam scrypt) {
        scrypt = scrypt;
    }

    std::list<Identity> getIdentities() {
        return identities;
    }

    void setIdentities(std::list<Identity> identityList) {
        identities = identityList;
    }

    std::list<AccountParame> getAccounts() {
        return accounts;
    }

    void setAccounts(std::list<AccountParame> accountList) {
        accounts = accountList;
    }
};
#endif // !WALLET_H