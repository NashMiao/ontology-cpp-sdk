#ifndef CONNECTMGR_H
#define CONNECTMGR_H

#include "../../network/connect/IConnector.h"
#include "../../network/rpc/RpcClient.h"
#include "ConnectType.h"
#include "boost/any.hpp"

#include <typeinfo>

class ConnectMgr {
private:
  IConnector connector;

public:
  ConnectMgr() {}

  ConnectMgr(std::string url, ConnectType type) {
    if (type == ConnectType::RPC) {
      setConnector(RpcClient(url));
    } else if (type == ConnectType::RESTful) {
      // TODO
      throw "ConnectMgr: ConnectType::RESTful";
    } else {
      throw "ConnectMgr: Unsupport ConnectType";
    }
  }

  ConnectMgr(IConnector connector) { setConnector(connector); }

  void setConnector(const IConnector &_connector) { connector = _connector; }

  boost::any sendRawTransactionPreExec(std::string hexData) {
    boost::any any_ret;
    any_ret = connector.sendRawTransaction(true, "", hexData);
    try {
      RpcClient rpc;
      rpc = dynamic_cast<RpcClient &>(connector);
      return any_ret;
    }
    catch (std::bad_cast const &ex)
    {
      std::cout << "[" << ex.what() << "]" << std::endl;
      throw "connector instanceof Unsupport type";
    }
  }
};

#endif