
#include "../common/Helper.h"

#include <string>

#include <gtest/gtest.h>

TEST(Base58Test, DecodeTest)
{
    std::vector<unsigned char> vchRet;
    std::string encode_str = "TA4WVfUB1ipHL8s3PRSYgeV1HhAU3KcKTq";
    std::string decode_str = "0x410100aeb10ff2919bfe14dc432899d3b649893119f6c9dbb4";
    Helper::DecodeBase58(encode_str, vchRet);
    EXPECT_EQ(decode_str, Helper::toHexString(vchRet));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}