#ifndef VM_H
#define VM_H

#include "../../OntSdk.h"
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
  // TODO:
  // InvokeCode makeInvokeCodeTransaction(std::string codeAddr, std::string method,
  //                                      std::vector<unsigned char> params, byte vmtype, String payer,
  //                                      long gaslimit,
  //                                      long gasprice){
  //   if (vmtype == VmType.NEOVM.value()) {
  //     Contract contract =
  //         new Contract((byte)0, null, Address.parse(codeAddr), "", params);
  //     params = Helper.addBytes(new byte[]{0x67}, contract.toArray());
  //   } else if (vmtype == VmType.WASMVM.value()) {
  //     Contract contract =
  //         new Contract((byte)1, null, Address.parse(codeAddr), method, params);
  //     params = contract.toArray();
  //   } else if (vmtype == VmType.Native.value()) {
  //     Contract contract =
  //         new Contract((byte)0, null, Address.parse(codeAddr), method, params);
  //     params = contract.toArray();
  //   }
  //   InvokeCode tx = new InvokeCode();
  //   tx.attributes = new Attribute[1];
  //   tx.attributes[0] = new Attribute();
  //   tx.attributes[0].usage = AttributeUsage.Nonce;
  //   tx.attributes[0].data = UUID.randomUUID().toString().getBytes();
  //   tx.code = params;
  //   tx.gasLimit = gaslimit;
  //   tx.gasPrice = gasprice;
  //   if (payer != null) {
  //     tx.payer = Address.decodeBase58(payer.replace(Common.didont, ""));
  //   }

  // //   tx.vmType = vmtype;
  //   return tx;
  // }
};
#endif