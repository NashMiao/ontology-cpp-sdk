// g++ main.cpp crypto/Sign.cpp crypto/AES.cpp `pkg-config --cflags --libs
// openssl` -o main &&
// ./main
#include "crypto/AES.h"
#include "crypto/Sign.h"
#include <openssl/kdf.h>
#include <vector>

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

void aes_enc_dec() {
  AES aes;
  aes.params_init();
  std::string msg = "Hello world!";
  cout << "msg:\n" << msg << endl;
  std::string enc_msg, dec_msg;
  aes.auth_encry(msg, enc_msg);
  cout << "enc_msg:\n" << enc_msg << endl;
  aes.auth_decry(enc_msg, dec_msg);
  cout << "dec_msg:\n" << dec_msg << endl;
}

std::string hexStr(unsigned char *data, int len) {
  char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                   '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}

std::string exportCtrEncryptedPrikey(std::string passphrase, int n) {
  int N = n;
  int r = 8;
  int p = 8;
  int dkLen = 64;

  int salt_len = 4;
  unsigned char salt[] = {0xfa, 0xa4, 0x88, 0x3d};

  EVP_PKEY_CTX *pctx;
  unsigned char derivedkey[dkLen];

  size_t outlen = sizeof(derivedkey);
  pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_SCRYPT, NULL);

  if (EVP_PKEY_derive_init(pctx) <= 0) {
    return NULL;
  }
  if (EVP_PKEY_CTX_set1_pbe_pass(pctx, passphrase.c_str(),
                                 passphrase.length()) <= 0) {
    return NULL;
  }
  if (EVP_PKEY_CTX_set1_scrypt_salt(pctx, salt, salt_len) <= 0) {
    return NULL;
  }
  if (EVP_PKEY_CTX_set_scrypt_N(pctx, n) <= 0) {
    return NULL;
  }
  if (EVP_PKEY_CTX_set_scrypt_r(pctx, r) <= 0) {
    return NULL;
  }
  if (EVP_PKEY_CTX_set_scrypt_p(pctx, p) <= 0) {
    return NULL;
  }
  if (EVP_PKEY_derive(pctx, derivedkey, &outlen) <= 0) {
    return NULL;
  }

  std::string str;
  str = hexStr(derivedkey, outlen);
  cout << str.length() << endl;
  cout << str << endl;
  cout << "derivedkey:\n"
       << "9f0632e05eab137baae6e0a83300341531e8638612a08042d3a4074578869af1ccf5"
          "008e434d2cae9477f9e6e4c0571ab65a60e32e8c8fc356d95f64dd9717c9"
       << endl;

  EVP_PKEY_CTX_free(pctx);
  return "test";
}

int main() {
  // sign_by_pri_key();
  // sign_by_set_pub_pri();
  // sign_by_gen_key();
  // aes_enc_dec();

  std::string passphrase = "passwordtest";
  exportCtrEncryptedPrikey(passphrase, 16384);
  return 0;
}