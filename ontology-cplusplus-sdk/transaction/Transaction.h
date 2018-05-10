#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <boost/multiprecision/cpp_int.hpp>
#include "TransactionType.h"
using namespace boost::multiprecision;

class Transaction
{
    uint8_t version = 0;
    TransactionType txType;
    // int nonce = new Random().nextInt();
    int nonce;
    Attribute[] attributes;
    Fee[] fee = new Fee[0];
    long networkFee;
    Sig[] sigs = new Sig[0];
};

#endif // !TRANSACTION_H