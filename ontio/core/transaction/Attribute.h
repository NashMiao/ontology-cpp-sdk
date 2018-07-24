#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>
#include <vector>

#include <nlohmann/json.hpp>

#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"
#include "AttributeUsage.h"

using namespace boost::multiprecision;

class Attribute
{
private:
  AttributeUsage usage;
  std::vector<unsigned char> data;
  int size;

public:
  Attribute() {}
  Attribute(AttributeUsage _usage, const std::vector<unsigned char> &_data,
            int _size)
      : usage(_usage), data(_data), size(_size) {}
  nlohmann::json json()
  {
    nlohmann::json result;
    result["Usage"] = (int)AttributeUsageMethod::getByte(usage);
    result["Data"] = data;
    result["Size"] = size;
    return result;
  }

  void serialize(BinaryWriter *writer)
  {
    writer->writeByte(AttributeUsageMethod::getByte(usage));
    try
    {
      if (usage == AttributeUsage::Script ||
          usage == AttributeUsage::DescriptionUrl ||
          usage == AttributeUsage::Description ||
          usage == AttributeUsage::Nonce)
      {
        writer->writeVarBytes(data);
      }
      else
      {
        throw "IOException";
      }
    }
    catch (const char *e)
    {
      cerr << e << endl;
    }
  }

  void deserialize(BinaryReader *reader)
  {
    try
    {
      usage = AttributeUsageMethod::valueOf(reader->readByte());
      if (usage == AttributeUsage::Script ||
          usage == AttributeUsage::DescriptionUrl ||
          usage == AttributeUsage::Description ||
          usage == AttributeUsage::Nonce)
      {

        data = reader->readVarBytes_vec(255);
      }
      else
      {
        throw "IOException";
      }
    }
    catch (const char *e)
    {
      cerr << e << endl;
    }
  }
};
#endif // !ATTRIBUTE_H