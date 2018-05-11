#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"
#include "../../transaction/Transaction.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

// using namespace boost::multiprecision;
using namespace std;

struct BlockStruct {
  int version;
  boost::multiprecision::uint256_t prevBlockHash;
  boost::multiprecision::uint256_t transactionsRoot;
  boost::multiprecision::uint256_t blockRoot;
  int timestamp;
  int height;
  long long consensusData;
  vector<unsigned char> consensusPayload;
  // Address nextBookkeeper;
  std::vector<string> sigData;
  // std::vector<std::vector<uint8_t>> bookkeepers;
  std::vector<Transaction> transactions;
  uint256_t hash;
};

class Block {
private:
  BlockStruct header;

public:
  bool isHeader() {
    if (header.transactions.size() == 0) {
      return true;
    }
    return false;
  }

  void deserialize() {
    std::string result = "00000000c23b936425c51041ac2f69a4950040559baee7aa07ca0"
                         "404863e3bd4b22c07ca"
                         "db08cf2f8ea6ff968dec5ce1c7d61ac0a858e775d30508a4432a1"
                         "745049a99f0f3b013a8"
                         "e7816026d2e1609eca558a30e204337b27bf329bd77001479b5dc"
                         "90d68fbdf5a01000000"
                         "b841e81a33821b2e021448236ac019300c8beb6b44fabba39942c"
                         "57b0423120202a76a43"
                         "4b18379e3bda651b7c04e972dadc4760d1156b5c86b3c4d27da48"
                         "c91a12312020384d843"
                         "c02ecef233d3dd3bc266ee0d1a67cf2a1666dc1b2fb455223efde"
                         "e745223120203c43f13"
                         "6596ee666416fedb90cde1e0aee59a79ec18ab70e82b73dd29776"
                         "7eddf23120203fab194"
                         "38e18d8a5bebb6cd3ede7650539e024d7cc45c88b95ab13f8266c"
                         "e95700341014d789755"
                         "d890a9bc36ec4646841ba3bed2dced684e473267e99fc451ed57b"
                         "5540bd9cdd9770efa27"
                         "43418ee3a0f8c9905e472f35112a99d2058e7a5c201d31ce4101b"
                         "edd29e05c79b71800b2"
                         "ec67870f5c8497ab150bc811333eaa1d3cf87ae2f3c07e2a97958"
                         "5cd2b17600aaa98b24f"
                         "8dd1eb02dc067b46f6c6bd509e05f4911d6841015088a1dc841da"
                         "c040134fee1f61247b1"
                         "38b139973454e562777bcced5fa3b88d097d5c12c2bf26ccbdd38"
                         "6f06746839e692c72c0"
                         "1a218e50966c2b79f3742b3801000000000000000000d715abfe6"
                         "2912815000000000000"
                         "0000000000";
    BinaryReader BinRead;
    BinRead.set_uc_vec(result);

    nlohmann::json block;
    int version = BinRead.readInt();
    block["version"] = version;
    std::string prevBlockHash = BinRead.Read8Bytes();
    block["PrevBlockHash"] = prevBlockHash;
    std::string TransactionsRoot = BinRead.Read8Bytes();
    block["TransactionsRoot"] = TransactionsRoot;
    std::string BlockRoot = BinRead.Read8Bytes();
    block["BlockRoot"] = BlockRoot;
    int Timestamp = BinRead.readInt();
    block["Timestamp"] = Timestamp;
    int Height = BinRead.readInt();
    block["Height"] = Height;
    long long consensusData = BinRead.readLong();
    block["consensusData"] = consensusData;
    std::string nextBookkeeper = BinRead.Read5Bytes();
    block["nextBookkeeper"] = nextBookkeeper;
    int len = BinRead.readVarInt();
    std::vector<std::string> bookkeepers;
    for (int i = 0; i < len; i++) {
      bookkeepers.push_back(BinRead.readVarBytes());
    }
    block["bookkeepers"] = bookkeepers;

    int sigDataLen = BinRead.readVarInt();
    std::vector<std::string> sigData;
    for (int i = 0; i < sigDataLen; i++) {
      sigData.push_back(BinRead.readVarBytes());
    }
    block["sigData"] = sigData;

    cout << block << endl;
  }

  //   public:
  //     void deserializeUnsigned(BinaryReader& reader)
  //     {
  //         try
  //         {
  //             header.version = reader.readInt();
  //             header.prevBlockHash = reader.readSerializable();
  //             header.transactionsRoot = reader.readSerializable();
  //             header.blockRoot = reader.readSerializable();
  //             header.timestamp = reader.readInt();
  //             header.height = reader.readInt();
  //             header.consensusData = Long.valueOf(reader.readLong());
  //             header.consensusPayload.push_back(reader.readVarBytes());
  //             header.nextBookkeeper = reader.readSerializable();
  //             int len = (int)reader.readVarInt();
  //             _header.bookkeepers = new byte[len][];
  //             for (int i = 0; i < len; i++)
  //             {
  //                 this.bookkeepers[i] = reader.readVarBytes();
  //             }
  //             transactions = new Transaction[0];
  //         }
  //         catch (exception e)
  //         {
  //             throw "deserializeUnsigned Error!";
  //         }
  //     }

  //     void serializeUnsigned(BinaryWriter writer)
  //     {
  //         writer.writeInt(version);
  //         writer.writeSerializable(prevBlockHash);
  //         writer.writeSerializable(transactionsRoot);
  //         writer.writeSerializable(blockRoot);
  //         writer.writeInt(timestamp);
  //         writer.writeInt(height);
  //         writer.writeLong(consensusData);
  //         writer.writeSerializable(nextBookkeeper);
  //     }

  //     void deserialize(BinaryReader reader)
  //     {
  //         deserializeUnsigned(reader);
  //         int len = (int)reader.readVarInt();
  //         sigData = new String[len];
  //         for (int i = 0; i < len; i++)
  //         {
  //             this.sigData[i] = Helper.toHexString(reader.readVarBytes());
  //         }

  //         len = reader.readInt();
  //         transactions = new Transaction[len];
  //         for (int i = 0; i < transactions.length; i++)
  //         {
  //             transactions[i] = Transaction.deserializeFrom(reader);
  //         }
  //         if (transactions.length > 0)
  //         {
  //             if ((height != 0 &&
  //                  transactions[0].txType != TransactionType.Bookkeeping) ||
  //                 Arrays.stream(transactions)
  //                     .skip(1)
  //                     .anyMatch(p->p.txType == TransactionType.Bookkeeping))
  //             {
  //                 throw new IOException();
  //             }
  //         }
  //     }
};
