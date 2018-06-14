#ifndef TRANSACTIONTYPE_H
#define TRANSACTIONTYPE_H

#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"

/**
 * list transaction types
 */
enum TransactionType {
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
    TxType = Bookkeeping;
    break;
  case 0x02:
    TxType = Bookkeeper;
    break;
  case 0x03:
    TxType = Claim;
    break;
  case 0x04:
    TxType = Enrollment;
    break;
  case 0x05:
    TxType = Vote;
    break;
  case 0xd0:
    TxType = DeployCode;
    break;
  case 0xd1:
    TxType = InvokeCode;
    break;
  default:
    throw "IOException";
  }
  return TxType;
}

#endif // !TRANSACTIONTYPE_H