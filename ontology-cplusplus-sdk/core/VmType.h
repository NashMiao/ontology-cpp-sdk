#ifndef VMTYPE_H
#define VMTYPE_H

enum VmType { Native = 0xff, NEOVM = 0x80, WASMVM = 0x90 };

VmType valueOf(unsigned char v) {
  VmType ret;
  switch (v) {
  case 0xff:
    ret = Native;
    break;
  case 0x80:
    ret = NEOVM;
    break;
  case 0x90:
      ret = WASMVM;
      break;
  default:
    throw "IllegalArgumentException";
  }
  return ret;
}

#endif