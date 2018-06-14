#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../common/Helper.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

#include <vector>

class Serializable {
public:
  virtual void serialize(BinaryWriter &writer);
  virtual void deserialize(BinaryReader &reader);
  std::vector<unsigned char> toArray() {
    BinaryWriter writer;
    serialize(writer);
    return writer.toByteArray();
  }
  std::string toHexString() {
    Helper helper;
    return helper.toHexString();
  }
};

#endif