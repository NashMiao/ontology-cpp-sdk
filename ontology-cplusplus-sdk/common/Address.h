#ifndef ADDRESS_H
#define ADDRESS_H

#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include <string>

class Address
{
  private:
    std::string ZERO;
    unsigned char COIN_VERSION;

  public:
    Address() { COIN_VERSION = 0x41; }
    void deserialize(BinaryReader &reader){
        ZERO=reader.readVarBytes();
    }
};

#endif // !ADDRESS_H