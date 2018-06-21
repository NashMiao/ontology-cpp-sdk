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
};

#endif