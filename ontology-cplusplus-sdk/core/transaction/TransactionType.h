#ifndef TRANSACTIONTYPE_H
#define TRANSACTIONTYPE_H

#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"

/**
 * list transaction types
 */
enum class TransactionType {
  Bookkeeping = 0x00,
  Bookkeeper = 0x02,
  Claim = 0x03,
  Enrollment = 0x04,
  Vote = 0x05,
  DeployCode = 0xd0,
  InvokeCode = 0xd1,
};

TransactionType TxTypeDeserialize(BinaryReader &reader) {
  TransactionType TxType;
  int val = reader.readByte();
  switch (val) {
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

#endif // !TRANSACTIONTYPE_H