#ifndef WALLETMGR_H
#define WALLETMGR_H

#include <unordered_map>
#include "../wallet/Wallet.h"

class WalletMgr
{
private:
  Wallet wallet;
  std::unordered_map<int, int> acctPriKeyMap;
  std::unordered_map<int, int> identityPriKeyMap;
  Wallet walletFile;
  // SignatureScheme scheme;
  std::string filePath;

public:
  WalletMgr()
  {
    // acctPriKeyMap = new HashMap();
    // identityPriKeyMap = new HashMap();
    filePath = "";
  }
};
#endif // !WALLETMGR_H