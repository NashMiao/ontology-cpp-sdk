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

class Ont {
private:
    OntSdk sdk;
    std::string ontContract;
    nlohmann::json nativeAbi;

public:
    Ont() {
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
                             long long gaslimit, long long gasprice) {
        if (amount <= 0 || gasprice < 0 || gaslimit < 0) {
            throw new SDKException(ErrorCode::ParamErr(
                    "amount or gasprice or gaslimit should not be less than 0"));
        }

        InvokeCodeTransaction tx =
                makeTransfer(sendAcct.getAddressU160().toBase58(), recvAddr, amount,
                             payerAcct.getAddressU160().toBase58(), gaslimit, gasprice);
        std::vector<Account> accounts = {sendAcct};
        OntSdk::signTx(tx, accounts);
        if (!sendAcct.equals(payerAcct)) {
            OntSdk::addSign(tx, payerAcct);
        }
        std::string ret_str = "";
        if (sdk.getConnect().sendRawTransaction(tx.toHexString())) {
            ret_str = Helper::toHexString(tx.hash());
        }
        return ret_str;
    }

    std::string sendTransferFromMultiSignAddr(
            int M, std::vector<std::string> pubKeys, std::vector<Account> sendAccts,
            std::string recvAddr, long long amount, const Account &payerAcct,
            long long gaslimit, long long gasprice){
        if (sendAccts.size() <= 1) {
            throw new SDKException(
                    ErrorCode::ParamErr("parameters should not be null"));
        }
        if (amount <= 0 || gasprice < 0 || gaslimit < 0) {
            throw new SDKException(ErrorCode::ParamErr(
                    "amount or gasprice or gaslimit should not be less than 0"));
        }

        Address multiAddr =
                Address::addressFromMultiPubKeys((int) sendAccts.size(), pubKeys);
        InvokeCodeTransaction tx =
                makeTransfer(multiAddr.toBase58(), recvAddr, amount,
                             payerAcct.getAddressU160().toBase58(), gaslimit, gasprice);
        for (size_t i = 0; i < sendAccts.size(); i++) {
            // sdk.addMultiSign(tx, M, pubKeys, sendAccts[i]); TODO
        }
        sdk.addSign(tx, payerAcct);
        std::string ret_str = "";
        if (sdk.getConnect().sendRawTransaction(tx.toHexString())) {
            ret_str = Helper::toHexString(tx.hash());
        }
        return ret_str;
    }

    InvokeCodeTransaction makeTransfer(const std::string &sender_str,
                                       const std::string &receiver_str, long long amount,
                                       const std::string &payer_str, long long gaslimit,
                                       long long gasprice) {
        if (sender_str.empty() || receiver_str.empty() || payer_str.empty()) {
            throw "SDKException.ParamErr: parameters should not be null";
        }
        if (amount <= 0 || gasprice < 0 || gaslimit < 0) {
            throw "SDKException.ParamErr: amount or gasprice or gaslimit should not "
                  "be less than 0";
        }
        Address sender_address;
        Address receiver_address;
        sender_address = Address::decodeBase58(sender_str);
        receiver_address = Address::decodeBase58(receiver_str);
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

    long long queryBalanceOf(std::string base58_address) {
        if (base58_address == "") {
            throw new SDKException(ErrorCode::ParamErr("address should not be null"));
        }
        Address address;
        address = Address::decodeBase58(base58_address);
        std::list<boost::any> any_list{address};
        std::vector<Struct> struct_vec{any_list};
        std::list<boost::any> structs_list{struct_vec};
        std::vector<unsigned char> args;
        NativeBuildParams native_build_params;
        args = native_build_params.createCodeParamsScript(structs_list);

        Address ContractAddress(Helper::hexToBytes(ontContract));
        std::string init_method = "balanceOf";
        InvokeCodeTransaction tx;
        Vm vm;
        std::string payer_str = "";
        long long gaslimit = 0;
        long long gasprice = 0;
        tx = vm.buildNativeParams(ContractAddress, init_method, args, payer_str,
                                  gaslimit, gasprice);
        cout << tx.json() << endl;
        std::string url = "http://localhost:20336";
        nlohmann::json obj;
        sdk.getVm();
        ConnectMgr connect_mgr(url, ConnectType::RPC);
        std::cout << "HexTx: " << tx.toHexString() << std::endl;
        try {
            obj = connect_mgr.sendRawTransactionPreExec(tx.toHexString());
            std::cout << obj << std::endl;
        }
        catch (std::runtime_error &err) {
            std::cerr << err.what() << std::endl;
        }
//    return tx;
        return -1;
    }
};

#endif