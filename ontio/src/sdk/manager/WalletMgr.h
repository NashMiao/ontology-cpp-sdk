#ifndef SDK_MANAGER_WALLETMGR_H
#define SDK_MANAGER_WALLETMGR_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

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