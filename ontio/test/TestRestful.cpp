#include <iostream>
#include <string>
#include <vector>

#include "../network/restful/Result.h"
#include "../network/restful/http.h"

void test_Result_ssrst() {
  Result test_result;
  test_result.result.Action = std::string("action");
  test_result.result.Error = 123456789;
  test_result.result.Desc = std::string("desc");
  test_result.result.Version = std::string("version");
  test_result.result.Result = std::string("result");
  std::cout << "test_result.toString():\n" << test_result.toString() << std::endl;
}

void test_Result_jsrst() {
  Result test_result;
  test_result.result.Action = std::string("action");
  test_result.result.Error = 123456789;
  test_result.result.Desc = std::string("desc");
  test_result.result.Version = std::string("version");
  nlohmann::json rst;
  rst["GasPrice"] = 1;
  rst["GasLimit"] = 2;
  test_result.result.Result = std::string(rst.dump());
  std::cout << "test_result.toString():\n" << test_result.toString() << std::endl;
}

void test_http_get() {
  Http http;
  std::string url = "http://jsonplaceholder.typicode.com/posts/1";
  std::string response_body = "";
  CURLcode res;
  res = http.curl_get_body(url, response_body, false);
  std::cout << "res:\n" << res << std::endl;
  std::cout << "response_body:\n" << response_body << std::endl;
  std::cout << "-------------------------------------------" << std::endl;
  url =
      "http://polaris1.ont.io:20334/api/v1/transaction/"
      "20046da68ef6a91f6959caa798a5ac7660cc80cf4098921bc63604d93208a8ac?raw="
      "1";
  res = http.curl_get_body(url, response_body, false);
  std::cout << "res:\n" << res << std::endl;
  std::cout << "response_body:\n" << response_body << std::endl;
}

void test_http_post() {
  Http http;
  std::string url = "http://jsonplaceholder.typicode.com/posts";

  nlohmann::json json_postParams;
  json_postParams["title"] = "foo";
  json_postParams["body"] = "bar";
  json_postParams["userId:"] = 1;
  std::string str_postParams = json_postParams.dump();
  std::string response_body;
  response_body = http.curl_post_set_body(url, str_postParams, "", false);
  std::cout << "response_body:\n" << response_body << std::endl;
}