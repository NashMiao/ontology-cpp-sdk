#ifndef SIG_H
#define SIG_H

#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"
#include <string>
#include <vector>
class Sig {
private:
  std::vector<std::string> pubKeys;
  int M;
  std::vector<std::string> sigData;

public:
  void deserialize(BinaryReader* reader) {
    long long pub_key_len = reader->readVarInt();
    for (int i = 0; i < pub_key_len; i++) {
      pubKeys.push_back(reader->readVarBytes());
    }
    M = (int)reader->readVarInt();
    int sig_data_len = (int)reader->readVarInt();
    for (int i = 0; i < sig_data_len; i++) {
      sigData.push_back(reader->readVarBytes());
    }
  }
};
#endif // !SIG_H