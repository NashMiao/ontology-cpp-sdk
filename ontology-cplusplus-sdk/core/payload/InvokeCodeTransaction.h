#ifndef INVOKECODE_H
#define INVOKECODE_H

#include "../../core/transaction/Transaction.h"
#include "../../core/transaction/TransactionType.h"

#include <vector>

class InvokeCodeTransaction : public Transaction
{
private:
  std::vector<unsigned char> code;

public:
  InvokeCodeTransaction() : Transaction(TransactionType::InvokeCode) {}

  InvokeCodeTransaction(const std::vector<unsigned char> &_code,
                        long long _gasPrice, long long _gasLimit,
                        Address _payer)
      : Transaction(TransactionType::InvokeCode, _payer = _payer,
                    _gasPrice = _gasPrice, _gasLimit = _gasLimit),
        code(_code) {}

  void serializeExclusiveData(BinaryWriter *writer)
  {
    writer->writeVarBytes(code);
  }
  void deserializeExclusiveData(BinaryReader *reader)
  {
    try
    {
      code = reader->readVarBytes_vec();
    }
    catch (const char *err)
    {
      cerr << err << endl;
    }
  }
};
#endif