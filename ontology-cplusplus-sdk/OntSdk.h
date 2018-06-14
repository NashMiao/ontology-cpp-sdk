#ifndef ONTSDK_H
#define ONTSDK_H

#include "sdk/manager/WalletMgr.h"
#include "sdk/manager/OntAssetTx.h"
#include "crypto/Signature.h"
#include "core/asset/Sig.h"

class OntSdk
{
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
    OntSdk()
    {
        signatureScheme = SignatureScheme::SHA256withECDSA;
    }

    Transaction signTx(Transaction tx, std::vector<Account> accounts){
      std::vector<Sig> sigs;
      for (int i = 0; i < accounts.size();i++){
        Sig sig_item;
      }
    }
};
#endif // !ONTSDK_H