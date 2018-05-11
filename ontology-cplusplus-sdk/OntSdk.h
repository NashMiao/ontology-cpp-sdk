#ifndef ONTSDK_H
#define ONTSDK_H

#include "sdk/manager/WalletMgr.h"
#include "sdk/manager/OntAssetTx.h"
#include "crypto/Sign.h"

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
        signatureScheme = SHA256withECDSA;
    }
};
#endif // !ONTSDK_H