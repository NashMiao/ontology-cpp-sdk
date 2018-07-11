#ifndef TRANSACTIONTYPE_H
#define TRANSACTIONTYPE_H

#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"

/**
 * list transaction types
 */
enum class TransactionType : int
{
  Bookkeeping = 0x00,
  Bookkeeper = 0x02,
  Claim = 0x03,
  Enrollment = 0x04,
  Vote = 0x05,
  DeployCode = 0xd0,
  InvokeCode = 0xd1,
};

class TransactionTypeMethod
{
public:
  static unsigned char getByte(TransactionType type)
  {
    unsigned char ret;
    switch (type)
    {
    case TransactionType::Bookkeeping:
      ret = 0x00;
      break;
    case TransactionType::Bookkeeper:
      ret = 0x02;
      break;
    case TransactionType::Claim:
      ret = 0x03;
      break;
    case TransactionType::Enrollment:
      ret = 0x04;
      break;
    case TransactionType::Vote:
      ret = 0x05;
      break;
    case TransactionType::DeployCode:
      ret = 0xd0;
      break;
    case TransactionType::InvokeCode:
      ret = 0xd1;
      break;
    default:
      throw "TransactionType Error";
    }
    return ret;
  }

  static TransactionType getTransactionType(int type)
  {
    if (type == 0x00)
    {
      return TransactionType::Bookkeeping;
    }
    else if (type == 0x02)
    {
      return TransactionType::Bookkeeper;
    }
    else if (type == 0x03)
    {
      return TransactionType::Claim;
    }
    else if (type == 0x04)
    {
      return TransactionType::Enrollment;
    }
    else if (type == 0x05)
    {
      return TransactionType::Vote;
    }
    else if (type == 0xd0)
    {
      return TransactionType::DeployCode;
    }
    else if (type == 0xd1)
    {
      return TransactionType::InvokeCode;
    }
    else
    {
      throw "TransactionType error";
    }
  }

  static TransactionType TxTypeDeserialize(BinaryReader &reader)
  {
    TransactionType TxType;
    int val = reader.readByte();
    switch (val)
    {
    case 0x00:
      TxType = TransactionType::Bookkeeping;
      break;
    case 0x02:
      TxType = TransactionType::Bookkeeper;
      break;
    case 0x03:
      TxType = TransactionType::Claim;
      break;
    case 0x04:
      TxType = TransactionType::Enrollment;
      break;
    case 0x05:
      TxType = TransactionType::Vote;
      break;
    case 0xd0:
      TxType = TransactionType::DeployCode;
      break;
    case 0xd1:
      TxType = TransactionType::InvokeCode;
      break;
    default:
      throw "IOException";
    }
    return TxType;
  }
};
#endif // !TRANSACTIONTYPE_H