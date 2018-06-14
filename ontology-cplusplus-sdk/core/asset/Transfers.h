#ifndef TRANSFERS_H
#define TRANSFERS_H

#include "../../common/Address.h"
#include "../../io/Serializable.h"
#include "State.h"
#include <vector>

class Transfers : public Serializable {
private:
  std::vector<State> states;

public:
  Transfers() {}
  Transfers(const std::vector<State> &_states) { states = _states; }
  Transfers(const State &_states) { states.push_back(_states); }
  void deserialize(BinaryReader &reader) {
    int len = (int)reader.readVarInt();
    for (int i = 0; i < len; i++) {
      State state_item;
      reader.readSerializable(state_item);
      states.push_back(state_item);
    }
  }

  void serialize(BinaryWriter &writer) {
    writer.writeSerializableArray(states);
  }
};

#endif