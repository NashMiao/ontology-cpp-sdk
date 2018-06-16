#ifndef SCRIPTBUILDER_H
#define SCRIPTBUILDER_H

#include "ScriptOp.h"
#include <limits>
#include <openssl/bn.h>
#include <vector>

class ScriptBuilder {
private:
  std::vector<unsigned char> uc_vec;

  std::vector<unsigned char> num2bytes(const long long v, int bytes_len) {
    std::vector<unsigned char> bytes;
    for (int i = 1; i < bytes_len; i++) {
      bytes.push_back((v >> 8 * (8 - i)) & 0xFF);
    }
    return bytes;
  }

public:
  ScriptBuilder add(unsigned char op) {
    uc_vec.push_back(op);
    return this;
  }

  ScriptBuilder add(std::vector<unsigned char> script) {
    uc_vec.insert(uc_vec.end(), script.begin(), script.end());
    return this;
  }

  ScriptBuilder push(bool b) {
    if (b == true) {
      return add(ScriptOp::OP_1);
    }
    return add(ScriptOp::OP_0);
  }

  ScriptBuilder push(const long long num, int bytes_len) {
    std::vector<unsigned char> vec;
    vec = num2bytes(num, bytes_len);
    return add(vec);
  }

  ScriptBuilder push(std::vector<unsigned char> data) {
    if (data.empty()) {
      throw "NullPointerException";
    }
    if (data.size() <= (int)getByte(ScriptOp::OP_PUSHBYTES75)) {
      uc_vec.push_back((unsigned char)data.size());
      add(data);
    } else if (data.size() < 0x100) {
      add(ScriptOp::OP_PUSHDATA1);
      push((long long)data.size(), 1);
      long2bytes((long long)data.size(), 2);
      add(data);
    } else if (data.size() < 0x10000) {
      add(ScriptOp::OP_PUSHDATA2);
      push((long long)data.size(), 2);
      add(data);
    } else if (data.size() < 0x10000000) {
      add(ScriptOp::OP_PUSHDATA4);
      push((long long)data.size(), 4);
      add(data);
    } else {
      throw "IllegalArgumentException";
    }
  }

  ScriptBuilder push(BIGNUM *bn) {
    BIGNUM *num = BN_new();
    if (BN_is_word(bn, -1)) {
      return add(ScriptOp::OP_1NEGATE);
    }
    if (BN_is_zero(bn)) {
      return add(ScriptOP::OP_0);
    }
    if (!BN_set_word(bn, 16)) {
      throw "BN_set_word: error!";
    }
    if (BN_cmp(bn, BN_zero) == 1 && BN_cmp(num, bn) == 1) {
      return add(ScriptOp::OP_1 - 1 + BN_get_word(bn));
    }
    if (BN_get_word(bn) < 0 ||
        BN_get_word(bn) > std::numeric_limits<long long>::max()) {
      throw "IllegalArgumentException";
    }
  }

  ScriptBuilder pushNum(short num) {
    if (num == 0) {
      return add(ScriptOp.OP_0);
    } else if (num < 16) {
      return add(ScriptOp.valueOf(num - 1 + ScriptOp::OP_1.getByte()));
    }
  }
};

#endif