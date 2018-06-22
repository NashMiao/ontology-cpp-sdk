#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include "../connect/IConnector.h"
#include "RpcInterfaces.h"
#include "boost/any.hpp"
#include <iostream>
#include <map>
#include <vector>

class RpcClient : public IConnector {
private:
  RpcInterfaces rpc;

public:
  RpcClient(std::string url) {
    try {
      rpc = new RpcInterfaces(url);
    } catch (const char *err) {
      std::cerr << err << std::endl;
    }
  }

  std::string getUrl() { return rpc.getHost(); }

  boost::any getBalance(std::string address) {
    boost::any result;
    result = rpc.call("getbalance", address);
  }

  boost::any sendRawTransaction(bool preExec, std::string userid,
                                std::string sData) {
    boost::any result;
    std::vector<boost::any> any_vec;
    any_vec.push_back(sData);
    if (preExec) {
      any_vec.push_back(1);
      result = rpc.call("sendrawtransaction", any_vec);
    } else {
      result = rpc.call("sendrawtransaction", any_vec);
    }
    return result;
  }
};

#endif