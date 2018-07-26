#ifndef URLCONSTS_H
#define URLCONSTS_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <string>

class UrlConsts {
public:
  std::string Url_send_transaction = "/api/v1/transaction";
  std::string Url_get_transaction = "/api/v1/transaction/";
  std::string Url_get_generate_block_time = "/api/v1/node/generateblocktime";
  std::string Url_get_node_count = "/api/v1/node/connectioncount";
  std::string Url_get_block_height = "/api/v1/block/height";
  std::string Url_get_block_by_height = "/api/v1/block/details/height/";
  std::string Url_get_block_by_hash = "/api/v1/block/details/hash/";
  std::string Url_get_account_balance = "/api/v1/balance/";
  std::string Url_get_contract_state = "/api/v1/contract/";
  std::string Url_get_smartcodeevent_txs_by_height =
      "/api/v1/smartcode/event/transactions/";
  std::string Url_get_smartcodeevent_by_txhash =
      "/api/v1/smartcode/event/txhash/";
  std::string Url_get_block_height_by_txhash = "/api/v1/block/height/txhash/";
  std::string Url_get_storage = "/api/v1/storage/";
  std::string Url_get_merkleproof = "/api/v1/merkleproof/";
};

#endif
