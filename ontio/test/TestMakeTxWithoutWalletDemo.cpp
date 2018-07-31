#include <gtest/gtest.h>

#include "demo/MakeTxWithoutWalletDemo.h"

TEST(MakeTxWithoutWalletDemo, TRANSER)
{
    MakeTxWithoutWalletDemo make_tx_without_wallet_demo;
    make_tx_without_wallet_demo.init();
    make_tx_without_wallet_demo.transer();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}