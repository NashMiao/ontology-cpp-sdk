#ifndef SIG_H
#define SIG_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <stdexcept>
#include <string>
#include <vector>

#include "../../core/program/Program.h"
#include "../../io/BinaryReader.h"
#include "../../io/BinaryWriter.h"
#include "../../io/Serializable.h"

class Sig : public Serializable
{
private:
  std::vector<std::string> pubKeys;
  int M;
  std::vector<std::string> sigData;

public:
  Sig() {}
  Sig(const std::vector<std::string> &_pubKeys, int _M,
      const std::vector<std::string> &_sigData)
      : M(_M)
  {
    pubKeys.insert(pubKeys.end(), _pubKeys.begin(), _pubKeys.end());
    sigData.insert(sigData.end(), _sigData.begin(), _sigData.end());
  }
  Sig(const std::string &_pubKey, int _M, const std::string _sigData) : M(_M)
  {
    pubKeys.push_back(_pubKey);
    sigData.push_back(_sigData);
  }

  int sigData_length() { return (int)sigData.size(); }

  void add_sigData(std::vector<unsigned char> &_sig_data)
  {
    std::string str(_sig_data.begin(), _sig_data.end());
    sigData.push_back(str);
  }
  void add_pubKeys(std::vector<unsigned char> pub_key)
  {
    std::string str(pub_key.begin(), pub_key.end());
    pubKeys.push_back(str);
  }
  void add_M(int m = 1) { M += m; }

  void serialize(BinaryWriter *writer)
  {
    writer->writeVarBytes(Program::ProgramFromParams(sigData));
    size_t key_sz = pubKeys.size();
    if (key_sz == 1)
    {
      writer->writeVarBytes(Program::ProgramFromPubKey(pubKeys[0]));
    }
    else if (key_sz > 1)
    {
      writer->writeVarBytes(Program::ProgramFromMultiPubKey(M, pubKeys));
    }
    else
    {
      throw std::runtime_error("Sig serialize error.");
    }
  }

  void deserialize(BinaryReader *reader)
  {
    long long pub_key_len = reader->readVarInt();
    for (int i = 0; i < pub_key_len; i++)
    {
      pubKeys.push_back(reader->readVarBytes());
    }
    M = (int)reader->readVarInt();
    int sig_data_len = (int)reader->readVarInt();
    for (int i = 0; i < sig_data_len; i++)
    {
      sigData.push_back(reader->readVarBytes());
    }
  }
};
#endif // !SIG_H