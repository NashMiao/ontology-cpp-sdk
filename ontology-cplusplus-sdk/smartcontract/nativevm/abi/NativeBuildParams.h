#ifndef NATIVEBUILDPARAMS_H
#define NATIVEBUILDPARAMS_H

#include "../../../common/Address.h"
#include "../../../core/scripts/ScriptOp.h"
#include "Struct.h"
#include <boost/any.hpp>
#include <list>
#include <openssl/bn.h>
#include <string>
#include <typeinfo>
#include <vector>

class NativeBuildParams {
public:
  std::vector<unsigned char>
  createCodeParamsScript(std::list<boost::any> list) {
    std::list<boost::any>::reverse_iterator rit;
    std::vector<unsigned char> ret_uc_vec;
    for (rit = list.rbegin(); rit != list.rend(); ++rit) {
      boost::any val = *rit;
      if (val.type() == typeid(bool)) {
        ret_uc_vec.push_back(boost::any_cast<bool>(val));
      } else if (val.type() == typeid(int)) {
        ret_uc_vec.push_back(boost::any_cast<int>(val));
      } else if (val.type() == typeid(long long)) {
        ret_uc_vec.push_back(boost::any_cast<long long>(val));
      } else if (val.type() == typeid(std::string)) {
        ret_uc_vec.push_back(boost::any_cast<std::string>(val));
      } else if (val.type() == typeid(Address)) {
        ret_uc_vec.push_back(boost::any_cast<Address>(val));
      } else if (val.type() == typeid(BIGNUM)) {
        ret_uc_vec.push_back(boost::any_cast<BIGNUM>(val));
      } else if (val.type() == typeid(Struct)) {
        ret_uc_vec.push_back(getByte(ScriptOp::OP_NEWSTRUCT));
        ret_uc_vec.push_back(getByte(ScriptOp::OP_TOALTSTACK));
      }
      else
      {
        throw "createCodeParamsScript: TypeError!";
      }
    }
  }
};

#endif