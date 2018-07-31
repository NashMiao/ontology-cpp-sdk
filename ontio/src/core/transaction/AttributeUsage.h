#ifndef ATTRIBUTEUSAGE_H
#define ATTRIBUTEUSAGE_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <stdexcept>
#include <string>

enum class AttributeUsage
{
  Nonce = 0x00,
  Script = 0x20,
  DescriptionUrl = 0x81,
  Description = 0x90
};

class AttributeUsageMethod
{
public:
  static AttributeUsage valueOf(int v)
  {
    AttributeUsage ret;
    switch (v)
    {
    case 0x00:
      ret = AttributeUsage::Nonce;
      break;
    case 0x20:
      ret = AttributeUsage::Script;
      break;
    case 0x81:
      ret = AttributeUsage::DescriptionUrl;
      break;
    case 0x90:
      ret = AttributeUsage::Description;
      break;
    default:
      throw std::runtime_error("IllegalArgumentException");
    return ret;
     }
  }

  static unsigned char getByte(AttributeUsage usage)
  {
    unsigned char ret;
    switch (usage)
    {
    case AttributeUsage::Nonce:
      ret = 0x00;
      break;
    case AttributeUsage::Script:
      ret = 0x20;
      break;
    case AttributeUsage::DescriptionUrl:
      ret = 0x81;
      break;
    case AttributeUsage::Description:
      ret = 0x90;
      break;
    default:
      throw std::runtime_error("IllegalArgumentException");
    }
    return ret;
  }
};

#endif // !ATTRIBUTEUSAGE_H