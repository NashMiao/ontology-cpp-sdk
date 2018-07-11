#ifndef ONTSDK_H
#define ONTSDK_H

#include "account/Account.h"
#include "common/Common.h"
#include "core/asset/Sig.h"
#include "core/payload/InvokeCodeTransaction.h"
#include "core/transaction/Transaction.h"
#include "crypto/Signature.h"
#include "sdk/manager/ConnectMgr.h"
#include "sdk/manager/OntAssetTx.h"
#include "sdk/manager/WalletMgr.h"

#include <vector>

class OntSdk
{
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

  // Nep5Tx nep5Tx = null;
  // OntIdTx ontIdTx = null;
  // RecordTx recordTx = null;
  // SmartcodeTx smartcodeTx = null;
  // OntAssetTx ontAssetTx;
  // ClaimRecordTx claimRecordTx = null;
  // static OntSdk instance = null;

public:
  OntSdk() {}

  static SignatureScheme getDefaultSignScheme() { return defaultSignScheme; }

  static CurveName getDefaultCurveName() { return defaultCurveName; }

  void setDefaultConnect(ConnectMgr connect) { connectDefault = connect; }

  ConnectMgr getConnect()
  {
    if (&connectDefault != NULL)
    {
      return connectDefault;
    }
    else if (&connectRpc != NULL)
    {
      return connectRpc;
    }
    else if (&connectRestful != NULL)
    {
      return connectRestful;
    }
    else if (&connectWebSocket != NULL)
    {
      return connectWebSocket;
    }
    else
    {
      throw "getConnect(): connect uninint";
    }
  }

  ConnectMgr getWebSocket()
  {
    if (&connectWebSocket == NULL)
    {
      throw "SDKException(ErrorCode.WebsocketNotInit)";
    }
    return connectWebSocket;
  }

  static void signTx(InvokeCodeTransaction &tx,
                     const std::vector<Account> &accounts)
  {
    if (accounts.size() > Common::TX_MAX_SIG_SIZE)
    {
      throw SDKException(ErrorCode::StrParamErr(
          "the number of transaction signatures should not be over 16"));
    }
    std::vector<Sig> sigs;
    sigs.reserve(accounts.size());
    for (size_t i = 0; i < accounts.size(); i++)
    {
      Sig sig_item;
      for (size_t j = 0; j < accounts.size(); j++)
      {
        std::vector<unsigned char> pub_key;
        std::vector<unsigned char> signature;
        pub_key = accounts[j].serializePublicKey();
        signature = tx.sign(accounts[j], defaultSignScheme, defaultCurveName);
        sig_item.add_M();
        sig_item.add_pubKeys(pub_key);
        sig_item.add_sigData(signature);
      }
      sigs.push_back(sig_item);
    }
    tx.add_sigs(sigs);
  }

  static void addSign(InvokeCodeTransaction &tx, const Account &acct)
  {
    if (tx.sigs_length() > Common::TX_MAX_SIG_SIZE)
    {
      throw new SDKException(ErrorCode::ParamErr(
          "the number of transaction signatures should not be over 16"));
    }
    int m = 1;
    std::string pub_key = acct.serializePublicKey_str();
    std::string sig_data =
        tx.sign_str(acct, defaultSignScheme, defaultCurveName);
    Sig sig_item(pub_key, m, sig_data);
    tx.add_sig(sig_item);
  }

  static void addMultiSign(InvokeCodeTransaction &tx, int M,
                           const std::vector<Account> &acct)
  {
    if (tx.sigs_length() >= MULTI_SIG_MAX_PUBKEY_SIZE ||
        tx.sigs_length() + acct.size() > MULTI_SIG_MAX_PUBKEY_SIZE)
    {
      throw "the number of transaction signatures should not be over 16";
    }

    std::vector<Sig> _sigs;
    for (int i = 0; i < tx.sigs_length(); i++)
    {
      _sigs.push_back(tx.get_sig(i));
    }
    std::vector<std::string> _pubKeys;
    std::vector<std::string> _sigData;
    for (size_t i = 0; i < acct.size(); i++)
    {
      _pubKeys.push_back((acct[i].serializePublicKey_str()));
      _sigData.push_back(
          (tx.sign_str(acct[i], defaultSignScheme, defaultCurveName)));
      Sig sig_item(_pubKeys, M, _sigData);
      _sigs.push_back(sig_item);
    }
    tx.add_sigs(_sigs);
  }

  static void addMultiSign(InvokeCodeTransaction &tx, int M,
                           std::vector<std::string> pubKeys, Account acct)
      throws(SDKException)
  {
    Program::sortPublicKeys(pubKeys);
    if (tx.sigs_length() > Common::TX_MAX_SIG_SIZE || M > pubKeys.size() ||
        M <= 0)
    {
      throw new SDKException(ErrorCode::ParamError);
    }
    for (int i = 0; i < tx.sigs_length(); i++)
    {
      if (tx.sigs[i].pubKeys == pubKeys)
      {
        if (tx.sigs[i].sigData.length + 1 > pubKeys.length)
        {
          throw new SDKException(ErrorCode::ParamErr("too more sigData"));
        }
        sigData.push_back(tx.sign(acct, acct.getSignatureScheme(),acct.getCurveName()));
        tx.sigs[i].sigData = sigData;
        return tx;
      }
    }
    Sig[] sigs = new Sig[tx.sigs_length() + 1];
    for (int i = 0; i < tx.sigs_length(); i++)
    {
      sigs[i] = tx.sigs[i];
    }
    sigs[tx.sigs.length] = new Sig();
    sigs[tx.sigs.length].M = M;
    sigs[tx.sigs.length].pubKeys = pubKeys;
    sigs[tx.sigs.length].sigData = new byte[1][];
    sigs[tx.sigs.length].sigData[0] = tx.sign(acct, acct.getSignatureScheme());

    tx.sigs = sigs;
    return tx;
  }
};
#endif // !ONTSDK_H