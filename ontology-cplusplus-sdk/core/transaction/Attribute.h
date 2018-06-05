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
  void deserialize(BinaryReader *reader) {
    try {
      usage = valueOf(reader->readByte());
      cout <<"usage: "<< usage << endl;
      if (usage == Script || usage == DescriptionUrl || usage == Description ||
          usage == Nonce) {
        data = reader->readVarBytes(255);
        cout<<"data: "<<data<<endl;
      } else {
        throw "IOException";
      }
    } catch (const char *e) {
      cerr << e << endl;
    }
  }
};
#endif // !ATTRIBUTE_H