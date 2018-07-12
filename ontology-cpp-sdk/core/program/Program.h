#ifndef PROGRAM_H
#define PROGRAM_H

#if __cplusplus < 201103L
    #error "use --std=c++11 option for compile."
#endif

#include <algorithm>
#include <string>
#include <vector>

#include <openssl/ec.h>

#include "../../common/Address.h"
#include "../../common/Common.h"
#include "../../common/Helper.h"
#include "../../core/scripts/ScriptBuilder.h"
#include "../../crypto/Curve.h"
#include "../../crypto/ECC.h"
#include "../../crypto/ECDomainParameters.h"
#include "../../crypto/KeyType.h"
#include "../../sdk/exception/SDKException.h"

class Program {
public:
  static std::vector<unsigned char>
  ProgramFromParams(std::vector<std::string> &sigData) {
    ScriptBuilder builder;
    std::sort(
        sigData.begin(), sigData.end(),
        [](std::string &o1, std::string &o2) -> int { return o1.compare(o2); });
    size_t sz = sigData.size();
    for (size_t i = 0; i < sz; i++) {
      std::vector<unsigned char> vec_data(sigData[i].begin(), sigData[i].end());
      builder.push(vec_data);
    }
    return builder.toArray();
  }

  static std::vector<unsigned char>
  ProgramFromPubKey(const std::string &publicKey) {
    std::vector<unsigned char> vec_pubkey(publicKey.begin(), publicKey.end());
    ScriptBuilder builder;
    builder.push(vec_pubkey);
    builder.add(ScriptOp::OP_CHECKSIG);
    cout << "!!!!\n" << Helper::toHexString(builder.toArray()) << endl;

    return builder.toArray();
  }

  static void sortPublicKeys(std::vector<std::string> &publicKeys) {
    std::sort(publicKeys.begin(), publicKeys.end(), [](std::string &o1,
                                                       std::string &o2) -> int {
      int o1_label = KeyTypeMethod::getLabel(KeyTypeMethod::fromPubkey(o1));
      int o2_label = KeyTypeMethod::getLabel(KeyTypeMethod::fromPubkey(o2));
      if (o1_label != o2_label) {
        return (o1_label > o2_label ? 1 : -1);
      }
      ECC ecc;
      int result;
      switch (KeyTypeMethod::fromPubkey(o1)) {
      case KeyType::SM2:
        // TODO
        result = o1.compare(o2);
        break;
      case KeyType::ECDSA:
        EC_POINT *o1_ec_point;
        o1_ec_point = ecc.secp256r1->convert_EC_Point(o1);
        EC_POINT *o2_ec_point;
        o2_ec_point = ecc.secp256r1->convert_EC_Point(o2);
        result = ecc.secp256r1->compare(o1_ec_point, o2_ec_point);
        break;
      case KeyType::EDDSA:
        // TODO
        break;
      default:
        result = o1.compare(o2);
        break;
      }
      return result;
    });
  }

  static std::vector<unsigned char>
  ProgramFromMultiPubKey(int m, std::vector<std::string> &publicKeys) {
    int n = (int)publicKeys.size();
    if (m <= 0 || m > n || n > Common::MULTI_SIG_MAX_PUBKEY_SIZE) {
      throw new SDKException(ErrorCode::ParamError);
    }
    ScriptBuilder builder;
    builder.push(m);
    sortPublicKeys(publicKeys);
    for (int i = 0; i < n; i++) {
      builder.pushHexStr(publicKeys[i]);
    }
    BIGNUM *bn = BN_new();
    BN_set_word(bn, (unsigned long)n);
    builder.push(bn);
    BN_clear(bn);
    builder.add(ScriptOp::OP_CHECKMULTISIG);
    return builder.toArray();
  }
};

#endif