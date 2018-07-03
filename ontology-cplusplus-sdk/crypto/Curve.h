#ifndef CURVE_H
#define CURVE_H

#include <openssl/evp.h>
#include <openssl/obj_mac.h> // for NID_secp192k1

#include <string>

enum class CurveName : int
{
    p224 = NID_secp224k1,
    p256 = NID_X9_62_prime256v1, // ANSI X9.62 Prime 256v1 curve
    p384 = NID_secp384r1,
    p521 = NID_secp521r1,
    SM2P256V1 = NID_sm2,
    ED25519 = NID_ED25519
};

int getLabel(CurveName curve)
{
    int label;
    switch (curve)
    {
    case p224:
        label = 1;
        break;
    case p256:
        label = 2;
        break;
    case p384:
        label = 3;
        break;
    case p521:
        label = 4;
        break;
    case SM2P256V1:
        label = 20;
        break;
    case ED25519:
        label = 25;
        break;
    default:
        throw "getLabel: unknown type";
    }
    return label;
}

std::string toString()
{
    std::string name;
    switch (curve)
    {
    case p224:
        name = "P-224";
        break;
    case p256:
        name = "P-256";
        break;
    case p384:
        label = "P-384";
        break;
    case p521:
        name = "P-521";
        break;
    case SM2P256V1:
        name = "sm2p256v1";
        break;
    case ED25519:
        name = "ED25519";
        break;
    default:
        throw "getLabel: unknown type";
    }
    return name;
}

#endif