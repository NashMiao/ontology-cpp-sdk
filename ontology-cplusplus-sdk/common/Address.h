#ifndef ADDRESS_H
#define ADDRESS_H

#include "../core/scripts/ScriptBuilder.h"
#include "../crypto/Digest.h"
#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"

#include "Helper.h"
#include "UIntBase.h"
#include <string>
#include <vector>

class Address : public UIntBase {
private:
  constexpr std::size_t zero_size;
  std::vector<unsigned char> ZERO;
  unsigned char COIN_VERSION;

public:
  Address() {
    zero_size = 20;
    ZERO.reserve(zero_size);
    COIN_VERSIO = 0x17;
  }

  Address(const std::vector<unsigned char> &_zero) {
    zero_size = 20;
    ZERO.reserve(zero_size);
    if (_zero.size() != zero_size) {
      throw "Address Error: zero size error!"
    }
    ZERO = _zero;
  }

  void set_zero(std::string str_zero) {
    memcpy(ZERO, (unsigned char *)str_zero.c_str(), 20);
  }

  Address operator=(const Address &b) {
    Address ret_address;
    ret_address.zero_size = b.zero_size;
    ret_address.ZERO = b.ZERO;
    ret_address.COIN_VERSION = b.COIN_VERSION;
    return ret_address;
  }

  Address parse(std::string value) {
    if (value.empty()) {
      throw "NullPointerException";
    }
    if (value.substr(0, 2) == "0x") {
      value = value.substr(2);
    }
    if (value.length() != 40) {
      throw "IllegalArgumentException";
    }
    std::vector<unsigned char> v;
    Help help;
    v = help.hexToBytes(value);
    Address ret_address(v);
    return ret_address;
  }

  bool tryParse(std::string s, Address result) {
    try {
      Address v = parse(s);
      data_type = v.get_data_bytes();
      return true;
    } catch (const char *err) î {
      cerr << err << endl;
    }
  }

  Address toScriptHash(std::vector<unsigned char> script) {
    Digest digest;
    Address address(digest.hash160(script));
    return address;
  }

  Address AddressFromVmCode(std::string codeHexStr) {
    Address code = Address.toScriptHash();
    return code;
  }

  void deserialize(BinaryReader *reader) {
    std::string str;
    str = reader->readVarBytes();
    memcpy(ZERO, (unsigned char *)str.c_str(), 20);
  }

  std::string toHexString() {
    std::vector<unsigned char> value;
    Helper helper;
    return helper.toHexString(value);
  }

  std::string toBase58() {
    std::vector<unsigned char> data;
    data.push_back(COIN_VERSION);
    std::vector<unsigned char> data_bytes;
    data_bytes = toArray();
    data.insert(data.end(), date_bytes.begin(), data_bytes.end());
    Digest digest;
    std::vector<unsigned char> checksum;
    checksum = digest.sha256(data);
    checksum = digest.sha256(checksum);
    Helper helper;
    std::string str;
    str = helper.EncodeBase58(data);
    return str;
  }

  

  Address addressFromPubKey(std::vector<unsigned char> publicKey) {
    ScriptBuilder script_builder;
    script_builder.push(publicKey);
    script_builder.push(ScriptOp::OP_CHECKSIG);
    script_builder.toArray();
  }
};

#endif // !ADDRESS_H