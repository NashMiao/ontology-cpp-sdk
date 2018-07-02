#ifndef INVENTORY_H
#define INVENTORY_H

#include "../crypto/Digest.h"
#include "Signable.h"

class Inventory : public Signable
{
private:
  std::vector<unsigned char> _hash;

protected:
  Inventory() : Signable() {}

public:
  std::vector<unsigned char> hash()
  {
    if (_hash.empty())
    {
      std::vector<unsigned char> hash_data;
      hash_data = getHashData();
      _hash = Digest::hash256(hash_data);
    }
    return _hash;
  }
};
#endif