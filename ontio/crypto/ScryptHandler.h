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
    static std::string scrypt(const std::string &passphrase, const std::string &salt)
    {
        EVP_PKEY_CTX *pctx;
        unsigned char derivedkey[DkLen];

        size_t outlen = sizeof(derivedkey);
        pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_SCRYPT, NULL);

        if (EVP_PKEY_derive_init(pctx) <= 0)
        {
            throw new SDKException(ErrorCode::ParamError);
        }
        if (EVP_PKEY_CTX_set1_pbe_pass(pctx, passphrase.c_str(),
                                       passphrase.length()) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set1_scrypt_salt(pctx, salt.c_str(), (int)salt.length()) <=
            0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set_scrypt_N(pctx, N) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set_scrypt_r(pctx, R) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set_scrypt_p(pctx, P) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_derive(pctx, derivedkey, &outlen) <= 0)
        {
            return NULL;
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