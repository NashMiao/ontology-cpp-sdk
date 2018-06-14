#ifndef INVENTORY_H
#define INVENTORY_H

#include "../crypto/Digest.h"
#include "Signable.h"

class Inventory : public Signable, public Digest {
private:
  std::vector<unsigned char> hash;

public:
  std::vector<unsigned char> hash() {
    if (hash.empty()) {
      hash = hash256(getHashData());
    }
    return hash;
  }
};
#endif