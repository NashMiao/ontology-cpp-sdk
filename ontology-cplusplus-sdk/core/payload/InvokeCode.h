#ifndef INVOKECODE_H
#define INVOKECODE_H

#include "../../core/transaction/Transaction.h"
#include "../../core/transaction/TransactionType.h"

#include <vector>

class InvokeCode : public Transaction {
private:
  std::vector<unsigned char> code;

public:
  InvokeCode() { 
    this->Transaction(TransactionType::InvokeCode);
  }
  InvokeCode(const std::vector<unsigned char>& _code,long long _gasPrice,long long _gasLimit,Address _payer):code(_code),gasPrice(_gasPrice),gasLimit(_gasLimit),payer(_payer){}
};
#endif