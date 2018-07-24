#ifndef INVOKECODE_H
#define INVOKECODE_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <vector>

#include "../../core/transaction/Transaction.h"
#include "../../core/transaction/TransactionType.h"
#include "../program/Program.h"

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

  InvokeCodeTransaction(const std::vector<unsigned char> &_code,
                        long long _gasPrice, long long _gasLimit)
      : Transaction(TransactionType::InvokeCode, _gasPrice = _gasPrice,
                    _gasLimit = _gasLimit),
        code(_code) {}

  InvokeCodeTransaction operator=(InvokeCodeTransaction tx)
  {
    this->code = tx.code;
    this->Transaction::operator=(tx);
    return *this;
  }

  nlohmann::json json()
  {
    nlohmann::json Result = Transaction::json();
    Result["Payload"] = {"Code", Helper::toHexString(code)};
    return Result;
  }

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