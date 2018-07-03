#ifndef PROGRAM_H
#define PROGRAM_H

#include "../../common/Address.h"
#include "../../core/scripts/ScriptBuilder.h"
#include "../../sdk/exception/SDKException.h"

#include <vector>

class Program
{
  public:
    static std::vector<unsigned char> sortPublicKeys(const std::vector<unsigned char> &publicKeys)
    {
        
    }

    static std::vector<unsigned char> ProgramFromMultiPubKey(int m, const std::vector<unsigned char> &publicKeys)
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