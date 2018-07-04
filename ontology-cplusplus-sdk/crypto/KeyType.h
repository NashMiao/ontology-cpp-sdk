#ifndef KEYTYPE_H
#define KEYTYPE_H

#include "../common/ErrorCode.h"

#include <exception>
#include <ostream>
#include <vector>

enum class KeyType : int
{
    ECDSA = 0x12,
    SM2 = 0x13,
    EDDSA = 0x14
};

// get the crypto.KeyType according to the input label
static KeyType keyTypeFromLabel(int label)
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
static KeyType keyTypeFromLabel(unsigned char label)
{
    return keyTypeFromLabel((int)label);
}

static KeyType keyTypeFromPubkey(const std::vector<unsigned char> &pubkey)
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
            type = keyTypeFromLabel(pubkey[0]);
        }
        catch (std::invalid_argument &ia)
        {
            type = NULL;
            std::cerr << ia.what() << std::endl;
        }
    }
    return type;
}

static KeyType keyTypeFromPubkey(const std::string &pubkey){
    std::vector<unsigned char> vec_pubkey(pubkey.begin(), pubkey.end());
    return keyTypeFromPubkey(vec_pubkey);
}

    static int getLabel(KeyType type)
{
    int label;
    switch (type)
    {
    case KeyType::ECDSA:
        label = 0x12;
    case KeyType::SM2:
        label = 0x13;
    case KeyType::EDDSA:
        label = 0x14;
        break;
    default:
        break;
    }
}

#endif