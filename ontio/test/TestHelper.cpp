
#include "../src/common/Helper.h"

#include <string>

#include <gtest/gtest.h>

TEST(Base58Test, DecodeTest) {
  std::vector<unsigned char> vchRet;
  std::string encode_str = "TA4WVfUB1ipHL8s3PRSYgeV1HhAU3KcKTq";
  std::string decode_str =
      "0x410100aeb10ff2919bfe14dc432899d3b649893119f6c9dbb4";
  Helper::DecodeBase58(encode_str, vchRet);
  EXPECT_EQ(decode_str, Helper::toHexString(vchRet));
}

TEST(BASE64Test, EncodeTest) {
  std::string raw_str = "this is a example";
  std::string no_wrap_target = "dGhpcyBpcyBhIGV4YW1wbGU=";
  std::string no_padding_target = "dGhpcyBpcyBhIGV4YW1wbGUK";
  std::string no_wrap_base64_str = Helper::base64Encode(raw_str, true);
  EXPECT_EQ(no_wrap_target, no_wrap_base64_str);
  std::string no_padding_base64_str = Helper::base64Encode(raw_str, false);
  EXPECT_EQ(no_padding_target, no_padding_base64_str);
}

TEST(BASE64Test, DecodeTest) {
  std::string target = "this is a example";
  std::string no_wrap_str = "dGhpcyBpcyBhIGV4YW1wbGU=";
  std::string no_padding_str = "dGhpcyBpcyBhIGV4YW1wbGUK";
  std::string no_wrap_raw = Helper::base64Decode(no_wrap_str, true);
  EXPECT_EQ(no_wrap_raw, target);
  std::string no_padding_raw = Helper::base64Decode(no_padding_str, false);
  EXPECT_EQ(no_padding_raw, target);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}