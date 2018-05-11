#ifndef FEE_H
#define FEE_H

#include "../../common/Address.h"
#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"

class Fee
{
private:
  long long amount;
  Address payer;

public:
  Fee(long long &amount, Address &payer)
  {
    amount = amount;
    payer = payer;
  }

  void deserialize(BinaryReader &reader)
  {
    amount = reader.readLong();
    payer.deserialize(reader);
  }
};
#endif // !FEE_H