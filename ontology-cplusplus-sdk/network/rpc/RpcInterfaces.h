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
  RpcInterfaces(std::string _url) url(_url) {
    curl_global_init(CURL_GLOBAL_ALL);
  }

  ~RpcInterfaces() { curl_global_cleanup(); }

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
    } else {
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
      curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    }
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    std::string str_params;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str_params);
  }

  boost::any call(const std::string &method, std::vector<boost::any> params) {
    std::map<std::string, boost::any> request;
    request = makeRequest(method, params);
    boost::any any_response = send(request);
    std::map<std::string, boost::any> map_response;
    map_response =
        boost::any_cast<std::map<std::string, boost::any>>(any_response);
    if (map_response.size() == 0) {
      throw "RpcException(0,ErrorCode.ConnectUrlErr(  " + url +
          "response is null. maybe is connect error)";
    }
    std::map<std::string, boost::any>::iterator map_it;
    map_it = map_response.find("error");
    boost::any ret_value;
    if (map_it != map_response.end() && map_it->second == 0) {
      map_it = map_response.find("result");
      if (map_it == response.end()) {
        throw "RPC call: can't find result";
      }
      ret_value = map_it->second;
    } else {
      throw "RpcException(0, JSON.toJSONString(response))";
    }
    return ret_value;
  }
};

#endif