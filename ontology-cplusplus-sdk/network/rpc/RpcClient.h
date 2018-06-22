#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include "../../network/connect/IConnector.h"
#include "RpcInterfaces.h"
#include "boost/any.hpp"
#include <iostream>
#include <map>
#include <vector>

class RpcClient : public IConnector
{
private:
  RpcInterfaces rpc;

public:
  RpcClient() {}
  RpcClient(std::string url)
  {
    try
    {
      rpc.setUrl(url);
    }
    catch (const char *err)
    {
      std::cerr << err << std::endl;
    }
  }

  void setUrl(const std::string _url) { rpc.setUrl(_url); }

  std::string getUrl() override { return rpc.getHost(); }

  boost::any getBalance(std::string address) override
  {
    boost::any result;
    result = rpc.call("getbalance", address);
    return result;
  }

  boost::any sendRawTransaction(bool preExec, const std::string &userid,
                                const std::string &sData) override
  {
    std::string cut_sData;
    cut_sData.assign(sData, 2, sData.size() - 2);
    cout << "sData:\n"
         << sData << endl;
    cout << "cut_sData:\n"
         << cut_sData << endl;
    boost::any result;
    std::vector<boost::any> any_vec;
    nlohmann::json json_array;
    json_array.push_back(cut_sData);
    if (preExec)
    {
      json_array.push_back(1);
      result = rpc.call("sendrawtransaction", json_array);
    }
    else
    {
      result = rpc.call("sendrawtransaction", json_array);
    }
    return result;
  }

  std::string sendRawTransaction(const std::string &sData)
  {
    boost::any val;
    std::string value;
    // val = rpc.call("sendrawtransaction", sData);
    if (val.type() == typeid(std::string))
    {
      value = boost::any_cast<std::string>(val);
    }
    else
    {
      throw "sendRawTransaction: return type error!";
    }
    return value;
  }

  int getGenerateBlockTime()
  {
    boost::any val;
    // val = rpc.call("getgenerateblocktime");
    if (val.type() != typeid(int))
    {
      throw "getGenerateBlockTime: Type Error!";
    }
    int block_time;
    block_time = boost::any_cast<int>(val);
    return block_time;
  }

  int getNodeCount()
  {
    boost::any val;
    // val = rpc.call("getconnectioncount");
    if (val.type() != typeid(int))
    {
      throw "getNodeCount: Type Error!";
    }
    int node_count;
    node_count = boost::any_cast<int>(val);
    return node_count;
  }

  // Transaction getRawTransaction(std::string txhash) {
  //   boost::any val;
  //   std::string value;
  //   val = rpc.call("getrawtransaction", txhash);
  //   if (val.type() == typeid(std::string)) {
  //     value = boost::any_cast<std::string>(val);
  //   } else {
  //     throw "getRawTransaction: return type error!";
  //   }
  //   Transaction *ret_transaction;
  //   ret_transaction->deserializeFrom(Helper::hexToBytes(value));
  //   return ret_transaction;
  // }
};

#endif