#ifndef VMTYPE_H
#define VMTYPE_H

#if __cplusplus < 201103L
    #error "use --std=c++11 option for compile."
#endif

enum class VmType { Native = 0xff, NEOVM = 0x80, WASMVM = 0x90 };

VmType valueOf(unsigned char v) {
  VmType ret;
  switch (v) {
  case 0xff:
    ret = VmType::Native;
    break;
  case 0x80:
    ret = VmType::NEOVM;
    break;
  case 0x90:
    ret = VmType::WASMVM;
    break;
  default:
    throw "IllegalArgumentException";
  }
  return ret;
}

unsigned char get_uc_vmtype(VmType type) {
  return static_cast<unsigned char>(type);
}

#endif