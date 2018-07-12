#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>

#include "boost/any.hpp"
#include "nlohmann/json.hpp"

class IConnector
{
public:
  virtual std::string getUrl() = 0;
  virtual nlohmann::json getBalance(std::string address) = 0;
  virtual nlohmann::json sendRawTransaction(bool preExec,
                                            const std::string &userid,
                                            const std::string &sData) = 0;
  virtual nlohmann::json sendRawTransaction(const std::string &sData) = 0;
  virtual int getGenerateBlockTime() = 0;
  virtual int getNodeCount() = 0;
  virtual int getBlockHeight() = 0;
  virtual nlohmann::json getBlockJson(int index) = 0;
  virtual nlohmann::json getBlockJson(const std::string &hash) = 0;
  virtual nlohmann::json getContractJson(const std::string &hash) = 0;
  virtual int getBlockHeightByTxHash(const std::string &hash) = 0;
  virtual std::string getStorage(const std::string &codehash,
                                 const std::string &key) = 0;
  virtual std::string getAllowance(const std::string &asset,
                                   const std::string &from,
                                   const std::string &to) = 0;
  virtual std::string getVersion() = 0;
};

#endif