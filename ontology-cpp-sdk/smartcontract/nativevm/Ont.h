#ifndef ONT_H
#define ONT_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <list>
#include <string>

#include <nlohmann/json.hpp>

#include "../../OntSdk.h"
#include "../../core/VmType.h"
#include "../../core/asset/State.h"
#include "../../core/asset/Transfers.h"
#include "../../core/transaction/Transaction.h"
#include "../../smartcontract/nativevm/abi/NativeBuildParams.h"
#include "../Vm.h"
#include "abi/NativeBuildParams.h"

class Ont
{
private:
  OntSdk sdk;
  std::string ontContract;
  nlohmann::json nativeAbi;

public:
  Ont()
  {
    ontContract = "0000000000000000000000000000000000000001";
    nativeAbi = {
        "hash",
        "0000000000000000000000000000000000000001",
        "functions",
        {{"name", "init", "parameters", {}, "returntype", "Bool"},
         {"name",
          "transfer",
          "parameters",
          {{"name",
            "transfers",
            "type",
            "Struct",
            "subType",
            {{"name", "from", "type", "Address"},
             {"name", "to", "type", "Address"},
             {"name", "value", "type", "Int"}}}},
          "returntype",
          "Bool"},
         {"name",
          "approve",
          "parameters",
          {{"name", "from", "type", "Address"},
           {"name", "to", "type", "Address"},
           {"name", "value", "type", "Int"}},
          "returntype",
          "Bool"},
         {"name",
          "transferFrom",
          "parameters",
          {{"name", "sender", "type", "Address"},
           {"name", "from", "type", "Address"},
           {"name", "to", "type", "Address"},
           {"name", "value", "type", "Int"}},
          "returntype",
          "Bool"},
         {"name", "name", "parameters", {}, "returntype", "String"},
         {"name", "symbol", "parameters", {}, "returntype", "String"},
         {"name", "decimals", "parameters", {}, "returntype", "Int"},
         {"name", "totalSupply", "parameters", {}, "returntype", "Int"},
         {"name",
          "balanceOf",
          "parameters",
          {{"name", "account", "type", "Address"}},
          "returntype",
          "Int"},
         {"name",
          "allowance",
          "parameters",
          {{"name", "account", "type", "Address"}},
          "returntype",
          "Int"}},
        "events",
        {{"name",
          "transfer",
          "parameters",
          {{"name", "from", "type", "Address"},
           {"name", "to", "type", "Address"},
           {"name", "value", "type", "Int"}}}}};
  }
  std::string getContractAddress() { return ontContract; }

  std::string sendTransfer(Account sendAcct, const std::string &recvAddr,
                           long long amount, Account payerAcct,
                           long long gaslimit, long long gasprice)
  {
    if (amount <= 0 || gasprice < 0 || gaslimit < 0)
    {
      throw new SDKException(ErrorCode::ParamErr(
          "amount or gasprice or gaslimit should not be less than 0"));
    }

    InvokeCodeTransaction tx =
        makeTransfer(sendAcct.getAddressU160().toBase58(), recvAddr, amount,
                     payerAcct.getAddressU160().toBase58(), gaslimit, gasprice);
    std::vector<Account> accounts = {sendAcct};
    OntSdk::signTx(tx, accounts);
    if (!sendAcct.equals(payerAcct))
    {
      OntSdk::addSign(tx, payerAcct);
    }
    std::string ret_str = "";
    if (sdk.getConnect().sendRawTransaction(tx.toHexString()))
    {
      ret_str = Helper::toHexString(tx.hash());
    }
    return ret_str;
  }

  std::string sendTransferFromMultiSignAddr(
      int M, std::vector<std::string> pubKeys, std::vector<Account> sendAccts,
      std::string recvAddr, long long amount, const Account &payerAcct,
      long long gaslimit, long long gasprice) throw(SDKException)
  {
    if (sendAccts.size() <= 1)
    {
      throw new SDKException(
          ErrorCode::ParamErr("parameters should not be null"));
    }
    if (amount <= 0 || gasprice < 0 || gaslimit < 0)
    {
      throw new SDKException(ErrorCode::ParamErr(
          "amount or gasprice or gaslimit should not be less than 0"));
    }

    Address multiAddr =
        Address::addressFromMultiPubKeys((int)sendAccts.size(), pubKeys);
    InvokeCodeTransaction tx =
        makeTransfer(multiAddr.toBase58(), recvAddr, amount,
                     payerAcct.getAddressU160().toBase58(), gaslimit, gasprice);
    for (size_t i = 0; i < sendAccts.size(); i++)
    {
      // sdk.addMultiSign(tx, M, pubKeys, sendAccts[i]); TODO
    }
    sdk.addSign(tx, payerAcct);
    std::string ret_str = "";
    if (sdk.getConnect().sendRawTransaction(tx.toHexString()))
    {
      ret_str = Helper::toHexString(tx.hash());
    }
    return ret_str;
  }

  InvokeCodeTransaction makeTransfer(const std::string &sender_str,
                                     const std::string &receiver_str, long long amount,
                                     const std::string &payer_str, long long gaslimit,
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
    Vm vm;
    tx = vm.buildNativeParams(ContractAddress, init_method, args, payer_str,
                              gaslimit, gasprice);
    return tx;
  }
};

#endif