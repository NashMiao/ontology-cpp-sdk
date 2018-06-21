#ifndef RPCCLIENT_H
#define RPCCLIENT_H

#include "boost/any.hpp"
#include <map>
#include <vector>

class RpcClient
{
  public:
    std::map makeRequest(std::string method, std::vector<boost::any> params)
    {
        std::map<std::string, boost::any> request = {{"jsonrpc", "2.0"},
                                                     {"method", method},
                                                     {"params", params},
                                                     {"id", 1}};
        return request;
    }
};

#endif