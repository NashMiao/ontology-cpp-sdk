#ifndef RSA_H
#define RSA_H

#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;

struct RSA_Pub {
  ZZ e, N;
};

struct RSA_Pri {
  ZZ d, N;
};

class RSA {
private:
  RSA_Pub Pub;
  RSA_Pri Pri;

public:
  // RSA();
  // ~RSA();
  // gen Pub and Pri
  void KeyGen(long l);
  ZZ EncryptByPub(const ZZ &msg);
  ZZ DecryptByPri(const ZZ &cip);

  ZZ Sign(const ZZ &msg);
  bool Veri(const ZZ &msg, const ZZ &sign_msg);
};

#endif
