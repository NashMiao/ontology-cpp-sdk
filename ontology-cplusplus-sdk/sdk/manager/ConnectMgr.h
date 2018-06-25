#ifndef CONNECTMGR_H
#define CONNECTMGR_H

#include "../../network/connect/IConnector.h"
#include "../../network/rpc/RpcClient.h"
#include "ConnectType.h"
#include "boost/any.hpp"

#include <typeinfo>

class ConnectMgr {
private:
  IConnector *connector;
  RpcClient rpc_client;

public:
  ConnectMgr() {}

  ConnectMgr(const std::string &_url, ConnectType type) {
    if (type == ConnectType::RPC) {
      rpc_client.setUrl(_url);
      connector = &rpc_client;
    } else if (type == ConnectType::RESTful) {
      // TODO
      throw "ConnectMgr: ConnectType::RESTful";
    } else {
      throw "ConnectMgr: Unsupport ConnectType";
    }
  }

  ConnectMgr(RpcClient rpc_client) { connector = &rpc_client; }

  boost::any sendRawTransactionPreExec(const std::string &hexData) {
    boost::any any_ret;
    any_ret = connector->sendRawTransaction(true, "", hexData);
    return any_ret;
    // try
    // {
    //   RpcClient rpc;
    //   rpc = dynamic_cast<RpcClient &>(connector);
    //   any_ret = rpc.sendRawTransaction(true, "", hexData);
    //   return any_ret;
    // }
    // catch (std::bad_cast const &ex)
    // {
    //   std::cout << "[" << ex.what() << "]" << std::endl;
    //   throw "connector instanceof Unsupport type";
    // }
  }

  int getNodeCount()
  {
    int count;
    count = connector->getNodeCount();
    return count;
  }

  int getBlockHeight(){
    int height;
    height = connector->getBlockHeight();
    return height;
  }
};

#endif