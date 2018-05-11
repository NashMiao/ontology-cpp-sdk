#ifndef WALLET_H
#define WALLET_H

#include <string>
#include <list>

class Wallet {
    private:
    std::string name = "com.github.ontio";
    std::string version = "1.0";
    std::string createTime = "";
    std::string defaultOntid = "";
    std::string defaultAccountAddress = "";
    Scrypt scrypt = new Scrypt();
    Object extra = null;
    std::list<Identity> identities = new ArrayList<Identity>();
    std::list<Account> accounts = new ArrayList<>();
};
#endif // !WALLET_H