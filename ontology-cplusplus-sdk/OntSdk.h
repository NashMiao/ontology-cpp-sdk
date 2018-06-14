#ifndef ONTSDK_H
#define ONTSDK_H

#include "core/asset/Sig.h"
#include "crypto/Signature.h"
#include "sdk/manager/OntAssetTx.h"
#include "sdk/manager/WalletMgr.h"

class OntSdk {
private:
  WalletMgr walletMgr;
  // ConnectMgr connRpc;
  // ConnectMgr connRestful;
  // ConnectMgr connWebSocket;
  // ConnectMgr connDefault;

  // Nep5Tx nep5Tx = null;
  // OntIdTx ontIdTx = null;
  // RecordTx recordTx = null;
  // SmartcodeTx smartcodeTx = null;
  // OntAssetTx ontAssetTx;
  // ClaimRecordTx claimRecordTx = null;
  // static OntSdk instance = null;

public:
  SignatureScheme signatureScheme;
  CurveName curve_nid;
  OntSdk() {
    signatureScheme = SignatureScheme::SHA256withECDSA;
    curve_nid = CurveName::p256;
  }

  Transaction signTx(Transaction tx, const std::vector<Account> &accounts) {
    std::vector<Sig> sigs;
    for (size_t i = 0; i < accounts.size(); i++) {
      Sig sig_item;
      for (size_t j = 0; j < accounts.size(); j++) {
        std::vector<unsigned char> pub_key;
        std::vector<unsigned char> signature;
        pub_key = accounts[j].serializePublicKey();
        signature = tx.sign(accounts[j], SignatureScheme, curve_nid);
        sig_item.add_M();
        sig_item.add_sigData(signature);
        sig_item.add_pubKeys(pub_key);
      }
      sigs.push_back(sig_item);
    }
    tx.set_sigs(sigs);
    return tx;
  }
};
#endif // !ONTSDK_H