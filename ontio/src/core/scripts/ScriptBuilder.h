#ifndef SCRIPTBUILDER_H
#define SCRIPTBUILDER_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <algorithm>
#include <stdexcept>
#include <limits>
#include <vector>

#include <openssl/bn.h>

#include "../../common/Helper.h"
#include "ScriptOp.h"

class ScriptBuilder {
private:
  std::vector<unsigned char> uc_vec;

  std::vector<unsigned char> num2bytes(const long long v, int bytes_len) {
    std::vector<unsigned char> bytes;
    for (int i = 0; i < bytes_len; i++) {
      bytes.push_back((v >> 8 * (7 - i)) & 0xFF);
    }
    int n = 1;
    // little endian if true
    if (*(char *)&n == 1) {
      std::reverse(std::begin(bytes), std::end(bytes));
    }
    return bytes;
  }

public:
  ScriptBuilder add(unsigned char op) {
    uc_vec.push_back(op);
    return *this;
  }

  ScriptBuilder add(ScriptOp sop) {
    unsigned char uc_sop;
    uc_sop = ScriptOpMethod::getByte(sop);
    return add(uc_sop);
  }

  ScriptBuilder add(const std::vector<unsigned char> &script) {
    uc_vec.insert(uc_vec.end(), script.begin(), script.end());
    return *this;
  }

  ScriptBuilder push(bool b) {
    if (b == true) {
      return add(ScriptOpMethod::getByte(ScriptOp::OP_1));
    }
    return add(ScriptOpMethod::getByte(ScriptOp::OP_0));
  }

  ScriptBuilder push(int num) {
    if (num == -1) {
      return add(ScriptOp::OP_1NEGATE);
    }
    if (num == 0) {
      return add(ScriptOp::OP_0);
    }
    if (num > 0 && num <= 16) {
      return add(
          ((unsigned long)ScriptOpMethod::getByte(ScriptOp::OP_1) - 1 + num));
    }
    if (num < 0 || num > std::numeric_limits<long long>::max()) {
      throw std::runtime_error("IllegalArgumentException");
    }
    std::vector<unsigned char> bytes;
    bytes = num2bytes(num, sizeof(int));
    return push(bytes);
  }

  ScriptBuilder push(long long num) {
    if (num == -1) {
      return add(ScriptOp::OP_1NEGATE);
    }
    if (num == 0) {
      return add(ScriptOp::OP_0);
    }
    if (num > 0 && num <= 16) {
      return add(
          ((unsigned long)ScriptOpMethod::getByte(ScriptOp::OP_1) - 1 + num));
    }
    if (num < 0 || num > std::numeric_limits<long long>::max()) {
      throw std::runtime_error("IllegalArgumentException");
    }
    std::vector<unsigned char> bytes;
    bytes = num2bytes(num, sizeof(long long));
    return push(bytes);
  }

  ScriptBuilder push(const long long num, int bytes_len) {
    std::vector<unsigned char> vec;
    vec = num2bytes(num, bytes_len);
    return add(vec);
    return *this;
  }

  ScriptBuilder push(const char *c_bytes) {
    unsigned char *uc_bytes = (unsigned char *)c_bytes;
    std::vector<unsigned char> vec(uc_bytes, uc_bytes + strlen(c_bytes));
    push(vec);
    return *this;
  }

  ScriptBuilder push(const std::vector<unsigned char> &data) {
    if (data.empty()) {
      throw "NullPointerException";
    }
    if (data.size() <= (int)ScriptOpMethod::getByte(ScriptOp::OP_PUSHBYTES75)) {
      uc_vec.push_back((unsigned char)data.size());
      add(data);
    } else if (data.size() < 0x100) {
      add(ScriptOpMethod::getByte(ScriptOp::OP_PUSHDATA1));
      push((long long)data.size(), 1);
      num2bytes((long long)data.size(), 2);
      add(data);
    } else if (data.size() < 0x10000) {
      add(ScriptOpMethod::getByte(ScriptOp::OP_PUSHDATA2));
      push((long long)data.size(), 2);
      add(data);
    } else if (data.size() < 0x10000000) {
      add(ScriptOpMethod::getByte(ScriptOp::OP_PUSHDATA4));
      push((long long)data.size(), 4);
      add(data);
    } else {
      throw std::runtime_error("IllegalArgumentException");
    }
    return *this;
  }

  ScriptBuilder pushHexStr(const std::string &str) {
    std::vector<unsigned char> byte_uc;
    byte_uc = Helper::hexStringToByte(str);
    push(byte_uc);
    return *this;
  }

  ScriptBuilder push(const std::string &str) {
    std::vector<unsigned char> byte_uc(str.begin(), str.end());
    push(byte_uc);
    return *this;
  }

  ScriptBuilder push(BIGNUM *bn) {
    if (BN_is_word(bn, -1)) {
      return add(ScriptOpMethod::getByte(ScriptOp::OP_1NEGATE));
    }
    if (BN_is_zero(bn)) {
      return add(ScriptOpMethod::getByte(ScriptOp::OP_0));
    }
    if (BN_get_word(bn) > 0 && BN_get_word(bn) < 16) {
      return add(((unsigned long)ScriptOpMethod::getByte(ScriptOp::OP_1) - 1 +
                  BN_get_word(bn)));
    }
    if (BN_get_word(bn) < 0 ||
        BN_get_word(bn) > std::numeric_limits<long long>::max()) {
      throw std::runtime_error("IllegalArgumentException");
    }
    return *this;
  }

  ScriptBuilder pushNum(short num) {
    if (num == 0) {
      return add(ScriptOpMethod::getByte(ScriptOp::OP_0));
    } else if (num < 16) {
      return add(num - 1 + (short)ScriptOpMethod::getByte(ScriptOp::OP_1));
    }
    return *this;
  }

  ScriptBuilder pushPack() {return add(ScriptOpMethod::getByte(ScriptOp::OP_PACK));
  }

  std::vector<unsigned char> toArray() { return uc_vec; }
};

#endif