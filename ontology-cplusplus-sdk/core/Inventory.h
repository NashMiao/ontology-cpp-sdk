#ifndef INVENTORY_H
#define INVENTORY_H

#include "Signable.h"
#include <boost/multiprecision/cpp_int.hpp>

class Inventory::public Signable {
private:
  boost::multiprecision::uint256_t hash;
};
#endif