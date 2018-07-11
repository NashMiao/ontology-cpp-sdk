#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../common/Helper.h"
#include "BinaryReader.h"
#include "BinaryWriter.h"

#include <vector>

class Serializable
{
protected:
  Serializable() {}

public:
  virtual void serialize(BinaryWriter *writer) = 0;
  virtual void deserialize(BinaryReader *reader) = 0;

  std::vector<unsigned char> toArray()
  {
    BinaryWriter writer;
    try
    {
      serialize(&writer);
    }
    catch (const char *ex)
    {
      cerr << ex << endl;
      throw "UnsupportedOperationException(ex)";
    }
    return writer.toByteArray();
  }

  std::string toHexString()
  {
    std::string str;
    str = Helper::toHexString(toArray());
    return str;
  };
};

#endif