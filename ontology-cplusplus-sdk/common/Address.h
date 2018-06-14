#ifndef ADDRESS_H
#define ADDRESS_H

#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "Helper.h"
#include <string>
#include <vector>

class Address {
private:
  constexpr std::size_t zero_size;
  std::vector<unsigned char> ZERO;
  unsigned char COIN_VERSION_ONT;
  unsigned char COIN_VERSIO_NEO;

public:
  Address() {
    zero_size = 20;
    ZERO.reserve(zero_size);
    COIN_VERSION_ONT = 0x41;
    COIN_VERSIO_NEO = 0x17;
  }

  Address(const std::vector<unsigned char> &_zero) {
    zero_size = 20;
    ZERO.reserve(zero_size);
    if (_zero.size() != zero_size) {
      throw "Address Error: zero size error!"
    }
    ZERO = _zero;
  }

  void set_zero(std::string str_zero) {
    memcpy(ZERO, (unsigned char *)str_zero.c_str(), 20);
  }

  Address parse(std::string value) {
    if (value.empty()) {
      throw "NullPointerException";
    }
    if (value.substr(0, 2) == "0x") {
      value = value.substr(2);
    }
    if(value.length()!=40){
      throw "IllegalArgumentException";
    }
    
  }

  void deserialize(BinaryReader &reader) {
    std::string str;
    str = reader.readVarBytes();
    memcpy(ZERO, (unsigned char *)str.c_str(), 20);
  }

  std::string toHexString() {
    std::vector<unsigned char> value;
    Helper helper;
    return helper.toHexString(value);
  }
};

#endif // !ADDRESS_H