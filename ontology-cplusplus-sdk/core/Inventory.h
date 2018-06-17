#ifndef INVENTORY_H
#define INVENTORY_H

#include "../crypto/Digest.h"
#include "Signable.h"

class Inventory : public Signable {
private:
  std::vector<unsigned char> hash;

public:
  std::vector<unsigned char> hash() {
    if (hash.empty()) {
      Digest digest;
      hash = digest.hash256(getHashData());
    }
    return hash;
  }
};
#endif