#ifndef VM_H
#define VM_H

#include "../../OntSdk.h"
#include "../../core/VmType.h"
#include <string>
#include <vector>

class Vm {
private:
  Ontsdk sdk;
  std::string contractAddress;

public:
  Vm(Ontsdk _sdk) { sdk = _sdk; }
  void setCodeAddress(std::string codeHash) {
    if (codeHash[0] == "0" && (codeHash[1] == "x" || codeHash[1] == "X")) {
      codeHash = codeHash.substr(2);
    }
    contractAddress = codeHash;
  }
  std::string getCodeAddress() { return contractAddress; }
  InvokeCode makeInvokeCodeTransaction(std::string codeAddr, std::string method,
                                       std::vector<unsigned char> params,
                                       unsigned char vmtype, String payer,
                                       long gaslimit, long gasprice) {
    std::vector<unsigned char> _code;
    if (vmtype == NEOVM) {
      Contract contract = new Contract((unsigned char)0, _code,
                                       Address.parse(codeAddr), "", params);
      params = Helper.addBytes(new unsigned char[]{0x67}, contract.toArray());
    } else if (vmtype == WASMVM) {
      Contract contract = new Contract((unsigned char)1, _code,
                                       Address.parse(codeAddr), method, params);
      params = contract.toArray();
    } else if (vmtype == Native) {
      Contract contract = new Contract((unsigned char)0, _code,
                                       Address.parse(codeAddr), method, params);
      params = contract.toArray();
    } else {
      throw "IllegalArgumentException";
    }
    InvokeCode tx = new InvokeCode();
    tx.attributes = new Attribute[1];
    tx.attributes[0] = new Attribute();
    tx.attributes[0].usage = AttributeUsage.Nonce;
    tx.attributes[0].data = UUID.randomUUID().toString().getBytes();
    tx.code = params;
    tx.gasLimit = gaslimit;
    tx.gasPrice = gasprice;
    if (payer != NULL) {
      tx.payer = Address.decodeBase58(payer.replace(Common.didont, ""));
    }

    //   tx.vmType = vmtype;
    return tx;
  }
};
#endif