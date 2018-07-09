#ifndef MAKETXWITHOUTWALLETDEMO_H
#define MAKETXWITHOUTWALLETDEMO_H

#include "../OntSdk.h"
#include "../account/Account.h"
#include "../common/Address.h"
#include "../core/payload/InvokeCodeTransaction.h"
#include "../core/transaction/Transaction.h"
#include "../sdk/manager/ConnectMgr.h"
#include "../smartcontract/nativevm/Ont.h"
#include "../smartcontract/nativevm/abi/Struct.h"
#include <string>

class MakeTxWithoutWalletDemo
{
  private:
    std::string privatekey0;
    std::string privatekey1;
    std::string privatekey2;
    std::string privatekey3;
    std::string privatekey4;
    std::string privatekey5;
    std::string privatekey6;
    std::string privatekey7;
    std::string privatekey8;
    std::string privatekey9;
    Account acct0;
    Account acct1;
    Account acct2;
    Account acct3;
    Account acct4;
    Account acct5;

    void privatekey_init()
    {
        privatekey0 =
            "523c5fcf74823831756f0bcb3634234f10b3beb1c05595058534577752ad2d9f";
        privatekey1 =
            "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
        privatekey2 =
            "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";
        privatekey3 =
            "bc254cf8d3910bc615ba6bf09d4553846533ce4403bc24f58660ae150a6d64cf";
        privatekey4 =
            "06bda156eda61222693cc6f8488557550735c329bc7ca91bd2994c894cd3cbc8";
        privatekey5 =
            "f07d5a2be17bde8632ec08083af8c760b41b5e8e0b5de3703683c3bdcfb91549";
        privatekey6 =
            "6c2c7eade4c5cb7c9d4d6d85bfda3da62aa358dd5b55de408d6a6947c18b9279";
        privatekey7 =
            "24ab4d1d345be1f385c75caf2e1d22bdb58ef4b650c0308d9d69d21242ba8618";
        privatekey8 =
            "87a209d232d6b4f3edfcf5c34434aa56871c2cb204c263f6b891b95bc5837cac";
        privatekey9 =
            "1383ed1fe570b6673351f1a30a66b21204918ef8f673e864769fa2a653401114";
    }

    void account_init()
    {
        acct0 = new Account(privatekey0, OntSdk::getDefaultSignScheme(),
                            OntSdk::getDefaultCurveName());
        acct1 = new Account(privatekey1, OntSdk::getDefaultSignScheme(),
                            OntSdk::getDefaultCurveName());
        acct2 = new Account(privatekey2, OntSdk::getDefaultSignScheme(),
                            OntSdk::getDefaultCurveName());
        acct3 = new Account(privatekey3, OntSdk::getDefaultSignScheme(),
                            OntSdk::getDefaultCurveName());
        acct4 = new Account(privatekey4, OntSdk::getDefaultSignScheme(),
                            OntSdk::getDefaultCurveName());
        acct5 = new Account(privatekey5, OntSdk::getDefaultSignScheme(),
                            OntSdk::getDefaultCurveName());
    }

  public:
    void init()
    {
        privatekey_init();
        account_init();
    }
    void transer()
    {
        // Address sender;
        // sender.set_zero(std::string("ANH5bHrrt111XwNEnuPZj6u95Dd6u7G4D6"));
        // Address recvAddr;
        // recvAddr.set_zero(std::string("AKJS7q95Wx7FThAtwqHyCqhfK7tQz5KCUt"));

        Address sender;
        sender = acct0.getAddressU160();
        Address recvAddr;
        std::vector<std::string> multiPubKey;
        multiPubKey.push_back(acct1.serializePublicKey_str());
        multiPubKey.push_back(acct2.serializePublicKey_str());
        recvAddr = recvAddr.addressFromMultiPubKeys(2, multiPubKey);
        std::cout << "sender: " << sender.toBase58() << std::endl;
        std::cout << "recvAddr: " << recvAddr.toBase58() << std::endl;

        long long amount = 100000;
        Ont ont;
        InvokeCodeTransaction tx;
        tx = ont.makeTransfer(sender.toBase58(), recvAddr.toBase58(), amount,
                              sender.toBase58(), 30000, 0);
        cout << tx.json() << endl;

        std::vector<Account> vec_accounts;
        vec_accounts.push_back(acct0);
        OntSdk::signTx(tx, vec_accounts);

        vec_accounts.push_back(acct1);
        int m = 2;
        OntSdk::addMultiSign(tx, m, vec_accounts);

        std::vector<unsigned char> tx_hash = tx.hash();
        std::vector<unsigned char>::const_iterator tx_hash_cit;
        for (tx_hash_cit = tx_hash.cbegin(); tx_hash_cit != tx_hash.cend();
             tx_hash_cit++)
        {
            cout << *tx_hash_cit;
        }
        cout << endl;
        std::string str_tx = tx.toHexString();
        cout << "------------------------------" << endl;
        cout << str_tx << endl;
        cout << "------------------------------" << endl;
        std::string url = "http://polaris1.ont.io:20334/api/v1/transaction ";
        nlohmann::json obj;
        ConnectMgr connect_mgr(url, ConnectType::RPC);
        obj = connect_mgr.sendRawTransactionPreExec(str_tx);
    }
};
#endif