#ifndef SIG_H
#define SIG_H

#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"
#include <string>
#include <vector>
class Sig : public Srializable {
private:
  std::vector<std::string> pubKeys;
  int M;
  std::vector<std::string> sigData;

public:
  void Sig(const std::vector<std::string> &_pubKeys, int _M,
           const std::vector<std::string> &_sigData) {
    pubKeys.insert(pubKeys.end(), _pubKeys.begin(), _pubKeys.end());
    M = _M;
    sigData.insert(sigData.end(), _sigData.begin(), _sigData.end());
  }
  void add_sigData(std::vector<unsigned char> &_sig_data) {
    std::string str(_sig_data.begin(), _sig_data.end());
    sigData.push_back(str);
  }
  void add_pubKeys(std::vector<unsigned char> pub_key) {
    std::string str(pub_key.begin(), pub_key.end());
    pubKeys.push_back(str);
  }
  void add_M(int m = 1) { M += m; }

  void serialize(BinaryWriter &writer) {
    writer.writeVarInt(pubKeys.size());
    std::vector<std::string>::const_iterator cst_it;
    for (cst_it = pubKeys.cbegin(); cst_it != pubKeys.cend(); cst_it++) {
      writer.writeVarBytes(*cst_it);
    }
    writer.writeVarInt(M);
    writer.writeVarInt(SigData.size());
    for (cst_it = sigData.cbegin(); cst_it != sigData.cend(); cst_it++) {
      writer.writeVarBytes(*cst_it);
    }
  }
  void deserialize(BinaryReader *reader) {
    long long pub_key_len = reader->readVarInt();
    for (int i = 0; i < pub_key_len; i++) {
      pubKeys.push_back(reader->readVarBytes());
    }
    M = (int)reader.readVarInt();
    int sig_data_len = (int)reader->readVarInt();
    for (int i = 0; i < sig_data_len; i++) {
      sigData.push_back(reader->readVarBytes());
    }
  }
};
#endif // !SIG_H