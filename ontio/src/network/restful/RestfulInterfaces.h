#ifndef INTERFACES_H
#define INTERFACES_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>
#include <unordered_map>

#include "UrlConsts.h"
#include "http.h"

class Interfaces : public UrlConsts, public Http
{
private:
  std::string url;

public:
  Interfaces(std::string _url) { url = _url; }
  std::string getUrl() { return url; }

  // std::string sendTransaction(bool preExec, std::string userid,
  //                             std::string action, std::string version,
  //                             std::string data)
  // {
  //   std::unordered_map<std::string, std::string> params;
  //   if (userid != NULL)
  //   {
  //     params.insert({std::string("userid"), userid});
  //   }
  //   if (preExec)
  //   {
  //     params.insert({std::string("preExec"), std::string("1")});
  //   }
  //   std::unordered_map<std::string, std::string> body;
  //   body.insert({"Action", action});
  //   body.insert({"Version", version});
  //   body.insert({"Data", data});
  //   try
  //   {
  //     Http http;
  //     UrlConsts::Url UrlConsts urlconsts;
  //     http.post(url + urlconsts.Url_send_transaction, params, body);
  //   }
  // }

  std::string sendTransaction(bool preExec, std::string userid,
                              std::string action, std::string version,
                              std::string data)
  {
    nlohmann::json params = nlohmann::json::array();
    if (!userid.empty())
    {
      params.push_back({"userid", userid});
    }
    if (preExec)
    {
      params.push_back({"preEcec", 1});
    }
    nlohmann::json body = nlohmann::json::array();
    body = {{"Action", action}, {"Version", version}, {"Data", data}};
    std::string response_body;
    try
    {
      response_body = Http::curl_post_set_body(url + UrlConsts::Url_send_transaction,
                                         params, body, is_https);
    }
    catch (const char *err)
    {
      cerr << err << endl;
    }
    return response_body;
  }

  std::string getTransaction(std::string txhash, bool raw)
  {
    nlohmann::json params = nlohmann::json::array();
    if (raw)
    {
      params.push_back({"raw", 1});
    }
    try
    {
      std::string response_body = "";
      CURLcode res;
      res = Http::curl_get_body(url +, response_body, false);
      cout << "res:\n"
           << res << endl;
      cout << "response_body:\n"
           << response_body << endl;
      return Http::get(url + UrlConsts::Url_get_transaction + txhash, params);
    }
    catch (const char *err)
    {
      cerr << err << endl;
      throw "RestfulException(ErrorCode.ConnectUrlErr + url, e)";
    }
  }
};

#endif