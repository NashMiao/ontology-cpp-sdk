#ifndef ATTRIBUTEUSAGE_H
#define ATTRIBUTEUSAGE_H

enum AttributeUsage {
  Nonce = 0x00,
  Script = 0x20,
  DescriptionUrl = 0x81,
  Description = 0x90
};

AttributeUsage valueOf(int v) {
  AttributeUsage ret;
  switch (v) {
  case 0x00:
    ret = Nonce;
    break;
  case 0x20:
    ret = Script;
    break;
  case 0x81:
    ret = DescriptionUrl;
    break;
  case 0x90:
    ret = Description;
    break;
  default:
    throw "IllegalArgumentException";
  }
  return ret;
}

#endif // !ATTRIBUTEUSAGE_H