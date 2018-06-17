#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../../core/asset/Fee.h"
#include "../../core/transaction/Transaction.h"
#include "../Inventory.h"
#include "../asset/Sig.h"
#include "Attribute.h"
#include "TransactionType.h"
#include <nlohmann/json.hpp>

#include <stdlib.h>
#include <time.h>
#include <vector>

class Transaction : public Inventory {
private:
  unsigned int version;
  TransactionType txType;
  long long gasPrice;
  long long gasLimit;
  int nonce;
  std::vector<Attribute> attributes;
  std::vector<Fee> fee;
  long long networkFee;
  std::vector<Sig> sigs;

public:
  Transaction() {
    gasPrice = 0;
    gasLimit = 0;
  }
  Transaction(TransactionType type) {
    srand((unsigned)time(NULL));
    nonce = rand();
    txType = type;
    gasPrice = 0;
    gasLimit = 0;
    version = 0;
  }

  void set_sigs(std::vector<Sig> &_sigs) { sigs = _sigs; }

  Sig get_sig(int i) {
    Sig ret_sig;
    try {
      ret_sig = sigs[i];
    } catch (const std::out_of_range &oor) {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
    return ret_sig;
  }

  int sigs_length() { return (int)sigs.size(); }

  bool sigs_empty() { return sigs.empty(); }

  nlohmann::json json_out() {
    nlohmann::json Result;
    Result["version"] = version;
    // Result["TxType"] = txType;
    Result["Nonce"] = nonce;
    // Result["Attributes"] = attributes;
    // Result["Fee"] = fee;
    Result["NetworkFee"] = networkFee;
    // Result["Sigs"] = sigs;
    return json_out;
  }

  void serializeUnsigned(BinaryWriter *writer) {
    writer->writeByte(version);
    writer->writeByte(txType;
    writer->writeInt(nonce);
    writer->writeLong(gasPrice);
    writer->writeLong(gasLimit);
    writer->writeSerializable(payer);
    serializeExclusiveData(*writer);
    writer->writeSerializableArray(attributes);
  }

  void serialize(BinaryWriter *writer) {
    serializeUnsigned(*writer);
    writer->writeSerializableArray(sigs);
  }

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
    if (txType != reader.readByte()) {
      throw "IOException";
    }
    gasPrice = reader.readLong();
    gasLimit = reader.readLong();
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