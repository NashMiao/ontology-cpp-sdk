#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "BinaryReader.h"
#include "BinaryWriter.h"

#include <vector>

class Serializable{
public:
  virtual void serialize(BinaryWriter &writer) = 0;
  virtual void deserialize(BinaryReader &reader) = 0;
  virtual std::vector<unsigned char> toArray() = 0;
  virtual std::string toHexString() = 0;
};

#endif