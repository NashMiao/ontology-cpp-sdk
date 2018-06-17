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
    COIN_VERSION = 0x17;
  }

  Address(const std::vector<unsigned char> &value) {
    this->UIntBase::UIntBase(20, value);
  }

  void set_zero(std::string str_zero) {
    memcpy(ZERO, (unsigned char *)str_zero.c_str(), 20);
  }

  Address operator=(const Address &b) {
    Address ret_address;
    ret_address.set_data_bytes(b.get_data_bytes);
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

  Address AddressFromePubKeyNeo(std::vector<unsigned char> publicKey) {
    ScriptBuilder builder;
    builder.push(publicKey);
    builder.add(ScriptOp::OP_CHECKSIG);
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

  Address addressFromPubKey(std::vector<unsigned char> publicKey) {
    ScriptBuilder script_builder;
    script_builder.push(publicKey);
    script_builder.push(ScriptOp::OP_CHECKSIG);
    Digest digest;
    std::vector<unsigned char> hash160_vec;
    hash160_vec = digest.hash160(script_builder.toArray());
    Address address(hash160_vec);
    return address;
  }

  Address addressFromMultiPubKeys(int m,
                                  std::vector<unsigned char> publicKeys) {
    if (m <= 0 || m > publicKeys.size() || publicKeys.size() > 24) {
      throw "SDKException(ErrorCode.ParamError)";
    }
    try {
      BinaryWriter writer;
      writer.writeByte((unsigned char)publicKeys.size());
      writer.writeByte((unsigned char)m);
      for (size_t i = 0; i < publicKeys.size(); i++) {
        writer.writeVarBytes(publicKeys[i]);
      }
      std::vector<unsigned char> hash160;
      Digest digest;
      hash160 = digest.hash160(writer.toByteArray());
      hash160[0] = 0x02;
    } catch (const char *e) {
      cerr << e << endl;
    }
    Address u160(hash160);
    return u160;
  }

  Address decodeBase58(std::string address) {
    Helper helper;
    std::vector<unsigned char> data;
    data = helper.DecodeBase58(address);
    if (data.size() != 25) {
      throw "SDKException(ErrorCode.ParamError)";
    }
    if (data[0] != COIN_VERSION) {
      throw "SDKException(ErrorCode.ParamError)";
    }
    Digest digest;
    std::vector<unsigned char> checksum =
        digest.sha256(digest.sha256(data, 0, 21));
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
};

#endif // !ADDRESS_H