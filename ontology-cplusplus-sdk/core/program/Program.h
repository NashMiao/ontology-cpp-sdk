#ifndef PROGRAM_H
#define PROGRAM_H

#include <algorithm>
#include <string>
#include <vector>

#include <openssl/ec.h>

#include "../../common/Address.h"
#include "../../common/Common.h"
#include "../../common/Helper.h"
#include "../../core/program/Program.h"
#include "../../core/scripts/ScriptBuilder.h"
#include "../../crypto/Curve.h"
#include "../../crypto/ECC.h"
#include "../../crypto/ECDomainParameters.h"
#include "../../crypto/KeyType.h"
#include "../../sdk/exception/SDKException.h"

class Program
{
  public:
    static void sortPublicKeys(const std::vector<std::string> &publicKeys)
    {
        std::sort(publicKeys.begin(), publicKeys.end(),
                  [](std::string o1, std::string o2) -> int {
                      ECC ecc;
                      int o1_label = getLabel(keyTypeFromPubkey(o1));
                      int o2_label = getLabel(keyTypeFromPubkey(o2));
                      if (o1_label != o2_label)
                      {
                          return (o1_label > o2_label ? 1 : -1);
                      }
                      int result;
                      switch (keyTypeFromPubkey(o1))
                      {
                      case KeyType::SM2:
                          // TODO
                          result = o1.compare(o2);
                          break;
                      case KeyType::ECDSA:
                          EC_POINT *o1_ec_point;
                          o1_ec_point = ecc.secp256r1.get_EC_Point(o1);
                          EC_POINT *o2_ec_point;
                          o2_ec_point = ecc.secp256r1.get_EC_Point(o2);
                          result = ecc.secp256r1.compare(o1, o2);
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
    ProgramFromMultiPubKey(int m, const std::vector<std::string> &publicKeys)
    {
        int n = publicKeys.size();
        if (m <= 0 || m > n || n > Common::MULTI_SIG_MAX_PUBKEY_SIZE)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        ScriptBuilder builder;
        builder.push(m);
        sortPublicKeys(publicKeys);
        for (size_t i = 0; i < publicKeys.size(); i++)
        {
            builder.pushHexStr(publicKeys[i]);
        }
        BIGNUM *bn = BN_new();
        BN_set_word(bn, (unsigned long)publicKeys.size());
        builder.push(bn);
        BN_clear(bn);
        builder.add(ScriptOp::OP_CHECKMULTISIG);
        return builder.toArray();
    }
};

#endif