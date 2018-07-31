#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <map>
#include <memory>
#include <string>

#include <boost/algorithm/hex.hpp>
#include <boost/any.hpp>
#include <nlohmann/json.hpp>
#include <openssl/asn1.h>
#include <openssl/bio.h>
#include <openssl/ec.h>
#include <openssl/kdf.h>

#include "common/Helper.h"
#include "core/block/Block.h"
#include "core/transaction/Transaction.h"
#include "crypto/AES.h"
#include "crypto/Digest.h"
#include "crypto/ScryptHandler.h"
#include "crypto/Signature.h"
#include "demo/MakeTxWithoutWalletDemo.h"
#include "network/restful/Result.h"
#include "network/restful/http.h"

//std::string hexStr(unsigned char *data, int len) {
//    char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
//                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
//    std::string s(len * 2, ' ');
//    for (int i = 0; i < len; ++i) {
//        s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
//        s[2 * i + 1] = hexmap[data[i] & 0x0F];
//    }
//    return s;
//}

// void aes_enc_dec() {
//   AES aes;
//   aes.params_init();
//   cout << "iv:\n" << aes.get_iv() << endl;
//   cout << "key:\n" << aes.get_key() << endl;
//   std::string msg = "Hello world!";
//   cout << "msg:\n" << msg << endl;
//   std::string enc_msg, dec_msg;
//   aes.auth_encry(msg, enc_msg);
//   cout << "enc_msg:\n" << enc_msg << endl;
//   aes.auth_decry(enc_msg, dec_msg);
//   cout << "dec_msg:\n" << dec_msg << endl;
// }

//char *base64(const unsigned char *inputBuffer, int inputLen) {
//    EVP_ENCODE_CTX *ctx;
//    ctx = EVP_ENCODE_CTX_new();
//    int base64Len = (((inputLen + 2) / 3) * 4) + 1; // Base64 text length
//    int pemLen = base64Len + base64Len / 64; // PEM adds a newline every 64 bytes
//    char *base64 = new char[pemLen];
//    int result;
//    EVP_EncodeInit(ctx);
//    EVP_EncodeUpdate(ctx, (unsigned char *) base64, &result,
//                     (unsigned char *) inputBuffer, inputLen);
//    EVP_EncodeFinal(ctx, (unsigned char *) &base64[result], &result);
//    return base64;
//}
//
//unsigned char *unbase64(char *input, int length, int *outLen) {
//    EVP_ENCODE_CTX *ctx;
//    ctx = EVP_ENCODE_CTX_new();
//    int orgLen = (((length + 2) / 4) * 3) + 1;
//    unsigned char *orgBuf = new unsigned char[orgLen];
//    int result, tmpLen;
//    EVP_DecodeInit(ctx);
//    EVP_DecodeUpdate(ctx, (unsigned char *) orgBuf, &result,
//                     (unsigned char *) input, length);
//    EVP_DecodeFinal(ctx, (unsigned char *) &orgBuf[result], &tmpLen);
//    result += tmpLen;
//    *outLen = result;
//    return orgBuf;
//}

//std::string exportCtrEncryptedPrikey(std::string passphrase, int n) {
//  int N = n;
//  int r = 8;
//  int p = 8;
//  int dkLen = 64;
//
//  int salt_len = 4;
//  unsigned char salt[] = {0xfa, 0xa4, 0x88, 0x3d};
//
//  EVP_PKEY_CTX *pctx;
//  unsigned char derivedkey[dkLen];
//
//  size_t outlen = sizeof(derivedkey);
//  pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_SCRYPT, NULL);
//
//  if (EVP_PKEY_derive_init(pctx) <= 0) {
//    return NULL;
//  }
//  if (EVP_PKEY_CTX_set1_pbe_pass(pctx, passphrase.c_str(),
//                                 passphrase.length()) <= 0) {
//    return NULL;
//  }
//  if (EVP_PKEY_CTX_set1_scrypt_salt(pctx, salt, salt_len) <= 0) {
//    return NULL;
//  }
//  if (EVP_PKEY_CTX_set_scrypt_N(pctx, N) <= 0) {
//    return NULL;
//  }
//  if (EVP_PKEY_CTX_set_scrypt_r(pctx, r) <= 0) {
//    return NULL;
//  }
//  if (EVP_PKEY_CTX_set_scrypt_p(pctx, p) <= 0) {
//    return NULL;
//  }
//  if (EVP_PKEY_derive(pctx, derivedkey, &outlen) <= 0) {
//    return NULL;
//  }
//
//  std::string hex_derivedkey;
//  hex_derivedkey = hexStr(derivedkey, outlen);
//  cout << hex_derivedkey << endl << hex_derivedkey.length() << endl;
//  if (hex_derivedkey.empty()) {
//    return NULL;
//  }

// std::string str_derivedkey =
//     std::string(reinterpret_cast<char *>(derivedkey));
// cout << "str_derivedkey:\n"
//      << str_derivedkey << endl
//      << "outlen:" << outlen << endl
//      << str_derivedkey.length() << endl;

