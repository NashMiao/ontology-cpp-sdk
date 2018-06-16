#ifndef ONTSDK_H
#define ONTSDK_H

#include "core/asset/Sig.h"
#include "crypto/Signature.h"
#include "sdk/manager/OntAssetTx.h"
#include "sdk/manager/WalletMgr.h"

class OntSdk {
private:
  WalletMgr walletMgr;
  SignatureScheme defaultSignScheme = SignatureScheme::SHA256WITHECDSA;
  CurveName defaultCurveName = CurveName::p256;
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

  Transaction addMultiSign(Transaction tx, int M, std::vector<Account> acct) {
    std::vector<Sig> _sigs;
    for (int i = 0; i < tx.sigs_length(); i++) {
      _sigs.push_back(tx.get_sig(i));
    }
    std::vector<std::string> _pubKeys;
    std::vector<std::string> _sigData;
    for (int i = 0; i < acct.size(); i++) {
      _pubKeys.push_back(acct[i].serializePublicKey());
      _sigData.push_back(tx.sign(acct[i], defaultSignScheme, defaultCurveName));
      Sig sig_item(_pubKeys, M, _sigData);
      _sigs.push_back(sig_item);
    }
    tx.set_sigs(_sigs);
    return tx;
  }
};
#endif // !ONTSDK_H