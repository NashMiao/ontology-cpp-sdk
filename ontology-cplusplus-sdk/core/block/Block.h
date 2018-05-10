#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"
#include "../../transaction/Transaction.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

// using namespace boost::multiprecision;
using namespace std;

struct BlockStruct
{
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

class Block
{
  private:
    BlockStruct header;

  public:
    bool isHeader()
    {
        if (header.transactions.size() == 0)
        {
            return true;
        }
        return false;
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
