#ifndef STATE_H
#define STATE_H

#include "../../common/Address.h"
#include "../../io/Serializable.h"
#include <nlohmann/json.hpp>

class State : public Serializable {
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

  void deserialize(BinaryReader &reader) {
    try {
      reader.readSerializable(from);
      reader.readSerializable(to);
      value = reader.readVarInt();
    } catch (const char *e) {
      cerr << e << endl;
    }
  }

  void serialize(BinaryWriter &writer) {
    writer.writeSerializable(from);
    writer.writeSerializable(to);
    writer.writeVarInt(value);
  }

  nlohmann::json json() {
    nlohmann::json state_json;
    state_json["from"] = from.toHexString();
    state_json["to"] = to.toHexString();
    state_json["value"] = value;
    return state_json;
  }
};

#endif