//  unsigned char uc_iv[AES_BLOCK_SIZE];
//  unsigned char uc_key[AES_256_KEY_SIZE];
//  memcpy(uc_iv, &derivedkey[0], AES_BLOCK_SIZE * sizeof(unsigned char));
//  memcpy(uc_key, &derivedkey[32], AES_256_KEY_SIZE * sizeof(unsigned char));
//
//  cout << "uc_iv:\n" << hexStr(uc_iv, 16) << endl << sizeof(uc_iv) << endl;
//  cout << "uc_key:\n" << hexStr(uc_key, 32) << endl << sizeof(uc_key) << endl;
//
//  AES aes;
//
//  aes.set_params(uc_key, uc_iv, AEAD_mode::AES_CTR);
//
//  unsigned char uc_private_key[] = {
//      0xc1, 0x9f, 0x16, 0x78, 0x5b, 0x8f, 0x35, 0x43, 0xbb, 0xaf, 0x5e,
//      0x1d, 0xbb, 0x5d, 0x39, 0x8d, 0xfa, 0x6c, 0x85, 0xaa, 0xad, 0x54,
//      0xfc, 0x9d, 0x71, 0x20, 0x3c, 0xe8, 0x3e, 0x50, 0x5c, 0x07};
//
//  cout << "uc_private_key:\n" << hexStr(uc_private_key, 32) << endl;

// cout << "uc_private_key:\n"
//      << uc_private_key << endl
//      << sizeof(uc_private_key) << endl;

// std::string private_key =
// std::string(reinterpret_cast<char *>(uc_private_key));
// std::string enc_private_key;

//  cout << "aes.get_iv():\n" << hexStr(aes.get_iv(), 16) << endl;
//  cout << "aes.get_key():\n" << hexStr(aes.get_key(), 32) << endl;
//
//  int enc_private_key_sz = 32;
//  unsigned char *enc_private_key = new unsigned char(enc_private_key_sz);
//  aes.auth_encry(uc_private_key, enc_private_key);
//  cout << "enc_private_key:\n" << enc_private_key << endl;
//  string str_enc_private_key;

// str_enc_private_key = hexStr(enc_private_key, 48);
// cout << "str_enc_private_key:\n" << str_enc_private_key << endl;
// cout << Base64Encode(str_enc_private_key.c_str(),
//                      str_enc_private_key.length(), false)
//      << endl;

//  cout << "base64(enc_private_key, 48):\n"
//       << base64(enc_private_key, enc_private_key_sz) << endl;
//
//  char test_key[] = "3JZLD/X45qSFjmRRvRVhcEjKgCJQDPWOsjx2dcTEj58=";
//  int o_l;
//  unsigned char *uc_tset_key = unbase64(test_key, 45, &o_l);
//
//  cout << "test_key:\n" << unbase64(test_key, 45, &o_l) << endl;
//
//  cout << hexStr(enc_private_key, 48) << endl;
//  cout << hexStr(uc_tset_key, 48) << endl;
//
//  EVP_PKEY_CTX_free(pctx);
//
//  return "test";
//}

//void bn_write_read() {

// std::ofstream outfile;
// outfile.open("outfile.txt");
// if (!outfile.is_open()) {
//   cout << "outfile.txt error!" << endl;
// }

//    BinaryWriter BW;

// BW.set_ofstream(outfile);
//    BW.writeVarInt(12345678);
//
//    std::ifstream infile;
// infile.open("infile.txt");
// if (!infile.is_open()) {
//   cout << "infile.txt error!" << endl;
// }

//    BinaryReader BR;

// BR.set_ifstream(infile);

//    long long value;
//    value = BR.readVarInt(1234567890);
//    cout << value << endl;
//}

void test_MakeTxWithoutWalletDemo()
{
    MakeTxWithoutWalletDemo make_tx_without_wallet_demo;
    make_tx_without_wallet_demo.init();
    // make_tx_without_wallet_demo.transer();
    make_tx_without_wallet_demo.queryBalanceOf();
}

int main()
{
    // test_MakeTxWithoutWalletDemo();
    std::string plaintext_1 = "Hello world!";
    std::string key_1 = "SixteenbyteskeyplSixteenbyteskey";
    std::string iv_1 = "Firsttetbytesiv";
    std::string target_cipher_1 =
        "0x12c533d803a6bb9024ff8deb6849af1e465fc1414f0f60d86fd08c94";
    std::vector<unsigned char> byte_plaintext_1(plaintext_1.begin(),
                                                plaintext_1.end());
    std::vector<unsigned char> byte_key_1(key_1.begin(), key_1.end());
    std::vector<unsigned char> byte_iv_1(iv_1.begin(), iv_1.end());
    std::vector<unsigned char> encryptext_1;
    encryptext_1 =
        AES::gcmEncrypt(byte_plaintext_1, byte_key_1, byte_iv_1, false);

    std::vector<unsigned char> add;
    std::vector<unsigned char> encryptext_2;
    std::vector<unsigned char> tag;
    AES::encrypt(byte_plaintext_1, byte_plaintext_1, byte_key_1, byte_iv_1, encryptext_2, tag);
    std::cout << Helper::toHexString(encryptext_2) << std::endl;
    std::cout << Helper::toHexString(tag) << std::endl;
}