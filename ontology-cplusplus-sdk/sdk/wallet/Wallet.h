#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <list>

#include "Identity.h"
#include "Account.h"

class Wallet {
    private:
    std::string name;
    std::string version;
    std::string createTime;
    std::string defaultOntid;
    std::string defaultAccountAddress;
    // Scrypt scrypt;
    // Object extra;
    std::list<Identity> identities;
    std::list<Account> accounts;
    public:
    Wallet(){
        name = "com.github.ontio";
        version = "1.0";
        createTime = "";
        defaultOntid = "";
        defaultAccountAddress = "";
    }
};
#endif // !WALLET_H