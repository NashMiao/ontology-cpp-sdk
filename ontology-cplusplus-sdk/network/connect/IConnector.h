#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "boost/any.hpp"
#include <string>

class IConnector
{
public:
  virtual std::string getUrl();
  virtual boost::any getBalance(std::string address);
  virtual boost::any sendRawTransaction(bool preExec, std::string userid,
                                        std::string hexData);
  virtual std::string sendRawTransaction(const std::string &sData);
};

#endif