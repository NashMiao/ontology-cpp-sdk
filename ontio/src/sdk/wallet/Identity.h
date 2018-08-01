#ifndef IDENTIFY_H
#define IDENTIFY_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>
#include <list>

#include <nlohmann/json.hpp>

#include "Control.h"

class Identity
{
private:
  std::string label;
  std::string ontid;
  bool isDefault;
  bool lock;
  std::list<Control> controls;
  nlohmann::json extra;

public:
  Identity()
  {
    label = "";
    ontid = "";
    isDefault = false;
    lock = false;
  }

  void setExtra(nlohmann::json &ex)
  {
    extra = ex;
  }

  nlohmann::json getExtra()
  {
    return extra;
  }
};
#endif // !IDENTIFY_H