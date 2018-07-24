#ifndef SCRIPT_H
#define SCRIPT_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>

#include <nlohmann/json.hpp>

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
    Scrypt(int n, int r, int p) N : (n), R(r), P(p) {}
    Script operator=(const Scrypt &scpt)
    {
        this->N = scpt.N;
        this->R = scpt.R;
        this->P = scpt.P;
        this->DkLen = scpt.DkLen;
        this->Salt = scpt.Salt;
        return *this;
    }

    int getN() { return N; }

    void setN(int n) { N = n; }

    void setR(int r) { R = r; }

    int getR() { return R; }

    void setP(int p) { P = p; }

    int getP() { return p; }

    int getDKLen() { return DkLen; }
};

#endif