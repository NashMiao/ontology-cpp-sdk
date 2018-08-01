#ifndef CONTROL_H
#define CONTROL_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <iostream>
#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "../../common/Helper.h"

class Control
{
  private:
    std::string algorithm;
    nlohmann::json parameters;
    std::string id;
    std::string key;
    std::string salt;
    std::string hash;
    std::string encAlg;
    std::string address;
    std::string publicKey;

  public:
    Control() : algorithm("ECDSA"), hash("sha256"), encAlg("aes-256-gcm")
    {
        parameters["curve"] = "secp256r1";
    }

    void setEncAlg(std::string enc_alg) { encAlg = enc_alg; }
    std::string getEncAlg() { return encAlg; }

    void setSalt(std::vector<unsigned char> vec_salt)
    {
        salt = Helper::base64Encode(vec_salt, false);
    }
    std::vector<unsigned char> getSalt()
    {
        std::string raw_salt = Helper::base64Decode(salt, false);
        return std::vector<unsigned char>(raw_salt.begin(), raw_salt.end());;
    }

    void setAddress(const std::string &addr) { address = addr; }
    std::string getAddress() { return address; }

    void setPublicKey(const std::string &pk) { publicKey = pk; }
    std::string getPublicKey() { return publicKey; }

    std::string toString()
    {
        nlohmann::json j;
        j["algorithm"] = algorithm;
        j["parameters"] = parameters;
        j["id"] = id;
        j["key"] = key;
        j["salt"] = salt;
        j["hash"] = hash;
        j["enc-alg"] = encAlg;
        j["address"] = address;
        j["publicKey"] = publicKey;
        return j.dump();
    }
};
#endif // !CONTROL_H