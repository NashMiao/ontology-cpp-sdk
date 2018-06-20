#ifndef ONT_H
#define ONT_H

#include "../../OntSdk.h"
#include "../../core/VmType.h"
#include "../../core/asset/State.h"
#include "../../core/asset/Transfers.h"
#include "../../core/transaction/Transaction.h"
#include "../../smartcontract/nativevm/abi/NativeBuildParams.h"
#include "../Vm.h"
#include "abi/NativeBuildParams.h"
#include <list>
#include <string>

class Ont
{
private:
  OntSdk sdk;
  std::string ontContract;
  int precision;

public:
  Ont()
  {
    ontContract = "ff00000000000000000000000000000000000001";
    precision = 1;
  }
  std::string getContractAddress() { return ontContract; }

  InvokeCodeTransaction makeTransfer(std::string sender_str,
                                     std::string receiver_str, long long amount,
                                     std::string payer_str, long long gaslimit,
                                     long long gasprice)
  {
    if (sender_str.empty() || receiver_str.empty() || payer_str.empty())
    {
      throw "SDKException.ParamErr: parameters should not be null";
    }
    if (amount <= 0 || gasprice < 0 || gaslimit < 0)
    {
      throw "SDKException.ParamErr: amount or gasprice or gaslimit should not "
            "be less than 0";
    }
    amount = amount * precision;
    Address sender_address;
    Address receiver_address;
    sender_address = sender_address.decodeBase58(sender_str);
    receiver_address = receiver_address.decodeBase58(receiver_str);
    std::list<boost::any> any_list{sender_address, receiver_address, amount};
    std::vector<Struct> struct_vec{any_list};

    std::list<boost::any> structs_list{struct_vec};
    std::vector<unsigned char> args;
    NativeBuildParams native_build_params;
    args = native_build_params.createCodeParamsScript(structs_list);

    Address ContractAddress(Helper::hexToBytes(ontContract));
    std::string init_method = "transfer";

    InvokeCodeTransaction tx;
    tx = Vm::buildNativeParams(ContractAddress, init_method, args, payer_str,
                               gaslimit, gasprice);
    return tx;
  }
};

#endif