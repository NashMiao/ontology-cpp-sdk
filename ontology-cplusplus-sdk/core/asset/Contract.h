#ifndef CONTRACT_H
#define CONTRACT_H

#include "../../common/Address.h"
#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"

#include <string>
#include <vector>

class Contract : public BinaryReader, public BinaryWriter {
private:
  unsigned char version;
  std::vector<unsigned char> code;
  Address constracHash;
  std::string method;
  std::vector<unsigned char> args;

public:
  Contract() {}
  Contract(unsigned char _version,const std::vector<unsigned char> &_code,
           const Address &_constracHash, const std::string &_method,
           const std::vector<unsigned char> &_args) {
    version = version;
    if (!_code.empty()) {
      code = _code;
    }
    constracHash = _constracHash;
    method = _method;
    args = _args;
  }
  void serialize(BinaryWrite &writer) {
    writer.writeByte(version);
    writer.writeVarBytes(code);
    writer.writeSerializable(constracHash);
    writer.writeVarBytes((unsigned char *)method.c_str());
    writer.writeVarBytes(args);
  }
  void deserialize(BinaryReader &reader) {
    try {
      version = reader.readByte();
      code = reader.readVarBytes();
      reader.readSerializable(constracHash);
      method = std::string(reader.readVarBytes());
      args = reader.readVarBytes();
    } catch (const char *e) {
      std::cerr << e << std::endl;
    }
  }
};

#endif