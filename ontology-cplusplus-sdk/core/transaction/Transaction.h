#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../../core/transaction/Transaction.h"
#include "../Inventory.h"
#include "../asset/Sig.h"
#include "Attribute.h"
#include "TransactionType.h"
#include <nlohmann/json.hpp>

#include <stdlib.h>
#include <time.h>
#include <vector>

class Transaction : public Inventory, public Serializable
{
private:
  long long gasPrice;
  long long gasLimit;
  TransactionType txType;
  Address payer;
  std::vector<Attribute> attributes;
  std::vector<Sig> sigs;
  int nonce;
  unsigned int version;

public:
  Transaction() : Inventory(), Serializable() {}

  Transaction(TransactionType _txType, unsigned int _version = 0)
      : Inventory(), Serializable(), version(_version)
  {
    srand((unsigned)time(NULL));
    nonce = rand();
  }

  Transaction(TransactionType _txType, Address _payer, long long _gasPrice,
              long long _gasLimit, unsigned int _version = 0)
      : Inventory(), Serializable(), gasPrice(_gasPrice),
        gasLimit(_gasLimit), txType(_txType), payer(_payer), version(_version)
  {
    srand((unsigned)time(NULL));
    nonce = rand();
  }

  Transaction(TransactionType _txType, long long _gasPrice, long long _gasLimit,
              unsigned int _version = 0)
      : Inventory(), Serializable(), gasPrice(_gasPrice),
        gasLimit(_gasLimit), version(_version)
  {
    srand((unsigned)time(NULL));
    nonce = rand();
  }

  Transaction(TransactionType _txType, TransactionType _type,
              long long _gasPrice, long long _gasLimit,
              const std::vector<Attribute> &_attributes,
              const std::vector<Sig> &_sigs, unsigned int _version)
      : Inventory(), Serializable(), gasPrice(_gasPrice),
        gasLimit(_gasLimit), txType(_type), attributes(_attributes),
        sigs(_sigs), version(_version)
  {
    srand((unsigned)time(NULL));
    nonce = rand();
  }

  Transaction &operator=(Transaction &tx)
  {
    this->version = tx.version;
    this->gasPrice = tx.gasPrice;
    this->gasLimit = tx.gasLimit;
    this->txType = tx.txType;
    this->payer = tx.payer;
    this->attributes = tx.attributes;
    this->sigs = tx.sigs;
    this->nonce = tx.nonce;
    return *this;
  }

  void set_sigs(std::vector<Sig> &_sigs) { sigs = _sigs; }

  Sig get_sig(int i)
  {
    Sig ret_sig;
    try
    {
      ret_sig = sigs[i];
    }
    catch (const std::out_of_range &oor)
    {
      std::cerr << "Out of Range error: " << oor.what() << '\n';
    }
    return ret_sig;
  }

  int sigs_length() { return (int)sigs.size(); }

  bool sigs_empty() { return sigs.empty(); }

  void set_payer(Address _payer) { payer = _payer; }

  nlohmann::json json_out()
  {
    nlohmann::json Result;
    Result["version"] = version;
    // Result["TxType"] = txType;
    Result["Nonce"] = nonce;
    // Result["Attributes"] = attributes;
    // Result["Sigs"] = sigs;
    return Result;
  }

  void serializeUnsigned(BinaryWriter *writer)
  {
    writer->writeByte(version);
    writer->writeByte(getByte(txType));
    writer->writeInt(nonce);
    writer->writeLong(gasPrice);
    writer->writeLong(gasLimit);
    writer->writeSerializable(payer);
    serializeExclusiveData(writer);
    writer->writeSerializableArray(attributes);
  }

  virtual void serializeExclusiveData(BinaryWriter *writer) = 0;

  void serialize(BinaryWriter *writer)
  {
    serializeUnsigned(writer);
    writer->writeSerializableArray(sigs);
  }

  void deserialize(BinaryReader *reader)
  {
    // std::string result =
    //     "00d1ee68fdec0000000000000000807d67000080b0cc71bda8653599c5666cae084bff"
    //     "587e2de10064231202032fac97c3c721c437fe310b5d8e075c6e925d2de59d0713078a"
    //     "ef28b70287ab612a6469643a6f6e743a5441345a63724845427a683557686d4d4e6e38"
    //     "6f68353357543368755a65316a767452c1125265674964576974685075626c69634b65"
    //     "79000000000000000000000101231202032fac97c3c721c437fe310b5d8e075c6e925d"
    //     "2de59d0713078aef28b70287ab6101014101417f393dfe2ca8fc9fbee036dce56142b6"
    //     "176f510359b3cf70164da14c83dfb0f21bd5157c141463f622a84bfd631a016bf17b3a"
    //     "8a835081a67601a7bc0b9bd3";
    // BinaryReader reader;
    // reader.set_uc_vec(result);
    deserializeUnsigned(reader);
    try
    {
      reader->readSerializableArray(sigs);
    }
    catch (const char *e)
    {
      cerr << e << endl;
    }
  }

  void deserializeUnsigned(BinaryReader *reader)
  {
    version = reader->readByte();
    if (txType != getTransactionType(reader->readByte()))
    {
      throw "IOException";
    }
    gasPrice = reader->readLong();
    gasLimit = reader->readLong();
    // try{

    // }
    deserializeUnsignedWithoutType(reader);
  }

  void deserializeUnsignedWithoutType(BinaryReader *reader)
  {
    try
    {
      deserializeExclusiveData(reader);
      reader->readSerializableArray(attributes);
    }
    catch (const char *ex)
    {
      throw "IOException(ex)";
    }
  }

  virtual void deserializeExclusiveData(BinaryReader *reader) = 0;
};
#endif // TRANSACTION_H