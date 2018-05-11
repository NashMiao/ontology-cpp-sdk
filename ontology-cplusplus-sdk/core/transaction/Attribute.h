#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../../io/BinaryReader.h"
#include "AttributeUsage.h"
#include <string>
#include <vector>

using namespace boost::multiprecision;

class Attribute {
private:
  AttributeUsage usage;
  std::string data;
  int size;

public:
  void deserialize(BinaryReader& reader) {
    usage = valueOf(reader.readByte());
    if (usage == Script || usage == DescriptionUrl || usage == Description ||
        usage == Nonce) {
      data = reader.readVarBytes(255);
    } else {
      throw "IOException";
    }
  }
};

#endif // !ATTRIBUTE_H