#ifndef CRYPTO_SCRYPTPARAM_H
#define CRYPTO_SCRYPTPARAM_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>

#include <nlohmann/json.hpp>

class ScryptParam
{
  private:
    int N;
    int R;
    int P;
    int DkLen;
    std::string Salt;

  public:
    explicit ScryptParam() : N(16384), R(8), P(8), DkLen(64) {}
    explicit ScryptParam(int n, int r, int p) : N(n), R(r), P(p) {}
    explicit ScryptParam(int n, int r, int p, const std::string &salt)
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