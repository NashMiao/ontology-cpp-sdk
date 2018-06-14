#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"
#include "AttributeUsage.h"
#include <string>
#include <vector>

using namespace boost::multiprecision;

class Attribute {
private:
  AttributeUsage usage;
  std::vector<unsigned char> data;
  int size;

public:
  void serialize(BinaryWriter *writer) {
    writer.writeByte(usage);
    try
    {
      if (usage == AttributeUsage::Script || usage == AttributeUsage::DescriptionUrl || usage == AttributeUsage::Description ||
          usage == AttributeUsage::Nonce) {
        writer.writeVarBytes(data);
      } else {
        throw "IOException";
      }
    } catch (const char *e) {
      cerr << e << endl;
    }
  }

  void deserialize(BinaryReader *reader) {
    try {
      usage = valueOf(reader->readByte());
      cout << "usage: " << usage << endl;
      if (usage == AttributeUsage::Script || usage == AttributeUsage::DescriptionUrl || usage == AttributeUsage::Description ||
          usage == AttributeUsage::Nonce) {
        data = reader->readVarBytes(255);
        cout << "data: " << data << endl;
      } else {
        throw "IOException";
      }
    } catch (const char *e) {
      cerr << e << endl;
    }
  }
};
#endif // !ATTRIBUTE_H