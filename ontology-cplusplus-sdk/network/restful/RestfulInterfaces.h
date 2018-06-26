#ifndef INTERFACES_H
#define INTERFACES_H

#include "UrlConsts.h"
#include "http.h"
#include <string>
#include <unordered_map>

class Interfaces {
private:
  std::string url;

public:
  Interfaces(std::string _url) { url = _url; }
  std::string getUrl() { return url; }
  std::string sendTransaction(bool preExec, std::string userid,
                              std::string action, std::string version,
                              std::string data) {
    std::unordered_map<std::string, std::string> params;
    if (userid != NULL) {
      params.insert({std::string("userid"), userid});
    }
    if (preExec) {
      params.insert({std::string("preExec"), std::string("1")});
    }
    std::unordered_map<std::string, std::string> body;
    body.insert({"Action", action});
    body.insert({"Version", version});
    body.insert({"Data", data});
    try {
      Http http;
      UrlConsts urlconsts;
      http.post(url + urlconsts.Url_send_transaction, params, body);
      
    }
  }
};

#endif