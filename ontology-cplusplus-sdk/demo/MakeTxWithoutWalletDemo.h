#ifndef MAKETXWITHOUTWALLETDEMO_H
#define MAKETXWITHOUTWALLETDEMO_H

#include "../account/Account.h"
#include "../common/Address.h"
#include "../core/transaction/Transaction.h"
#include "../smartcontract/nativevm/Ont.h"
#include <string>

class MakeTxWithoutWalletDemo {
public:
  std::string privatekey1 =
      "49855b16636e70f100cc5f4f42bc20a6535d7414fb8845e7310f8dd065a97221";
  std::string privatekey2 =
      "1094e90dd7c4fdfd849c14798d725ac351ae0d924b29a279a9ffa77d5737bd96";
  std::string privatekey3 =
      "bc254cf8d3910bc615ba6bf09d4553846533ce4403bc24f58660ae150a6d64cf";
  std::string privatekey4 =
      "06bda156eda61222693cc6f8488557550735c329bc7ca91bd2994c894cd3cbc8";
  std::string privatekey5 =
      "f07d5a2be17bde8632ec08083af8c760b41b5e8e0b5de3703683c3bdcfb91549";
  std::string privatekey6 =
      "6c2c7eade4c5cb7c9d4d6d85bfda3da62aa358dd5b55de408d6a6947c18b9279";
  std::string privatekey7 =
      "24ab4d1d345be1f385c75caf2e1d22bdb58ef4b650c0308d9d69d21242ba8618";
  std::string privatekey8 =
      "87a209d232d6b4f3edfcf5c34434aa56871c2cb204c263f6b891b95bc5837cac";
  std::string privatekey9 =
      "1383ed1fe570b6673351f1a30a66b21204918ef8f673e864769fa2a653401114";
  std::string ontContractAddr = "ff00000000000000000000000000000000000001";

  void transer() {
    Address sender;
    sender.set_zero(std::string("TA4WVfUB1ipHL8s3PRSYgeV1HhAU3KcKTq"));
    Address recvAddr;
    recvAddr.set_zero(std::string("TA5SgQXTeKWyN4GNfWGoXqioEQ4eCDFMqE"));
    long long amount = 1000;
    Ont ont;
    Transaction tx = ont.makeTransfer(sender, recvAddr, amount, sender, 30000, 0);
  }
};
#endif