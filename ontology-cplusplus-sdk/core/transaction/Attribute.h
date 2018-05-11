#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include "AttributeUsage.h"

using namespace boost::multiprecision;

class Attribute
{
  public:
    AttributeUsage usage;
    std::vector<uint8_t> data;
    int size;
};

#endif // !ATTRIBUTE_H