#ifndef TRANSFERS_H
#define TRANSFERS_H

#include "State.h"
#include <vector>

class Transfers {
private:
  std::vector<State> states;

public:
  Transfers() {}
  Transfers(const std::vector<State> &_states) { states = _states; }
  Transfers(const State &_states) { states.push_back(_states); }
};

#endif