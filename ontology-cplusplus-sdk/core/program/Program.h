#ifndef PROGRAM_H
#define PROGRAM_H

#include <algorithm>
#include <string>
#include <vector>

#include <openssl/ec.h>

#include "../../common/Address.h"
#include "../../core/program/Program.h"
#include "../../core/scripts/ScriptBuilder.h"
#include "../../crypto/Curve.h"
#include "../../crypto/ECC.h"
#include "../../crypto/KeyType.h"
#include "../../sdk/exception/SDKException.h"

class Program
{
  public:
    static std::vector<unsigned char>
    sortPublicKeys(const std::vector<std::string> &publicKeys)
    {
        std::sort(publicKeys.begin(), publicKeys.end(),
                  [](std::string o1, std::string o2) -> int {
                      int result;
                      switch (keyTypeFromPubkey(o1))
                      {
                      case KeyType::SM2:
                          // TODO
                          break;
                      case KeyType::ECDSA:
                          EC_POINT *o1_ec_point;
                          o1_ec_point = ECC::secp256r1.get_EC_Point(o1);
                          EC_POINT *o2_ec_point;
                          o2_ec_point = ECC::secp256r1.get_EC_Point(o2);
                          result = ECC::secp256r1.compare(o1, o2);
                          break;
                      case KeyType::EDDSA:
                          // TODO
                          break;
                      default:
                          break;
                      }
                      return result;
                  })
    }

    static std::vector<unsigned char>
    ProgramFromMultiPubKey(int m, const std::vector<unsigned char> &publicKeys)
    {
        int n = publicKeys.size();
        if (m <= 0 || m > n || n > Common::AddressMULTI_SIG_MAX_PUBKEY_SIZE)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        ScriptBuilder builder;
        builder.push(m);
    }
};

#endif