#ifndef VM_H
#define VM_H

#include "../OntSdk.h"
#include "../common/Address.h"
#include "../common/Common.h"
#include "../common/Helper.h"
#include "../core/payload/InvokeCodeTransaction.h"
#include <vector>

class Vm
{
private:
  OntSdk sdk;
  std::string contractAddress;
  static constexpr const char * NATIVE_INVOKE_NAME = "Ontology.Native.Invoke";

public:
  Vm() {}
  Vm(OntSdk _sdk) : sdk(_sdk) {}
  void setCodeAddress(std::string codeHash)
  {
    if (codeHash.at(0) == '0' &&
        (codeHash.at(1) == 'x' || codeHash.at(1) == 'X'))
    {
      codeHash = codeHash.substr(2);
    }
    contractAddress = codeHash;
  }
  std::string getCodeAddress() { return contractAddress; }

  InvokeCodeTransaction
  makeInvokeCodeTransaction(std::string codeAddr, std::string method,
                            std::vector<unsigned char> params,
                            std::string payer, long long gaslimit,
                            long long gasprice)
  {
    std::vector<unsigned char> params_item;
    params_item.push_back(0x67);
    params = Helper::addBytes(params, params_item);
    Address code_address;
    code_address = Address::parse(codeAddr);
    params_item = code_address.toArray();
    params = Helper::addBytes(params, params_item);
    size_t didont_pos = 0;
    didont_pos = payer.find(Common::didont);
    if (didont_pos != 0)
    {
      payer.replace(didont_pos, Common::didont.size(), "");
    }
    Address payer_address;
    payer_address = payer_address.decodeBase58(payer);
    InvokeCodeTransaction tx(params, gasprice, gaslimit, payer_address);
    return tx;
  }

  InvokeCodeTransaction
  makeInvokeCodeTransaction(const std::vector<unsigned char> &params,
                            std::string payer, long long gaslimit,
                            long long gasprice)
  {
    size_t didont_pos = 0;
    didont_pos = payer.find(Common::didont);
    if (didont_pos != 0)
    {
      payer.replace(didont_pos, Common::didont.size(), "");
    }
    Address payer_address;
    payer_address = payer_address.decodeBase58(payer);
    InvokeCodeTransaction tx(params, gasprice, gaslimit, payer_address);
    return tx;
  }

  InvokeCodeTransaction buildNativeParams(Address codeAddr,
                                          std::string initMethod,
                                          std::vector<unsigned char> args,
                                          std::string payer, long long gaslimit,
                                          long long gasprice)
  {
    ScriptBuilder builder;
    if (args.size() > 0)
    {
      builder.add(args);
    }
    builder.push(initMethod);
    builder.push(codeAddr.toArray());
    BIGNUM *bn;
    bn = BN_new();
    BN_set_word(bn, 0);
    builder.push(bn);
    BN_free(bn);
    builder.add(getByte(ScriptOp::OP_SYSCALL));
    builder.push(NATIVE_INVOKE_NAME);
    std::vector<unsigned char> builder_vec = builder.toArray();
    InvokeCodeTransaction tx =
        makeInvokeCodeTransaction(builder_vec, payer, gaslimit, gasprice);
    return tx;
  }
};
#endif