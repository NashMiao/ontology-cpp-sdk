#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "boost/any.hpp"
#include "nlohmann/json.hpp"
#include <string>

class IConnector
{
public:
  virtual std::string getUrl() = 0;
  virtual nlohmann::json getBalance(std::string address) = 0;
  virtual nlohmann::json sendRawTransaction(bool preExec, const std::string &userid,
                                        const std::string &sData) = 0;
  virtual std::string sendRawTransaction(const std::string &sData) = 0;
  virtual int getGenerateBlockTime() = 0;
  virtual int getNodeCount() = 0;
  virtual int getBlockHeight() = 0;
  virtual nlohmann::json getBlockJson(int index) = 0;
  virtual nlohmann::json getBlockJson(const std::string &hash) = 0;
  virtual nlohmann::json getContractJson(const std::string &hash) = 0;
};

#endif