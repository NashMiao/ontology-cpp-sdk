
#include "../src/common/Helper.h"
#include "../src/crypto/AES.h"
#include "../src/crypto/Digest.h"

#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(AES, generateKey) {
  std::string password = "password";
  std::vector<unsigned char> passwordBytes(password.begin(), password.end());
  std::string key_1 = Helper::toHexString(AES::generateKey(password));
  std::string expect_key =
      "0x73641c99f7719f57d8f4beb11a303afcd190243a51ced8782ca6d3dbe014d146";
  EXPECT_EQ(expect_key, key_1);

  std::vector<unsigned char> key_2 = AES::generateKey();
  EXPECT_EQ(key_2.size(), 32);
}

TEST(AES, generateIv) {
  std::vector<unsigned char> iv_1 = AES::generateIv();
  EXPECT_EQ(iv_1.size(), 16);
}

TEST(AES, gcmEncrypt) {
  std::string plaintext_1 = "Hello world!";
  std::string key_1 = "SixteenbyteskeyplSixteenbyteskey";
  std::string iv_1 = "Firsttestbytesiv";
  std::string target_cipher_1 =
      "0x12c533d803a6bb9024ff8deb6849af1e465fc1414f0f60d86fd08c94";
  std::vector<unsigned char> byte_plaintext_1(plaintext_1.begin(),
                                              plaintext_1.end());
  std::vector<unsigned char> byte_key_1(key_1.begin(), key_1.end());
  std::vector<unsigned char> byte_iv_1(iv_1.begin(), iv_1.end());
  std::vector<unsigned char> encryptext_1;
  encryptext_1 =
      AES::gcmEncrypt(byte_plaintext_1, byte_key_1, byte_iv_1, false);
  EXPECT_EQ(Helper::toHexString(encryptext_1), target_cipher_1);

  std::vector<unsigned char> add;
  std::vector<unsigned char> encryptext_2;
  std::vector<unsigned char> tag;
  AES::encrypt(byte_plaintext_1, add, byte_key_1, byte_iv_1, encryptext_2, tag);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}