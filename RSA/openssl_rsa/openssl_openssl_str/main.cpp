#include "rsa.h"

int main() {
  string n_s, e_s, d_s;
  Rsa my_rsa;
  my_rsa.KeyGen();
  const string one = "hello world!";
  cout << "one: " << one << endl;
  string key_str;

  my_rsa.Key2Str(my_rsa.GetPriKey(), key_str);
  cout << "Generate Private Key:\n" << key_str << endl;
  my_rsa.Key2Str(my_rsa.GetPubKey(), key_str);
  cout << "Generate Public Key:\n" << key_str << endl;

  string two;
  bool EnRet;
  EnRet = my_rsa.RsaPubKeyEnc(one, two);
  cout << "my_rsa.RsaPubKeyEnc(one, two):\n" << EnRet << endl;
  cout << "two: " << two << endl;

  string three;
  bool DeRet;
  DeRet = my_rsa.RsaPriKeyDec(two, three);
  cout << "my_rsa.RsaPriKeyDec(two, three):\n" << DeRet << endl;
  cout << "three: " << three << endl;

  string sign_digest;
  bool veri_ret;
  unsigned int siglen;
  veri_ret = my_rsa.RsaSign(one, sign_digest, siglen);
  cout << "my_rsa.RsaSign(one, sign_digest):\n"
       << veri_ret << endl
       << sign_digest << endl;
  veri_ret = my_rsa.RsaVeri(one, sign_digest, siglen);
  cout << "veri_ret1: " << veri_ret << endl;
  veri_ret = my_rsa.RsaVeri(one, "sign_digest", siglen);
  cout << "veri_ret2: " << veri_ret << endl;
  return 0;
}
