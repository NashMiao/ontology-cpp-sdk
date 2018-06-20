#ifndef ONTSDK_H
#define ONTSDK_H

#include "account/Account.h"
#include "core/asset/Sig.h"
#include "crypto/Signature.h"
#include "sdk/manager/OntAssetTx.h"
#include "sdk/manager/WalletMgr.h"

#include <vector>

class OntSdk {
private:
  WalletMgr walletMgr;
  const SignatureScheme static defaultSignScheme =
      SignatureScheme::SHA256withECDSA;
  const CurveName static defaultCurveName = CurveName::p256;
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
  OntSdk() {}

  SignatureScheme getDefaultSignScheme() { return defaultSignScheme; }

  CurveName getCurveName() { return defaultCurveName; }

  static void signTx(Transaction &tx, const std::vector<Account> &accounts) {
    std::vector<Sig> sigs;
    for (size_t i = 0; i < accounts.size(); i++) {
      Sig sig_item;
      for (size_t j = 0; j < accounts.size(); j++) {
        std::vector<unsigned char> pub_key;
        std::vector<unsigned char> signature;
        pub_key = accounts[j].serializePublicKey();
        signature = tx.sign(accounts[j], defaultSignScheme, defaultCurveName);
        sig_item.add_M();
        sig_item.add_sigData(signature);
        sig_item.add_pubKeys(pub_key);
      }
      sigs.push_back(sig_item);
    }
    tx.set_sigs(sigs);
  }

  static void addMultiSign(Transaction &tx, int M,
                           const std::vector<Account> &acct) {
    std::vector<Sig> _sigs;
    for (int i = 0; i < tx.sigs_length(); i++) {
      _sigs.push_back(tx.get_sig(i));
    }
    std::vector<std::string> _pubKeys;
    std::vector<std::string> _sigData;
    for (size_t i = 0; i < acct.size(); i++) {
      _pubKeys.push_back((acct[i].serializePublicKey_str()));
      _sigData.push_back(
          (tx.sign_str(acct[i], defaultSignScheme, defaultCurveName)));
      Sig sig_item(_pubKeys, M, _sigData);
      _sigs.push_back(sig_item);
    }
    tx.set_sigs(_sigs);
  }
};
#endif // !ONTSDK_H