#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Attribute.h"
#include "TransactionType.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <vector>

using namespace boost::multiprecision;

class Transaction {
  uint8_t version = 0;
  TransactionType txType;
  // int nonce = new Random().nextInt();
  int nonce;
  std::vector<Attribute> attributes;
  // Fee[] fee = new Fee[0];
  long long networkFee;
  // Sig[] sigs = new Sig[0];
};

#endif // !TRANSACTION_H