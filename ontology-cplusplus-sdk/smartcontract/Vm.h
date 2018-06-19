#ifndef VM_H
#define VM_H

#include "../OntSdk.h"
#include "../common/Common.h"
#include "../common/Address.h"
#include "../common/Helper.h"
#include "../core/payload/InvokeCode.h"
#include <string>
#include <vector>

class Vm {
private:
  OntSdk sdk;
  std::string contractAddress;

public:
  Vm() {}
  Vm(Ontsdk _sdk) : sdk(_sdk) {}
  void setCodeAddress(std::string codeHash) {
    if (codeHash.at(0) == '0' &&
        (codeHash.at(1) == 'x' || codeHash.at(1) == 'X')) {
      codeHash = codeHash.substr(2);
    }
    contractAddress = codeHash;
  }
  std::string getCodeAddress() { return contractAddress; }
  InvokeCode makeInvokeCodeTransaction(std::string codeAddr, std::string method,
                                       std::vector<unsigned char> params,
                                       VmType vmtype, std::string payer,
                                       long long gaslimit, long long gasprice) {
    std::vector<unsigned char> params_item;
    params_item.push_back(0x67);
    params = Helper::addBytes(params, params_item);
    Address code_address;
    code_address = Address::parse(codeAddr);
    params_item=code_address.toArray();
    params = Helper::addBytes(params, params_item);
    sizt_t didont_pos=payer.find(Common::didont); 
    if(didont_pos!=0){
      payer.replace(didont_pos, Common::didont.size(), "");
    }
    Address payer_addresss;
    payer_address=payer_address.decodeBase58(payer);
    InvokeCode tx(params,gaslimit,gasprice,payer_address);
    return tx;
  }
};
#endif