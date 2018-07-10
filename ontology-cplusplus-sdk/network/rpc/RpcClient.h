#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include "../../network/connect/IConnector.h"
#include "RpcInterfaces.h"
#include "boost/any.hpp"
#include <iostream>
#include <map>
#include <vector>

class RpcClient : public IConnector {
private:
  RpcInterfaces rpc;
  std::string version = "v1.0.0";
  std::string action = "sendRawTransaction";

public:
  RpcClient() {}
  RpcClient(std::string url) {
    try {
      rpc.setUrl(url);
    } catch (const char *err) {
      std::cerr << err << std::endl;
    }
  }

  void setUrl(const std::string _url) { rpc.setUrl(_url); }

  std::string getUrl() override { return rpc.getHost(); }

  nlohmann::json getBalance(std::string address) override {
    nlohmann::json result;
    result = rpc.call("getbalance", address);
    return result;
  }

  nlohmann::json sendRawTransaction(bool preExec, const std::string &userid,
                                    const std::string &sData) override {
    std::string cut_sData;
    if (sData[0] == '0' && sData[1] == 'x') {
      cut_sData.assign(sData, 2, sData.size() - 2);
    }
    nlohmann::json result;
    std::vector<boost::any> any_vec;
    nlohmann::json json_array = nlohmann::json::array();
    json_array.push_back(cut_sData);
    if (preExec) {
      json_array.push_back(1);
      try {
        result = rpc.call("sendrawtransaction", json_array);
      } catch (const char *e) {
        cerr << std::string("sendRawTransaction exepection: ") + std::string(e)
             << endl;
      }
    } else {
      try {
        result = rpc.call("sendrawtransaction", json_array);
      } catch (const char *e) {
        cerr << e << endl;
      }
    }
    return result;
  }

  std::string sendRawTransaction(const std::string &sData) override {
    nlohmann::json val;
    val = rpc.call("sendrawtransaction", sData);
    if (!val.is_string()) {
      throw "sendRawTransaction: return type error!";
    }
    std::string value;
    value = val;
    return value;
  }

  int getGenerateBlockTime() override {
    nlohmann::json val;
    val = rpc.call("getgenerateblocktime");
    if (!val.is_number()) {
      throw "getGenerateBlockTime: Type Error!";
    }
    int block_time;
    block_time = val;
    return block_time;
  }

  int getNodeCount() override {
    nlohmann::json val;
    val = rpc.call("getconnectioncount");
    if (!val.is_number()) {
      throw "getNodeCount: Type Error!";
    }
    int node_count;
    node_count = val;
    return node_count;
  }

  int getBlockHeight() override {
    nlohmann::json val;
    val = rpc.call("getblockcount");
    if (!val.is_number()) {
      throw "getNodeCount: Type Error!";
    }
    int block_height;
    block_height = val;
    return block_height;
  }

  nlohmann::json getBlockJson(int index) override {
    nlohmann::json json_array = nlohmann::json::array();
    json_array.push_back(index);
    json_array.push_back(1);
    nlohmann::json result;
    result = rpc.call("getblock", json_array);
    return result;
  }

  nlohmann::json getBlockJson(const std::string &hash) override {
    nlohmann::json json_array = nlohmann::json::array();
    json_array.push_back(hash);
    json_array.push_back(1);
    nlohmann::json result;
    result = rpc.call("getblock", json_array);
    return result;
  }

  nlohmann::json getContractJson(const std::string &hash) override {
    nlohmann::json json_array = nlohmann::json::array();
    json_array.push_back(hash);
    json_array.push_back(1);
    nlohmann::json result;
    result = rpc.call("getcontractstate", json_array);
    return result;
  }

  int getBlockHeightByTxHash(const std::string &hash) {
    nlohmann::json result;
    result = rpc.call("getblockheightbytxhash", hash);
    int height;
    if (result.is_number()) {
      height = result;
    } else {
      throw "new RuntimeException(e)";
    }
    return height;
  }

  std::string getStorage(const std::string &codehash, const std::string &key) {
    nlohmann::json result;
    nlohmann::json json_array = nlohmann::json::array();
    json_array.push_back(codehash);
    json_array.push_back(key);
    result = rpc.call("getstorage", json_array);
    string storage;
    if (result.is_string()) {
      storage = result;
    } else {
      throw "new RuntimeException(e)";
    }
    return storage;
  }

  std::string getAllowance(const std::string &asset, const std::string &from,
                           const std::string &to) {
    nlohmann::json result;
    nlohmann::json json_array = nlohmann::json::array();
    json_array.push_back(asset);
    json_array.push_back(from);
    json_array.push_back(to);
    result = rpc.call("getallowance", json_array);
    std::string allowance;
    if (result.is_string()) {
      allowance = result;
    } else {
      throw "new RuntimeException(e)";
    }
    return allowance;
  }

  std::string getVersion() {
    nlohmann::json result;
    result = rpc.call("getversion");
    std::string version;
    if (result.is_string()) {
      version = result;
    } else {
      throw "new RuntimeException(e)";
    }
    return version;
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