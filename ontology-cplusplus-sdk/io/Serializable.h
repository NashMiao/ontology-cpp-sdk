#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../common/Helper.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

#include <vector>

class Serializable {
  virtual void serialize(BinaryWriter &writer) = 0;
  virtual void deserialize(BinaryReader &reader) = 0;
  std::vector<unsigned char> toArray() {
    BinaryWriter writer;
    serialize(writer);
    return writer.toByteArray();
  }
  std::string toHexString() {
    Helper helper;
    helper.toHexString();
  }
};

#endif