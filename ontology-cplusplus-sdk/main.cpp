// g++ main.cpp crypto/Sign.cpp `pkg-config --cflags --libs openssl` -o main &&
// ./main
#include "crypto/Sign.h"

int main() {
  Sign ec_sign;
  bool ret;

  std::string private_key =
      "01";
  std::string public_key =
      "036e01e13fdc24f79387a54c807d0b161603509ddedcc361170f4b12df90d92255";
  CurveName curve_name = p256;
  std::string out_public_key;
  ec_sign.EC_get_pubkey_by_prikey(private_key, out_public_key, curve_name);

  ec_sign.EC_set_private_key(private_key, curve_name);
  ec_sign.EC_set_public_key(out_public_key, curve_name);

  cout << "private_key:\n" << private_key << endl;
  cout << "out_public_key:\n" << out_public_key << endl;
  cout << "public_key:\n" << public_key << endl;

  //   ret = ec_sign.EC_set_private_key(private_key, curve_name);
  //   cout << ret << endl;
  //   ec_sign.EC_set_public_key(public_key, curve_name);
  //   cout << ret << endl;

  ret = ec_sign.ECDSA_key_generate();
  std::string msg = "Hello world!";
  std::string str_sign_dgst;
  ec_sign.EC_sign(msg, str_sign_dgst);
  cout << "msg:" << msg << endl << "str_sig_dgst:" << str_sign_dgst << endl;
  ret = ec_sign.EC_veri(msg, str_sign_dgst);
  cout << "ret: " << ret << endl;
  return 0;
}