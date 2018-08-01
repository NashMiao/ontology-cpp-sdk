#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "../src/common/Helper.h"
#include "../src/crypto/ECC.h"
#include "../src/sdk/wallet/Control.h"

TEST(Control, SaltTest) {
  Control ctr;
  std::vector<unsigned char> in_salt;
  std::vector<unsigned char> out_salt;
  in_salt = ECC::generateKey(16);
  ctr.setSalt(in_salt);
  out_salt = ctr.getSalt();
  EXPECT_EQ(in_salt, out_salt) << Helper::toHexString(in_salt) << std::endl
                               << Helper::toHexString(out_salt) << std::endl;
}

TEST(Control, toStringTest) {
  Control crt;
  std::string str1 =
      "{\"address\":\"\",\"algorithm\":\"ECDSA\",\"enc-alg\":\"aes-256-gcm\","
      "\"hash\":\"sha256\",\"id\":\"\",\"key\":\"\",\"parameters\":{\"curve\":"
      "\"secp256r1\"},\"publicKey\":\"\",\"salt\":\"\"}";
  EXPECT_EQ(str1, crt.toString());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}