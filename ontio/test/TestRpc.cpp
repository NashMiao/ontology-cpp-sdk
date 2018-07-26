#include <string>

#include <gtest/gtest.h>

#include "../src/common/Helper.h"
#include "../src/network/connect/IConnector.h"
#include "../src/sdk/manager/ConnectMgr.h"

TEST(RpcTest, RpcGetTest) {
  std::string url = "http://polaris1.ont.io:20336";
  ConnectMgr connect_mgr(url, ConnectType::RPC);
  int obj;
  obj = connect_mgr.getNodeCount();
  EXPECT_EQ(1, obj);
  obj = connect_mgr.getBlockHeight();
  std::string contract_hash = "fff49c809d302a2956e9dc0012619a452d4b846c";
  nlohmann::json ret;
  ret = connect_mgr.getContractJson(contract_hash);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}