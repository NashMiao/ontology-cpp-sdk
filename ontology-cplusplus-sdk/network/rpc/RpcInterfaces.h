#ifndef RPCINTERFACES_H
#define RPCINTERFACES_H

#include "boost/any.hpp"
#include <curl/curl.h>
#include <map>
#include <string>
#include <vector>

class RpcInterfaces {
private:
  std::string url;
  
  std::map<std::string, boost::any>
  makeRequest(const std::string &method, std::vector<boost::any> params) {
    std::map<std::string, boost::any> request = {
        {"jsonrpc", "2.0"}, {"method", method}, {"params", params}, {"id", 1}};
    std::string request_str = "POST url=" + url + ",";
    std::cout << request_str << std::endl;
    return request;
  }

public:
  RpcInterfaces(std::string _url) url(_url) {}

  std::string getHost() { return url; }

  boost::any send(boost::any request, is_https = false) {
    CURL *curl = curl_easy_init();
    if (!curl) {
      throw "RpcInterfaces send: curl_easy_init error!";
    }
    curl_slist *plist =
        curl_slist_append(NULL, "Content-Type:application/json;charset=UTF-8");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);
    if (is_https) {
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
    }

    else {
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
  }

  boost::any call(const std::string &method, boost::any params) {
    std::map<std::string, boost::any> request;
    request = makeRequest(method, params);
  }
};

#endif