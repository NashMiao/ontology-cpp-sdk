#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>

#include <openssl/kdf.h>
#include <openssl/evp.h>

class Scrypt
{
  private:
    int N = 16384;
    int R = 8;
    int P = 8;
    int DkLen = 64;
    std::string Salt;

  public:
    Scrypt() {}
    Scrypt(int n, int r, int p) : N(n), R(r), P(p) {}

    void setDkLen(int dkLen)
    {
        DkLen = dkLen;
    }

    int getDkLen()
    {
        return DkLen;
    }

    void setN(int n)
    {
        N = n;
    }

    int getN()
    {
        return N;
    }

    void setR(int r)
    {
        R = r;
    }

    int getR()
    {
        return R;
    }

    void setP(int p)
    {
        P = p;
    }

    int getP()
    {
        return P;
    }

    std::string scrypt(const std::string &passphrase)
    {
        EVP_PKEY_CTX *pctx;
        unsigned char derivedkey[DkLen];

        size_t outlen = sizeof(derivedkey);
        pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_SCRYPT, NULL);

        if (EVP_PKEY_derive_init(pctx) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set1_pbe_pass(pctx, passphrase.c_str(),
                                       passphrase.length()) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set1_scrypt_salt(pctx, salt, salt_len) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set_scrypt_N(pctx, N) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set_scrypt_r(pctx, r) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_CTX_set_scrypt_p(pctx, p) <= 0)
        {
            return NULL;
        }
        if (EVP_PKEY_derive(pctx, derivedkey, &outlen) <= 0)
        {
            return NULL;
        }

        std::string hex_derivedkey;
        hex_derivedkey = hexStr(derivedkey, outlen);
        cout << hex_derivedkey << endl
             << hex_derivedkey.length() << endl;
        if (hex_derivedkey.empty())
        {
            return NULL;
        }
    }
};