#ifndef KEYTYPE_H
#define KEYTYPE_H

#include "../common/ErrorCode.h"

#include <exception>
#include <ostream>
#include <vector>

enum class KeyType
{
    ECDSA = 0x12,
    SM2 = 0x13,
    EDDSA = 0x14
};

// get the crypto.KeyType according to the input label
static KeyType fromLabel(int label)
{
    KeyType type;
    switch (label)
    {
    case 0x12:
        type = KeyType::ECDSA;
        break;
    case 0x13:
        type = KeyType::SM2;
        break;
    case 0x14:
        type = KeyType::EDDSA;
        break;
    default:
        throw new std::invalid_argument(ErrorCode.UnknownAsymmetricKeyType.dump());
    }
    return type;
}

// get the crypto.KeyType according to the input label
static KeyType fromLabel(unsigned char label)
{
    return fromLabel((int)label);
}

static KeyType fromPubkey(std::vector<unsigned char> pubkey)
{
    KeyType type;
    if (pubkey.size() == 33)
    {
        type = KeyType::ECDSA;
    }
    else
    {
        try
        {
            type = fromLabel(pubkey[0]);
        }
        catch(std::invalid_argument &ia){
            type = NULL;
            std::cerr << ia.what() << std::endl;
        }
    }
    return type;
}

#endif