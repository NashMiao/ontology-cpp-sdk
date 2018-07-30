
#include "../src/common/Helper.h"
#include "../src/crypto/AES.h"
#include "../src/crypto/Digest.h"

#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(AES, generateKey)
{
    std::string password = "password";
    std::vector<unsigned char> passwordBytes(password.begin(), password.end());
    std::cout << Helper::toHexString(Digest::sha256(passwordBytes)) << std::endl;
    std::string key = Helper::toHexString(AES::generateKey(password));
    std::string expect_key =
        "73641c99f7719f57d8f4beb11a303afcd190243a51ced8782ca6d3dbe014d14603036c12"
        "be3726eb283d078dff481175e96224f0b0c632c7a37e10eb40fe6be889";
    EXPECT_EQ(expect_key, key);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}