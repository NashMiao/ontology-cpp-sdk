#ifndef INVOKECODE_H
#define INVOKECODE_H

#include "../transaction/Transaction.h"

#include <vector>

class InvokeCode : public Transaction {
private:
  unsigned char vmType;
  std::vector<unsigned char> code;

public:
  InvokeCode() {}
  void 
};
#endif