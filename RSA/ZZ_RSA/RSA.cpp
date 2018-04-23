#include "RSA.h"
#define NDEBUG
#include <assert.h>
#include <time.h>

void RSA::KeyGen(long l) {
  ZZ p, q, N;
  // n = random l-bit prime.  Uses ProbPrime with NumTrials.

  p = RandomPrime_ZZ(l);
  q = RandomPrime_ZZ(l);

  // test
  cout << "p: " << p << endl;
  cout << "q: " << q << endl;

  N = p * q;
  const ZZ r = (p - 1) * (q - 1);
  SetSeed(to_ZZ(time(NULL)));
  // x = pseudo-random number in the range 0..n-1, or 0 if n <= 0
  // ZZ RandomBnd(const ZZ& n);

  ZZ e = RandomBnd(r);

  if (e == 0) {
    e += 1;
  }
  // void XGCD(ZZ& d, ZZ& s, ZZ& t, const ZZ& a, const ZZ& b);
  // d = gcd(a, b) = a*s + b*t.
  ZZ x, y;
  ZZ d = to_ZZ(1);
  XGCD(d, x, y, e, r);

  // x = (a*b)%n
  // ZZ MulMod(const ZZ& a, const ZZ& b, const ZZ& n);

  if (x < 0) {
    x += r;
  }

  Pri.d = x;
  Pri.N = N;

  Pub.e = e;
  Pub.N = N;
}

ZZ RSA::EncryptByPub(const ZZ &msg) {
  // ZZ PowerMod(const ZZ &a, const ZZ &e, const ZZ &n);
  // x = a^e % n (e may be negative)
  ZZ cip = PowerMod(msg, Pub.e, Pub.N);
  return cip;
}

ZZ RSA::DecryptByPri(const ZZ &cip) {
  ZZ msg;
  msg = PowerMod(cip, Pri.d, Pri.N);
  return msg;
}

ZZ RSA::Sign(const ZZ &msg) {
  ZZ sign_msg;
  sign_msg = PowerMod(msg, Pri.d, Pri.N);
  return sign_msg;
}
bool RSA::Veri(const ZZ &msg, const ZZ &sign_msg) {
  ZZ veri_msg;
  veri_msg = PowerMod(sign_msg, Pub.e, Pub.N);
  if (veri_msg == msg) {
    return true;
  }
  return false;
}
