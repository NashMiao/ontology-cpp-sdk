
#include "../src/common/Helper.h"
#include "../src/crypto/Digest.h"

#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(SHA256, SHA256Test)
{
  std::vector<unsigned char> vec{0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9};
  std::string sha256_1 =
      "0x47e4ee7f211f73265dd17658f6e21c1318bd6c81f37598e20a2756299542efcf";
  EXPECT_EQ(sha256_1, Helper::toHexString(Digest::sha256(vec)));

  std::string sha256_2 =
      "0x5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8";
  std::string password = "password";
  std::vector<unsigned char> passwordBytes(password.begin(), password.end());
  EXPECT_EQ(sha256_2, Helper::toHexString(Digest::sha256(passwordBytes)));
}

TEST(HASH256, HASH256Test)
{
  std::vector<unsigned char> vec{0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9};
  std::string hash256 =
      "0x427a27c0e4a3b8009099086aec014100b8ce898d074ac841f7c80831dabb8a8c";
  EXPECT_EQ(hash256, Helper::toHexString(Digest::hash256(vec)));

  std::string hash256_2 = "0x73641c99f7719f57d8f4beb11a303afcd190243a51ced8782ca6d3dbe014d146";
  std::string password = "password";
  std::vector<unsigned char> passwordBytes(password.begin(), password.end());
  EXPECT_EQ(hash256_2, Helper::toHexString(Digest::hash256(passwordBytes)));
}

int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}