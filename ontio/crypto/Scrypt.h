#ifndef SCRYPT_H
#define SCRYPT_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <stdexcept>
#include <string>

#include <openssl/evp.h>
#include <openssl/kdf.h>

#include "../common/ErrorCode.h"
#include "../common/Helper.h"
#include "../sdk/exception/SDKException.h"

class Scrypt
{
  private:
    int N;
    int R;
    int P;
    int DkLen;
    std::string Salt;

  public:
    explicit Scrypt() : N(16384), R(8), P(8), DkLen(64) {}
    explicit Scrypt(int n, int r, int p) : N(n), R(r), P(p) {}
    explicit Scrypt(int n, int r, int p, const std::string &salt)
        : N(n), R(r), P(p), Salt(salt) {}

    void setDkLen(int dkLen) { DkLen = dkLen; }

    int getDkLen() { return DkLen; }

    void setN(int n) { N = n; }

    int getN() { return N; }

    void setR(int r) { R = r; }

    int getR() { return R; }

    void setP(int p) { P = p; }

    int getP() { return P; }

    void setSalt(const std::string &salt) { Salt = salt; }

    std::string getSalt() { return Salt; }

    std::string scrypt(const std::string &passphrase, const std::string &salt)
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

    std::string toString()
    {
        nlohmann::json j;
        j["n"] = N;
        j["r"] = R;
        j["p"] = P;
        j["DkLen"] = DkLen;
        j["Salt"] = Salt;
        return j.dump();
    }
};
#endif