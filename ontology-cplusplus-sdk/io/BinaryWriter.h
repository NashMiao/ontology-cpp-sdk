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

std::string myhexStr(unsigned char *data, int len) {
  char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                   '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
  std::string s(len * 2, ' ');
  for (int i = 0; i < len; ++i) {
    s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
    s[2 * i + 1] = hexmap[data[i] & 0x0F];
  }
  return s;
}

class BinaryWriter {
private:
  std::ofstream outfile;
  std::vector<unsigned char> uc_vec;

  void bytes_push_back(unsigned char *bytes, int len) {
    for (int i = 0; i < len; i++) {
      uc_vec.push_back(bytes[i]);
    }
  }

  void long2bytes(const long long v, unsigned char *bytes, int bytes_len) {
    for (int i = 1; i < bytes_len; i++) {
      bytes[i] = (v >> 8 * (8 - i)) & 0xFF;
    }
  }

public:
  BinaryWriter() { outfile.open("outfile", ios::out | ios::binary); }

  void set_ofstream(std::ofstream &ofstrm) { outfile.copyfmt(ofstrm); }

  std::vector<unsigned char> toByteArray() { return uc_vec; }

  void write(const std::vector<unsigned char> &buffer) {
    uc_vec.insert(uc_vec.end(), buffer.begin(), buffer.end());
  }

  bool writeVarInt(long long v) {
    if (v < 0xFD) {
      unsigned char buffer = v & 0xFF;
      uc_vec.push_back(buffer);
    } else if (v <= 0xFFFF) {
      int bytes_len = 3;
      unsigned char *bytes = new unsigned char[bytes_len];
      long2bytes(v, bytes, bytes_len);
      bytes[0] = 0xFD;
      bytes_push_back(bytes, bytes_len);
      delete[] bytes;
    } else if (v <= 0xFFFFFFFF) {
      int bytes_len = 5;
      unsigned char *bytes = new unsigned char[bytes_len];
      long2bytes(v, bytes, bytes_len);
      bytes[0] = 0xFE;
      bytes_push_back(bytes, bytes_len);
      delete[] bytes;
    } else {
      int bytes_len = 9;
      unsigned char *bytes = new unsigned char[bytes_len];
      long2bytes(v, bytes, bytes_len);
      bytes[0] = 0xFF;
      bytes_push_back(bytes, bytes_len);
      delete[] bytes;
    }
    return true;
  }

  bool writeByte(unsigned char v) { uc_vec.push_back(v); }

  bool writeVarBytes(const unsigned char *v) {
    long long len = (sizeof(v) / sizeof(unsigned char));

    if (!writeVarInt(len)) {
      return false;
    }

    for (int i = 0; i < len; i++) {
      uc_vec.push_back(v[i]);
    }

    return true;
  }

  bool writeVarBytes(std::vector<unsigned char> _vec) {
    long long len = _vec.length();

    if (!writeVarInt(len)) {
      return false;
    }
    uc_vec.insert(uc_vec.cend(), _vec.cbegin(), _vec_cend());
    return true;
  }

  bool writeVarBytes(const std::string &str) {
    int str_len = str.length();
    std::string utf8_str(str);
    if (!writeVarInt(str_len)) {
      return false;
    }
    if (!writeVarBytes((unsigned char *)str.c_str())) {
      return false;
    }
    return true;
  }

  bool writeVarString(const std::string &str) {
    int str_len = str.length();
    std::string utf8_str(str);
    if (!writeVarInt(str_len)) {
      return false;
    }
    if (!writeVarBytes((unsigned char *)str.c_str())) {
      return false;
    }
    return true;
  }

  template <class T> bool writeSerializableArray(std::vector<T> t_vec) {
    if (!writeVarInt(t_vec.size())) {
      s int vec_len = (int)t_vec.size();
      for (int i = 0; i < vec_len; i++) {
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
