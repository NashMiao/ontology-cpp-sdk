#ifndef ONT_H
#define ONT_H

#include "../../OntSdk.h"
#include "../../core/asset/State.h"
#include "../../core/transaction/Transaction.h"
#include <string>

class Ont {
private:
  OntSdk sdk;
  std::string ontContract;
  int precision;

public:
  Ont() {
    ontContract = "ff00000000000000000000000000000000000001";
    precision = 1;
  }
  std::string getContractAddress() { return ontContract; }

  Transaction makeTransfer(std::string sender, std::string recvAddr,
                           long amount, std::string payer, long long gaslimit,
                           long long gasprice) {
    if (sender.empty() || recvAddr.empty() || payer.empty()) {
      throw "SDKException.ParamErr: parameters should not be null";
    }
    if (amount <= 0 || gasprice < 0 || gaslimit < 0) {
      throw "SDKException.ParamErr: amount or gasprice or gaslimit should not "
            "be less than 0";
    }
    amount = amount * precision;
    Helper helper;
    std::vector<unsigned char> sender_vchRet;
    std::vector<unsigned char> recvAddr_vchRet;
    helper.DecodeBase58(sender, sender_vchRet);
    helper.DecodeBase58(sender, recvAddr_vchRet);
    State state(Address(sender_vchRet), Address(recvAddr_vchRet), amount);
    Transfers transfers = Transfers(state);
    Transaction tx =
        makeInvokeCodeTransaction(ontContract, "transfer", transfers.toArray(),
                                  VmType::Native, payer, gaslimit, gasprice);
    return tx;
  }
};

#endif