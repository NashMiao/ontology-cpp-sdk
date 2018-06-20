#ifndef NATIVEBUILDPARAMS_H
#define NATIVEBUILDPARAMS_H

#include "../../../common/Address.h"
#include "../../../core/scripts/ScriptOp.h"
#include "../../../io/BinaryWriter.h"
#include "Struct.h"
#include <boost/any.hpp>
#include <list>
#include <openssl/bn.h>
#include <string>
#include <typeinfo>
#include <vector>

class NativeBuildParams {
private:
  static std::vector<unsigned char>
  createCodeParamsScript(ScriptBuilder &builder, boost::any &obj) {
    try {
      boost::any val = obj;
      if (val.type == typeid(std::vector<unsigned char>)) {
        builder.push(val);
      } else if (val.type() == typeid(bool)) {
        bool value = boost::any_cast<bool>(val);
        builder.push(value);
      } else if (val.type() == typeid(int)) {
        int value = boost::any_cast<int>(val);
        builder.push(value);
      } else if (val.type() == typeid(long long)) {
        long long value = boost::any_cast<long long>(val);
        builder.push(value);
      } else if (val.type() == typeid(std::string)) {
        std::string value = boost::any_cast<std::string>(val);
        builder.push(value);
      } else if (val.type() == typeid(Address)) {
        Address value = boost::any_cast<Address>(val);
        builder.push(value.toArray());
      } else if (val.type() == typeid(BIGNUM)) {
        BIGNUM value = boost::any_cast<BIGNUM>(val);
        builder.push((long long)BN_get_word(value));
      } else if (val.type() == typeid(Struct)) {
        Struct value = boost::any_cast<Struct>(val);
        std::list<boost::any> value_list = value.getList();
        for (size_t i = 0; i < value_list.size(); i++) {
          boost::any o = value_list[i];
          createCodeParamsScript(builder, o);
          builder.add(ScriptOp::OP_DUPFROMALTSTACK);
          builder.add(ScriptOp::OP_SWAP);
          builder.add(ScriptOp::OP_APPEND);
        }
      } else {
        throw "SDKException(ErrorCode.OtherError(not this type))";
      }
    } catch (const char *err) {
      cerr << err << endl;
    }
    return builder.toArray();
  }

  static std::vector<unsigned char>
  createCodeParamsScript(ScriptBuilder &builder,
                         std::list<boost::any> &any_list) {
    std::list<boost::any>::reverse_iterator rit;
    for (rit = list.rbegin(); rit != list.rend(); ++rit) {
      boost::any val = *rit;
      if (val.type == typeid(std::vector<unsigned char>)) {
        builder.push(val);
      } else if (val.type() == typeid(bool)) {
        bool value = boost::any_cast<bool>(val);
        builder.push(value);
      } else if (val.type() == typeid(int)) {
        int value = boost::any_cast<int>(val);
        builder.push(value);
      } else if (val.type() == typeid(long long)) {
        long long value = boost::any_cast<long long>(val);
        builder.push(value);
      } else if (val.type() == typeid(std::string)) {
        std::string value = boost::any_cast<std::string>(val);
        builder.push(value);
      } else if (val.type() == typeid(Address)) {
        Address value = boost::any_cast<Address>(val);
        builder.push(value.toArray());
      } else if (val.type() == typeid(BIGNUM)) {
        BIGNUM value = boost::any_cast<BIGNUM>(val);
        builder.push((long long)BN_get_word(value));
      } else if (val.type() == typeid(std::list<boost::any>)) {
        std::list<boost::any> list_value = val;
        createCodeParamsScript(builder, list_value);
        builder.push((long long)struct_vec.size());
        builder.pushPack();
      } else {
        throw "SDKException(ErrorCode.OtherError(not this type)";
      }
    }
  }

public:
  static std::vector<unsigned char>
  createCodeParamsScript(std::list<boost::any> list) {
    ScriptBuilder builder;
    std::list<boost::any>::reverse_iterator rit;
    for (rit = list.rbegin(); rit != list.rend(); ++rit) {
      boost::any val = *rit;
      if (val.type == typeid(std::vector<unsigned char>)) {
        builder.push(val);
      } else if (val.type() == typeid(bool)) {
        bool value = boost::any_cast<bool>(val);
        builder.push(value);
      } else if (val.type() == typeid(int)) {
        int value = boost::any_cast<int>(val);
        builder.push(value);
      } else if (val.type() == typeid(long long)) {
        long long value = boost::any_cast<long long>(val);
        builder.push(value);
      } else if (val.type() == typeid(std::string)) {
        std::string value = boost::any_cast<std::string>(val);
        builder.push(value);
      } else if (val.type() == typeid(Address)) {
        Address value = boost::any_cast<Address>(val);
        builder.push(value.toArray());
      } else if (val.type() == typeid(BIGNUM)) {
        BIGNUM value = boost::any_cast<BIGNUM>(val);
        builder.push((long long)BN_get_word(value));
      } else if (val.type() == typeid(Struct)) {
        builder.push((long long)0);
        builder.add(getByte(ScriptOp::OP_NEWSTRUCT));
        builder.add(getByte(ScriptOp::OP_TOALTSTACK));
        Struct value = boost::any_cast<Struct>(val);
        std::list<boost::any> value_list = value.getList();
        for (size_t i = 0; i < value_list.size(); i++) {
          boost::any o = value_list[i];
          createCodeParamsScript(builder, o);
          builder.add(getByte(ScriptOp::OP_DUPFROMALTSTACK));
          builder.add(getByte(ScriptOp::OP_SWAP));
          builder.add(getByte(ScriptOp::OP_APPEND));
        }
        builder.add(getByte(ScriptOp::OP_FROMALTSTACK));
      } else if (val.type() == typeid(std::vector<Struct>)) {
        builder.push((long long)0);
        builder.add(getByte(ScriptOp::OP_NEWSTRUCT));
        builder.add(getByte(ScriptOp::OP_TOALTSTACK));
        std::vector<Struct> struct_vec;
        struct_vec = boost::any_cast<std::vector<Struct>>(val);
        for (size_t i = 0; i < struct_vec.size(); i++) {
          createCodeParamsScript(builder, struct_vec[i]);
        }
        builder.add(ScriptOp::OP_FROMALTSTACK);
        builder.push((long long)struct_vec.size());
        builder.pushPack();
      } else if (val.type() == typeid(std::list<boost::any>)) {
        std::list<boost::any> list_value = val;
        createCodeParamsScript(builder, list_value);
        builder.push((long long)struct_vec.size());
        builder.pushPack();
      } else {
        throw "createCodeParamsScript: TypeError!";
      }
    }
  }
};

#endif