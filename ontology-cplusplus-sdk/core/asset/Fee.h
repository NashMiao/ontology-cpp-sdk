#ifndef FEE_H
#define FEE_H

#include "../../common/Address.h"

class Fee
{
  public:
    long long amount;
    Address payer;
    Fee(long long &amount, Address &payer)
    {
        amount = amount;
        payer = payer;
    }
};
#endif // !FEE_H