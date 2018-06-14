#ifndef CONTROL_H
#define CONTROL_H
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