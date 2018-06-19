#ifndef UINTBASE_H
#define UINTBASE_H

#include "../io/Serializable.h"
#include "Helper.h"
#include <string>
#include <vector>

class UIntBase : public Serializable {
private:
  std::vector<unsigned char> data_bytes;

public:
  UIntBase(int bytes, const std::vector<unsigned char> &value) {
    if (value.empty()) {
      data_type.assign(bytes, '0');
    } else if (value.size() != bytes) {
      throw "IllegalArgumentException";
    } else {
      data_bytes = value;
    }
  }

  std::vector<unsigned char>
  set_data_bytes(const std::vector<unsigned char> &_data_bytes) {
    data_bytes = _data_bytes;
  }

  UIntBase operator=(const UIntBase & base){
    UIntBae ret_base;
    ret_base.data_bytes = base.data_bytes;
    return ret_base;
  }

  std::vector<unsigned char> get_data_bytes() { return data_bytes; }

  void serialize(BinaryWriter *writer) { writer->write(data_bytes); }

  void deserialize(BinaryReader *reader) { reader->read(data_bytes); }

  std::vector<unsigned char> toArray() { return data_bytes; }

  std::string toHexString() {
    Helper helper;
    std::string str;
    str = helper.toHexString(toArray());
    str.reserve(str.begin(), str.end());
    return str;
  }
};

#endif