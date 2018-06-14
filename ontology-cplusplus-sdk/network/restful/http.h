#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <curl/curl.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

using namespace std;

class Http {
private:
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                              void *userp) {
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
  }

  std::string cvtParams(std::unordered_map<std::string, std::string> params) {
    if (params.empty()) {
      return "";
    }
    std::string str = "?";
    CURL *curl = curl_easy_init();
    if (curl) {
      std::unordered_map<std::string, std::string>::const_iterator params_it;
      for (params_it = params.cbegin(); params_it != params.cend();
           params_it++) {
        std::string key = params_it->first;
        std::string value = params_it->second;
        if (!value.empty()) {
          value = std::string(
              curl_easy_escape(curl, value.c_str(), value.length()));
        }
        str.append("&").append(key).append("=").append(value);
      }
      curl_easy_cleanup(curl);
    }
    return str;
  }

public:
  Http() { curl_global_init(CURL_GLOBAL_ALL); }
  ~Http() { curl_global_cleanup(); }
  // http GET
  CURLcode curl_get_body(const std::string &url, std::string &response_body,
                         bool is_https) {
    CURL *curl = curl_easy_init();
    std::string response_write;
    std::string response_head;
    response_body.clear();
    CURLcode res;
    if (curl) {
      // set params
      curl_slist *plist = curl_slist_append(
          NULL, "Content-Type:application/json;charset=UTF-8");
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
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response_write);
      curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&response_head);
      curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
      curl_easy_setopt(curl, CURLOPT_HEADER, 1);
      curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10000);
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10000);
      res = curl_easy_perform(curl);
      if (res != CURLE_OK) {
        std::string err_str = "curl_easy_perform() failed: ";
        err_str.append(curl_easy_strerror(res));
        throw err_str;
      }
    } else {
      throw "curl_easy_init() failed.";
    }
    response_body =
        response_write.substr(response_head.size(), response_write.size());
    // release curl
    curl_easy_cleanup(curl);
    return res;
  }

  // http POST
  std::string curl_post_set_body(const std::string &url,
                                 const std::string &postParams,
                                 const std::string &post_body, bool is_https) {
    // init curl
    CURL *curl = curl_easy_init();
    std::string response_write;
    std::string response_head;
    // res code
    CURLcode res;
    if (curl) {
      // set params
      curl_slist *plist = curl_slist_append(
          NULL, "Content-Type:application/json;charset=UTF-8");
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);
      if (is_https) {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
      }

      else {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
      }
      curl_easy_setopt(curl, CURLOPT_POST, 1);
      curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str());
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
      curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&response_write);
      curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteCallback);
      curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&response_head);
      curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
      curl_easy_setopt(curl, CURLOPT_HEADER, 1);
      curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10000);
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10000);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_body.c_str());
      res = curl_easy_perform(curl);
      if (res != CURLE_OK) {
        std::string err_str = "curl_easy_perform() failed: ";
        err_str.append(curl_easy_strerror(res));
        throw err_str;
      }
    } else {
      throw "curl_easy_init() failed.";
    }
    std::string response_body;
    response_body =
        response_write.substr(response_head.size(), response_write.size());
    // release curl
    curl_easy_cleanup(curl);
    return response_body;
  }

  std::string
  ToJSONString(std::unordered_map<std::string, std::string> uord_map) {
    std::unordered_map<std::string, std::string>::const_iterator uord_map_it;
    nlohmann::json json_uord_map;
    for (uord_map_it = uord_map.cbegin(); uord_map_it != uord_map.cend();
         uord_map_it++) {
      json_uord_map[uord_map_it->first] = uord_map_it->second;
    }
    std::string str_uord_map = json_uord_map.dump();
    return str_uord_map;
  }

  std::string post(std::string url,
                   std::unordered_map<std::string, std::string> params,
                   std::unordered_map<std::string, std::string> body) {
    std::string response_body;
    try {
      if (url.substr(0, 5) == "https") {
        response_body = curl_post_set_body(url, cvtParams(params),
                                           ToJSONString(body), true);
      } else {
        response_body = curl_post_set_body(url, cvtParams(params),
                                           ToJSONString(body), false);
      }
    } catch (const char *e) {
      std::cerr << e << std::endl;
    }
    return response_body;
  }
};
#endif