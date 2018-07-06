#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <codecvt>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>
#include <vector>

using namespace std;

std::string myhexStr(unsigned char *data, int len)
{
  char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                   '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i)
  {
    s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}

class BinaryWriter
{
private:
  std::vector<unsigned char> uc_vec;

  void bytes_push_back(unsigned char *bytes, int len)
  {
    for (int i = 0; i < len; i++)
    {
      uc_vec.push_back(bytes[i]);
    }
  }

  void long2bytes(const long long v, unsigned char *bytes, int bytes_len)
  {
    for (int i = 1; i < bytes_len; i++)
    {
      bytes[i] = (v >> 8 * (8 - i)) & 0xFF;
    }
  }

  std::vector<unsigned char> long2bytes(const long long v)
  {
    size_t bytes_len = sizeof(long long);
    std::vector<unsigned char> bytes;
    for (size_t i = 0; i < bytes_len; i++)
    {
      bytes.push_back((v >> 8 * (7 - i)) & 0xFF);
    }
    int n = 1;
    // little endian if true
    if (*(char *)&n == 1)
    {
      std::reverse(std::begin(bytes), std::end(bytes));
    }
    return bytes;
  }

  std::vector<unsigned char> int2bytes(const int v)
  {
    size_t bytes_len = sizeof(int);
    std::vector<unsigned char> bytes;
    for (size_t i = 0; i < bytes_len; i++)
    {
      bytes.push_back((v >> 8 * (7 - i)) & 0xFF);
    }
    int n = 1;
    // little endian if true
    if (*(char *)&n == 1)
    {
      std::reverse(std::begin(bytes), std::end(bytes));
    }
    return bytes;
  }

  std::vector<unsigned char> short2bytes(const short v)
  {
    size_t bytes_len = sizeof(short);
    std::vector<unsigned char> bytes;
    for (size_t i = 0; i < bytes_len; i++)
    {
      bytes.push_back((v >> 8 * (7 - i)) & 0xFF);
    }
    int n = 1;
    // little endian if true
    if (*(char *)&n == 1)
    {
      std::reverse(std::begin(bytes), std::end(bytes));
    }
    return bytes;
  }

public:
  BinaryWriter() {}

  std::vector<unsigned char> toByteArray() { return uc_vec; }

  void write(const std::vector<unsigned char> &buffer)
  {
    uc_vec.insert(uc_vec.end(), buffer.begin(), buffer.end());
  }

  void writeBool(bool v)
  {
    if (sizeof(bool) != 1)
    {
      throw std::runtime_error("IOException");
    }
    unsigned char v_uc = v ? 1 : 0;
    uc_vec.push_back(v_uc);
  }

  bool writeVarInt(long long v)
  {
    if (v < 0xFD)
    {
      unsigned char buffer = v & 0xFF;
      uc_vec.push_back(buffer);
    }
    else if (v <= 0xFFFF)
    {
      int bytes_len = 3;
      unsigned char *bytes = new unsigned char[bytes_len];
      long2bytes(v, bytes, bytes_len);
      bytes[0] = 0xFD;
      bytes_push_back(bytes, bytes_len);
      delete[] bytes;
    }
    else if (v <= 0xFFFFFFFF)
    {
      int bytes_len = 5;
      unsigned char *bytes = new unsigned char[bytes_len];
      long2bytes(v, bytes, bytes_len);
      bytes[0] = 0xFE;
      bytes_push_back(bytes, bytes_len);
      delete[] bytes;
    }
    else
    {
      int bytes_len = 9;
      unsigned char *bytes = new unsigned char[bytes_len];
      long2bytes(v, bytes, bytes_len);
      bytes[0] = 0xFF;
      bytes_push_back(bytes, bytes_len);
      delete[] bytes;
    }
    return true;
  }

  void writeByte(unsigned char v) { uc_vec.push_back(v); }

  void writeShort(short v)
  {
    if (sizeof(short) != 2)
    {
      throw std::runtime_error("IOException");
    }
    std::vector<unsigned char> bytes;
    bytes = short2bytes(v);
    uc_vec.insert(uc_vec.end(), bytes.begin(), bytes.end());
  }

  void writeInt(int v)
  {
    if (sizeof(int) != 4)
    {
      throw std::runtime_error("IOException");
    }
    std::vector<unsigned char> bytes;
    bytes = int2bytes(v);
    uc_vec.insert(uc_vec.end(), bytes.begin(), bytes.end());
  }

  void writeLong(long long v)
  {
    if (sizeof(long long) != 8)
    {
      throw std::runtime_error("IOException");
    }
    std::vector<unsigned char> bytes;
    bytes = long2bytes(v);
    uc_vec.insert(uc_vec.end(), bytes.begin(), bytes.end());
  }

  bool writeVarBytes(const unsigned char *v)
  {
    long long len = (strlen((char *)v) / sizeof(unsigned char));

    if (!writeVarInt(len))
    {
      return false;
    }

    for (int i = 0; i < len; i++)
    {
      uc_vec.push_back(v[i]);
    }
    return true;
  }

  bool writeVarBytes(const std::vector<unsigned char> &_vec)
  {
    long long len = _vec.size();

    if (!writeVarInt(len))
    {
      return false;
    }
    uc_vec.insert(uc_vec.cend(), _vec.cbegin(), _vec.cend());
    return true;
  }

  bool writeVarBytes(const std::string &str)
  {
    int str_len = str.length();
    std::string utf8_str(str);
    if (!writeVarInt(str_len))
    {
      return false;
    }
    if (!writeVarBytes((unsigned char *)str.c_str()))
    {
      return false;
    }
    return true;
  }

  bool writeVarString(const std::string &str)
  {
    int str_len = str.length();
    ;
    if (!writeVarInt(str_len))
    {
      return false;
    }
    if (!writeVarBytes((unsigned char *)str.c_str()))
    {
      return false;
    }
    return true;
  }

  template <class T>
  void writeSerializable(T &v) { v.serialize(this); }

  template <class T>
  bool writeSerializableArray(const std::vector<T> &t_vec)
  {
    size_t sz = t_vec.size();
    if (!writeVarInt((int)sz))
    {
      for (size_t i = 0; i < sz; i++)
      {
        T t_item;
        t_item = t_vec[i];
        t_item.serialize(this);
      }
      return false;
    }
    return true;
  }
};
#endif
