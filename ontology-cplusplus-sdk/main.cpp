// g++ main.cpp crypto/Sign.cpp `pkg-config --cflags --libs openssl` -o main &&
// ./main
#include "crypto/Sign.h"

void sign_by_set_pub_pri() {
  Sign ec_sign;
  ec_sign.EC_init();
  CurveName curve_name = p256;
  std::string private_key =
      "70789d4ac31576c61c5d12e38a66de605b18faf2c8d60a2c1952a6286b67318f";
  std::string public_key =
      "036e01e13fdc24f79387a54c807d0b161603509ddedcc361170f4b12df90d92255";
  ec_sign.EC_set_key(public_key, private_key, curve_name);
  cout << "private_key:\n"
       << private_key << endl
       << "public_key:\n"
       << public_key << endl;
  std::string out_public_key;
  std::string out_private_key;
  ec_sign.EC_get_private_key(out_private_key);
  ec_sign.EC_get_public_key(out_public_key);
  cout << "out_private_key:\n"
       << out_private_key << endl
       << "out_public_key:\n"
       << out_public_key << endl;

  bool ret;
  std::string msg = "Hello world!";
  std::string str_sign_dgst;
  ec_sign.EC_sign(msg, str_sign_dgst);
  cout << "msg:\n" << msg << endl << "str_sig_dgst:\n" << str_sign_dgst << endl;
  ret = ec_sign.EC_veri(msg, str_sign_dgst);
  cout << "ret: " << ret << endl;
}

void sign_by_gen_key() {
  Sign ec_sign;
  ec_sign.EC_init();
  ec_sign.ECDSA_key_generate();
  std::string out_public_key;
  std::string out_private_key;
  ec_sign.EC_get_private_key(out_private_key);
  ec_sign.EC_get_public_key(out_public_key);
  cout << "out_private_key:\n"
       << out_private_key << endl
       << "out_public_key:\n"
       << out_public_key << endl;

  std::string msg = "Hello world!";
  std::string str_sign_dgst;
  ec_sign.EC_sign(msg, str_sign_dgst);
  cout << "msg:\n" << msg << endl << "str_sig_dgst:\n" << str_sign_dgst << endl;
  bool ret;
  ret = ec_sign.EC_veri(msg, str_sign_dgst);
  cout << "ret: " << ret << endl;
}

void sign_by_pri_key() {
  Sign ec_sign;
  CurveName curve_name = p256;
  ec_sign.EC_init();
  std::string private_key =
      "70789d4ac31576c61c5d12e38a66de605b18faf2c8d60a2c1952a6286b67318f";
  std::string public_key = "";
  ec_sign.EC_get_pubkey_by_prikey(private_key, public_key, curve_name);
  ec_sign.EC_set_key(public_key, private_key, curve_name);
  cout << "private_key:\n"
       << private_key << endl
       << "public_key:\n"
       << public_key << endl;
  std::string out_public_key;
  std::string out_private_key;
  ec_sign.EC_get_private_key(out_private_key);
  ec_sign.EC_get_public_key(out_public_key);
  cout << "out_private_key:\n"
       << out_private_key << endl
       << "out_public_key:\n"
       << out_public_key << endl;

  bool ret;
  std::string msg = "Hello world!";
  std::string str_sign_dgst;
  ec_sign.EC_sign(msg, str_sign_dgst);
  cout << "msg:\n" << msg << endl << "str_sig_dgst:\n" << str_sign_dgst << endl;
  ret = ec_sign.EC_veri(msg, str_sign_dgst);
  cout << "ret: " << ret << endl;
}

int main() {
  sign_by_pri_key();
  sign_by_set_pub_pri();
  sign_by_gen_key();
  return 0;
}