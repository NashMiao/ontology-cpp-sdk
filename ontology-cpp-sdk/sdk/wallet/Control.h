#ifndef CONTROL_H
#define CONTROL_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>
#include <iostream>
#include <unordered_map>

class Control
{
  public:
    std::string algorithm;
    std::unordered_map<int, int> parameters;
    std::string id;
    std::string key;
    Control()
    {
        algorithm = "ECDSA";
        id = "";
        key = "";
    }
};
#endif // !CONTROL_H