#ifndef VM_H
#define VM_H

#include "../../OntSdk.h"
#include "../../common/Helper.h"
#include "../../core/payload/InvokeCode.h"
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
    std::vector<unsigned char> _code;
    Helper helper;
    Address codeAddr;
    codeAddr = codeAddr.parse(codeAddr);
    if (vmtype == VmType::NEOVM) {
      Contract contract(unsigned char(0), _code, codeAddr, "", params);
      params = helper.addBytes(unsigned char(0x67), contract.toArray());
    } else if (vmtype == VmType::WASMVM) {
      Contract contract((unsigned char)1, _code, codeAddr, method, params);
      params = contract.toArray();
    } else if (vmtype == VmType::Native) {
      Contract contract((unsigned char)0, _code, codeAddr, method, params);
      params = contract.toArray();
    } else {
      throw "IllegalArgumentException";
    }
    // TODO
    InvokeCode tx;
    return tx;
  }
};
#endif