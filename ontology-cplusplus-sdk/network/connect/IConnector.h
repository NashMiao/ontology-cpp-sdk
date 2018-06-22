#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "boost/any.hpp"
#include <string>

class IConnector
{
public:
  virtual std::string getUrl() = 0;
  virtual boost::any getBalance(std::string address) = 0;
  virtual boost::any sendRawTransaction(bool preExec, const std::string &userid,
                                        const std::string &sData) = 0;
};

#endif