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
  static constexpr std::size_t zero_size = 20;
  std::vector<unsigned char> ZERO;
  unsigned char COIN_VERSION;

public:
  Address() : COIN_VERSION(0x17) { ZERO.reserve(zero_size); }

  Address(const std::vector<unsigned char> &value) : UIntBase(20, value) {}

  void set_zero(std::string str_zero) { memcpy(&ZERO[0], &str_zero[0], 20); }

  Address& operator=(const Address &b) {
    std::vector<unsigned char> b_data_bytes;
    b_data_bytes = b.get_data_bytes();
    this->set_data_bytes(b_data_bytes);
    this->ZERO = b.ZERO;
    this->COIN_VERSION = b.COIN_VERSION;
    return *this;
  }

  static Address parse(std::string value) {
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
    v = Helper::hexToBytes(value);
    Address ret_address(v);
    return ret_address;
  }

  bool tryParse(std::string s, Address result) {
    try {
      Address v = parse(s);
      this->set_data_bytes(v.get_data_bytes());
      return true;
    } catch (const char *err) {
      cerr << err << endl;
    }
  }

  Address toScriptHash(std::vector<unsigned char> script) {
    Digest digest;
    Address address(digest.hash160(script));
    return address;
  }

  Address AddressFromVmCode(std::string codeHexStr) {
    std::vector<unsigned char> codeUcVec;
    codeUcVec = Helper::hexToBytes(codeHexStr);
    Address code = toScriptHash(codeUcVec);
    return code;
  }

  static Address AddressFromePubKeyNeo(std::vector<unsigned char> publicKey) {
    ScriptBuilder builder;
    builder.push(publicKey);
    builder.add(getByte(ScriptOp::OP_CHECKSIG));
    Digest digest;
    std::vector<unsigned char> hash160;
    hash160 = digest.hash160(builder.toArray());
    Address address(hash160);
    return address;
  }

  // void deserialize(BinaryReader &reader) {
  //   std::string str;
  //   str = reader.readVarBytes();
  //   memcpy(ZERO, (unsigned char *)str.c_str(), 20);
  // }

  std::string toHexString() {
    std::vector<unsigned char> value;
    Helper helper;
    return helper.toHexString(value);
  }

  static Address addressFromPubKey(std::vector<unsigned char> publicKey) {
    ScriptBuilder script_builder;
    script_builder.push(publicKey);
    script_builder.push(getByte(ScriptOp::OP_CHECKSIG));
    Digest digest;
    std::vector<unsigned char> hash160_vec;
    hash160_vec = digest.hash160(script_builder.toArray());
    Address address(hash160_vec);
    return address;
  }

  Address addressFromMultiPubKeys(int m, std::vector<std::string> publicKeys) {
    if (m <= 0 || m > int(publicKeys.size()) || int(publicKeys.size()) > 24) {
      throw "SDKException(ErrorCode.ParamError)";
    }
    std::vector<unsigned char> hash160_vec;
    try {
      BinaryWriter writer;
      writer.writeByte((unsigned char)publicKeys.size());
      writer.writeByte((unsigned char)m);
      for (size_t i = 0; i < publicKeys.size(); i++) {
        writer.writeVarBytes(publicKeys[i]);
      }
      Digest digest;
      hash160_vec = digest.hash160(writer.toByteArray());
      hash160_vec[0] = 0x02;
    } catch (const char *e) {
      cerr << e << endl;
    }
    Address u160_addr(hash160_vec);
    return u160_addr;
  }

  Address decodeBase58(std::string address) {
    std::vector<unsigned char> data;
    Helper::DecodeBase58(address, data);
    if (data.size() != 25) {
      throw "SDKException(ErrorCode.ParamError)";
    }
    if (data[0] != COIN_VERSION) {
      throw "SDKException(ErrorCode.ParamError)";
    }
    std::vector<unsigned char> checksum;
    checksum = Digest::sha256(Digest::sha256(data, 0, 21));
    for (int i = 0; i < 4; i++) {
      if (data[data.size() - 4 + i] != checksum[i]) {
        throw "SDKException(ErrorCode.ParamError)";
      }
    }
    std::vector<unsigned char> buffer;
    buffer.assign(data.begin() + 1, data.begin() + 21);
    return Address(buffer);
  }

  std::string toBase58() {
    std::vector<unsigned char> data;
    data.push_back(COIN_VERSION);
    std::vector<unsigned char> data_bytes;
    data_bytes = toArray();
    data.insert(data.end(), data_bytes.begin(), data_bytes.begin() + 20);
    Digest digest;
    std::vector<unsigned char> checksum;
    checksum = digest.sha256(data, 0, 21);
    checksum = digest.sha256(checksum);
    data.insert(data.end(), checksum.begin(), checksum.begin() + 4);
    std::string str;
    str = Helper::EncodeBase58(data);
    return str;
  }
};

#endif // !ADDRESS_H