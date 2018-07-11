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
      int n = 1;
      // little endian if true
      if (*(char *)&n == 1)
      {
        std::vector<unsigned char> inver_hash;
        size_t vec_sz = _hash.size();
        for (int i = (int)vec_sz - 1; i > -1; i--)
        {
          inver_hash.push_back(_hash[i]);
        }
        _hash = inver_hash;
      }
    }
    return _hash;
  }
};
#endif