#ifndef UINTBASE_H
#define UINTBASE_H

#include "../io/Serializable.h"
#include <vector>
#include <string>

class UIntBase : public Serializable {
private:
  std::vector<unsigned char> data_bytes;

public:
  UIntBase(int bytes, const std::vector<unsigned char> &value) {
    if (value.empty()) {
        data_type.assign(bytes, '0');
    }
    else if(value.size()!=bytes){
        throw "IllegalArgumentException";
    }
    else{
        data_bytes = value;
    }
  }

  std::vector<unsigned char> get_data_bytes(){
    return data_bytes;
  }

  virtual void serialize(BinaryWriter &writer) = 0;
  virtual void deserialize(BinaryReader &reader) = 0;
  virtual std::vector<unsigned char> toArray() = 0;
  virtual std::string toHexString() = 0;
};

#endif