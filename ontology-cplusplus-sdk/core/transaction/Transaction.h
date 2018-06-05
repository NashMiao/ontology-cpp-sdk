#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../../core/asset/Fee.h"
#include "../asset/Sig.h"
#include "Attribute.h"
#include "TransactionType.h"
#include <nlohmann/json.hpp>

#include <vector>

class Transaction {
private:
  unsigned int version;
  TransactionType txType;
  long long gasPrice = 0;
  long long gasLimit = 0;
  int nonce;
  std::vector<Attribute> attributes;
  std::vector<Fee> fee;
  long long networkFee;
  std::vector<Sig> sigs;

public:
  Transaction(TransactionType type) {
    // int nonce = new Random().nextInt();
    // Fee[] fee = new Fee[0];
    // Sig[] sigs = new Sig[0];
    version = 0;
    txType = type;
  }

  // void json_out()
  // {
  //   nlohmann::json Result;
  //   Result["version"] = version;
  //   Result["TxType"] = txType;
  //   Result["Nonce"] = nonce;
  //   Result["Attributes"] = attributes;
  //   Result["Fee"] = fee;
  //   Result["NetworkFee"] = networkFee;
  //   Result["Sigs"] = sigs;
  //   cout << "Result:\n"
  //        << Result << endl;
  // }

  void deserialize() {
    std::string result =
        "00d1ee68fdec0000000000000000807d67000080b0cc71bda8653599c5666cae084bff"
        "587e2de10064231202032fac97c3c721c437fe310b5d8e075c6e925d2de59d0713078a"
        "ef28b70287ab612a6469643a6f6e743a5441345a63724845427a683557686d4d4e6e38"
        "6f68353357543368755a65316a767452c1125265674964576974685075626c69634b65"
        "79000000000000000000000101231202032fac97c3c721c437fe310b5d8e075c6e925d"
        "2de59d0713078aef28b70287ab6101014101417f393dfe2ca8fc9fbee036dce56142b6"
        "176f510359b3cf70164da14c83dfb0f21bd5157c141463f622a84bfd631a016bf17b3a"
        "8a835081a67601a7bc0b9bd3";
    BinaryReader reader;
    reader.set_uc_vec(result);
    deserializeUnsigned(reader);
    try {
      reader.readSerializableArray(sigs);
    } catch (const char *e) {
      cerr << e << endl;
    }
  }

  void deserializeUnsigned(BinaryReader &reader) {
    version = reader.readByte();
    cout << "version: " << version << endl;
    if (txType != reader.readByte()) {
      throw "IOException";
    }
    cout << "t_txtype: " << txType << endl;
    gasPrice = reader.readLong();
    gasLimit = reader.readLong();
    cout << "gasPrice: " << gasPrice << endl;
    cout << "gasLimit: " << gasLimit << endl;
    // try{
      
    // }
    deserializeUnsignedWithoutType(reader);
  }

  void deserializeUnsignedWithoutType(BinaryReader &reader) {
    deserializeExclusiveData(reader);
    reader.readSerializableArray(attributes);

    int fee_len = (int)reader.readVarInt();
    cout << "fee_len: " << fee_len << endl;
    for (int i = 0; i < fee_len; i++) {
      Fee t_fee;
      t_fee.deserialize(reader);
      fee.push_back(t_fee);
    }
    networkFee = reader.readLong();
  }

  void deserializeExclusiveData(BinaryReader &reader) {}
};
#endif // TRANSACTION_H