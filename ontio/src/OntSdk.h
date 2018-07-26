#ifndef ONTIO_ONTSDK_H
#define ONTIO_ONTSDK_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <vector>

#include "account/Account.h"
#include "common/Common.h"
#include "common/ErrorCode.h"
#include "core/asset/Sig.h"
#include "core/payload/InvokeCodeTransaction.h"
#include "core/transaction/Transaction.h"
#include "crypto/Signature.h"
#include "sdk/manager/ConnectMgr.h"
#include "sdk/manager/OntAssetTx.h"
#include "sdk/manager/WalletMgr.h"

class Vm;

class OntSdk {
private:
  WalletMgr walletMgr;
  const SignatureScheme static defaultSignScheme =
      SignatureScheme::SHA256withECDSA;
  const CurveName static defaultCurveName = CurveName::p256;
  long long DEFAULT_GAS_LIMIT = 30000;
  static constexpr const int MULTI_SIG_MAX_PUBKEY_SIZE = 16;
  ConnectMgr connectRpc;
  ConnectMgr connectRestful;
  ConnectMgr connectWebSocket;
  ConnectMgr connectDefault;
  Vm *vm;

  // Nep5Tx nep5Tx = null;
  // OntIdTx ontIdTx = null;
  // RecordTx recordTx = null;
  // SmartcodeTx smartcodeTx = null;
  // OntAssetTx ontAssetTx;
  // ClaimRecordTx claimRecordTx = null;
  // static OntSdk instance = null;

public:
  OntSdk() {}

  Vm *getVm();

  static SignatureScheme getDefaultSignScheme() { return defaultSignScheme; }

  static CurveName getDefaultCurveName() { return defaultCurveName; }

  void setDefaultConnect(ConnectMgr connect);
  void setConnectTestNet();
  void setConnectMainNet();
  ConnectMgr getWebSocket();
  ConnectMgr getRpc();
  ConnectMgr getRestful();
  ConnectMgr getConnect();

  static void signTx(InvokeCodeTransaction &tx,
                     const std::vector<Account> &accounts);
  static void addSign(InvokeCodeTransaction &tx, const Account &acct);
  static void addMultiSign(InvokeCodeTransaction &tx, int M,
                           const std::vector<Account> &acct);
  // static void addMultiSign(InvokeCodeTransaction &tx, int M,
  //                          std::vector<std::string> pubKeys, Account acct)
  //     throws(SDKException)
  // {
  //   Program::sortPublicKeys(pubKeys);
  //   if (tx.sigs_length() > Common::TX_MAX_SIG_SIZE || M > pubKeys.size() ||
  //       M <= 0)
  //   {
  //     throw new SDKException(ErrorCode::ParamError);
  //   }
  //   for (int i = 0; i < tx.sigs_length(); i++)
  //   {
  //     if (tx.sigs[i].pubKeys == pubKeys)
  //     {
  //       if (tx.sigs[i].sigData_length() + 1 > pubKeys.size())
  //       {
  //         throw new SDKException(ErrorCode::ParamErr("too more sigData"));
  //       }
  //       sigData.push_back(tx.sign(acct,
  //       acct.getSignatureScheme(),acct.getCurveName()));
  //       tx.add_sig(sigData);
  //     }
  //   }
  // }
};
#endif // !ONTSDK_H