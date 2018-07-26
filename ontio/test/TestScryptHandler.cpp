#include <string>
#include <vector>
#include <iostream>

#include <gtest/gtest.h>

#include "../common/Helper.h"
#include "../crypto/ScryptHandler.h"

TEST(ScryptHandlerTest, ScryptTest)
{
    int n = 16384;
    int r = 8;
    int p = 8;
    int dkLen = 64;
    std::string password = "passwordtest";
    int salt_len = 4;
    std::string raw_salt = "0xfaa4883d";
    std::vector<unsigned char> salt = Helper::hexStringToByte(raw_salt);
    std::vector<unsigned char> dkey;
    dkey = ScryptHandler::scrypt(password, salt, n, r, p, dkLen);
    std::string hex_dkey = Helper::toHexString(dkey);
    std::string target =
        "0x9f0632e05eab137baae6e0a83300341531e8638612a08042d3a4074578869af1ccf500"
        "8e434d2cae9477f9e6e4c0571ab65a60e32e8c8fc356d95f64dd9717c9";
    ASSERT_EQ(target, hex_dkey);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}