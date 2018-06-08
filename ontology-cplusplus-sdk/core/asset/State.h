#ifndef STATE_H
#define STATE_H

#include "../../common/Address.h"
#include <nlohmann/json.hpp>

class State {
private:
  Address from;
  Address to;
  long long value;

public:
  State() {}
  State(Address _from, Address _to, long long amount) {
    from = _from;
    to = _to;
    value = amount;
  }

  nlohmann::json json(){
      nlohmann::json state_json;
      state_json["from"] = from.toHexString();
      state_json["to"] = to.toHexString();
      state_json["value"] = value;
      return state_json;
  }
};

#endif