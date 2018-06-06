#ifndef HTTP_H
#define HTTP_H

#include <curl/curl.h>
#include <string>
using namespace std;

class Http {
private:
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                              void *userp) {
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
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
  CURLcode curl_post_body(const string &url, const string &postParams,
                          string &response_body, bool is_https) {
    // init curl
    CURL *curl = curl_easy_init();
    std::string response_write;
    std::string response_head;
    response_body.clear();
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
};
#endif