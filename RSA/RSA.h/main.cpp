#include "RSA.h"

int main() {
  RSA rsa;
  long l;
  cin >> l;
  rsa.KeyGen(l);
  ZZ msg;
  cin >> msg;
  ZZ cip = rsa.EncryptByPub(msg);
  cout << "cip: " << cip << endl;
  ZZ out_msg = rsa.DecryptByPri(cip);
  cout << "out_msg: " << out_msg << endl;
}
