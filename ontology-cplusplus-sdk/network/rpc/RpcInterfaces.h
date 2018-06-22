#ifndef RPCINTERFACES_H
#define RPCINTERFACES_H

#include "boost/any.hpp"
#include <curl/curl.h>
#include <map>
#include <string>
#include <vector>

class RpcInterfaces
{
private:
  std::string url;

  std::string makeRequest(const std::string &method, nlohmann::json params)
  {
    nlohmann::json request = {
        {"jsonrpc", "2.0"}, {"method", method}, {"params", params}, {"id", 1}};
    std::string request_str = request.dump();
    std::cout << "POST url=" + url + "," + request_str << std::endl;
    return request_str;
  }

  std::string makeRequest(const std::string &method)
  {
    nlohmann::json request = {
        {"jsonrpc", "2.0"}, {"method", method}, {"params", ""}, {"id", 1}};
    std::string request_str = request.dump();
    std::cout << "POST url=" + url + "," + request_str << std::endl;
    return request_str;
  }

  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                              void *userp)
  {
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
  }

  std::string cvtParams(std::unordered_map<std::string, std::string> params)
  {
    if (params.empty())
    {
      return "";
    }
    std::string str = "?";
    CURL *curl = curl_easy_init();
    if (curl)
    {
      std::unordered_map<std::string, std::string>::const_iterator params_it;
      for (params_it = params.cbegin(); params_it != params.cend();
           params_it++)
      {
        std::string key = params_it->first;
        std::string value = params_it->second;
        if (!value.empty())
        {
          value = std::string(
              curl_easy_escape(curl, value.c_str(), value.length()));
        }
        str.append("&").append(key).append("=").append(value);
      }
      curl_easy_cleanup(curl);
    }
    return str;
  }

  CURLcode curl_get_body(const std::string &url, std::string &response_body,
                         bool is_https)
  {
    CURL *curl = curl_easy_init();
    std::string response_write;
    std::string response_head;
    response_body.clear();
    CURLcode res;
    if (curl)
    {
      // set params
      curl_slist *plist = curl_slist_append(
          NULL, "Content-Type:application/json;charset=UTF-8");
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);
      if (is_https)
      {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
      }

      else
      {
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
      if (res != CURLE_OK)
      {
        std::string err_str = "curl_easy_perform() failed: ";
        err_str.append(curl_easy_strerror(res));
        throw err_str;
      }
    }
    else
    {
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
                                 const std::string &post_body, bool is_https)
  {
    // init curl
    CURL *curl = curl_easy_init();
    std::string response_write;
    std::string response_head;
    // res code
    CURLcode res;
    if (curl)
    {
      // set params
      curl_slist *plist = curl_slist_append(
          NULL, "Content-Type:application/json;charset=UTF-8");
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, plist);
      if (is_https)
      {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, true);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, true);
      }

      else
      {
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
      if (res != CURLE_OK)
      {
        std::string err_str = "curl_easy_perform() failed: ";
        err_str.append(curl_easy_strerror(res));
        throw err_str;
      }
    }
    else
    {
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
  ToJSONString(std::unordered_map<std::string, std::string> uord_map)
  {
    std::unordered_map<std::string, std::string>::const_iterator uord_map_it;
    nlohmann::json json_uord_map;
    for (uord_map_it = uord_map.cbegin(); uord_map_it != uord_map.cend();
         uord_map_it++)
    {
      json_uord_map[uord_map_it->first] = uord_map_it->second;
    }
    std::string str_uord_map = json_uord_map.dump();
    return str_uord_map;
  }

  std::string post(std::string url,
                   std::unordered_map<std::string, std::string> params,
                   std::unordered_map<std::string, std::string> body)
  {
    std::string response_body;
    try
    {
      if (url.substr(0, 5) == "https")
      {
        response_body = curl_post_set_body(url, cvtParams(params),
                                           ToJSONString(body), true);
      }
      else
      {
        response_body = curl_post_set_body(url, cvtParams(params),
                                           ToJSONString(body), false);
      }
    }
    catch (const char *e)
    {
      std::cerr << e << std::endl;
    }
    return response_body;
  }

public:
  RpcInterfaces() { curl_global_init(CURL_GLOBAL_ALL); }

  RpcInterfaces(std::string _url) : url(_url)
  {
    curl_global_init(CURL_GLOBAL_ALL);
  }

  ~RpcInterfaces() { curl_global_cleanup(); }

  void setUrl(const std::string &_url) { url = _url; }

  std::string getHost() { return url; }

  nlohmann::json send(std::string request, bool is_https = false)
  {
    std::string response_body;
    response_body = curl_post_set_body(url, request, "", is_https);
    nlohmann::json ret_json = response_body, _json;
    return ret_json;
  }

  boost::any call(const std::string &method, nlohmann::json &json_array)
  {
    std::string request;
    request = makeRequest(method, json_array);
    nlohmann::json json_response;
    json_response = send(request);
    if (json_response.size() == 0)
    {
      throw "RpcException(0,ErrorCode.ConnectUrlErr(  " + url +
          "response is null. maybe is connect error)";
    }
    if (json_response.find("error") == json_response.end())
    {
      throw "json_response.find(\"error\")== json_response.end()";
    }
    if (json_response.find("error").value() != 0)
    {
      throw "RpcException(0, JSON.toJSONString(response))";
    }
    if (json_response.find("result") == json_response.end())
    {
      throw "json_response.find(\"result\")== json_response.end()";
    }
    boost::any ret_value;
    ret_value = json_response.find("result").value();
    return ret_value;
  }

  boost::any call(const std::string &method, const std::string &params)
  {
    nlohmann::json json_array;
    json_array.push_back(params);
    return call(method, json_array);
  }

  // boost::any call(const std::string &method)
  // {
  //   makeRequest()
  // }
};

#endif