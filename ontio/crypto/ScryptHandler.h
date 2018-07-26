#ifndef CRYPTO_SCRYPTHANDLER_H
#define CRYPTO_SCRYPTHANDLER_H

#include <stdexcept>
#include <string>

#include <openssl/evp.h>
#include <openssl/kdf.h>

#include "../common/ErrorCode.h"
#include "../common/Helper.h"
#include "../sdk/exception/SDKException.h"

class ScryptHandler
{
    // Derive one key from a password.

    // This function performs key derivation according to
    // the `scrypt`_ algorithm, introduced in Percival's paper
    // `"Stronger key derivation via sequential memory-hard functions"`__.

    // Args:
    // password (string):
    //     The secret pass phrase to generate the keys from.
    // salt (string):
    //     A string to use for better protection from dictionary attacks.
    //     This value does not need to be kept secret,
    //     but it should be randomly chosen for each derivation.
    //     It is recommended to be at least 8 bytes long.
    // n (integer):
    //     CPU/Memory cost parameter. It must be a power of 2 and less
    //     than :math:`2^{32}`.
    // r (integer):
    //     Block size parameter.
    // p (integer):
    //     Parallelization parameter.
    //     It must be no greater than :math:`(2^{32}-1)/(4r)`.
    // dkLen (integer):
    //     The length in bytes of every derived key.

    // A good choice of parameters *(n, r , p)* was suggested
    // by Colin Percival in his `presentation in 2009`__:

    // - *(16384, 8, 1)* for interactive logins (<=100ms)
    // - *(1048576, 8, 1)* for file encryption (<=5s)

    // Return:
    //     A hexadecimal string.
    static std::string scrypt(const std::string &password, const std::string &salt,
                              int n = 16384, int r = 8, int p = 8, int dkLen = 64)
    {
        EVP_PKEY_CTX *pctx;
        unsigned char derivedkey[dkLen];

        size_t outlen = sizeof(derivedkey);
        pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_SCRYPT, NULL);

        if (EVP_PKEY_derive_init(pctx) <= 0)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        if (EVP_PKEY_CTX_set1_pbe_pass(pctx, password.c_str(), password.length()) <=
            0)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        if (EVP_PKEY_CTX_set1_scrypt_salt(pctx, salt.c_str(), (int)salt.length()) <=
            0)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        if (EVP_PKEY_CTX_set_scrypt_N(pctx, n) <= 0)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        if (EVP_PKEY_CTX_set_scrypt_r(pctx, r) <= 0)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        if (EVP_PKEY_CTX_set_scrypt_p(pctx, p) <= 0)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        if (EVP_PKEY_derive(pctx, derivedkey, &outlen) <= 0)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        std::string hex_derivedkey = Helper::toHexString(derivedkey, outlen);
        if (hex_derivedkey.empty())
        {
            throw std::runtime_error("scrypt failed.");
        }
        return hex_derivedkey;
    }
};
#endif