#ifndef RPCINTERFACES_H
#define RPCINTERFACES_H

#include "boost/any.hpp"
#include <map>
#include <string>
#include <vector>

class RpcInterfaces
{
  private:
    std::string url;

  public:
    RpcInterfaces(std::string _url) url(_url) {}
    std::map makeRequest(std::string method, std::vector<boost::any> params)
    {
        std::map<std::string, boost::any> request = {
            {"jsonrpc", "2.0"}, {"method", method}, {"params", params}, {"id", 1}};
        std::string request_str = "POST url=" + url + ",";
        std::cout << request_str << std::endl;
        return request;
    }

};

#endif