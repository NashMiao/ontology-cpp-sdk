#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <boost/algorithm/hex.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class BinaryReader {
private:
  std::vector<unsigned char> uc_vec;
  std::vector<unsigned char>::iterator uc_vec_iter;

  // LittleEndian
  long long bytes2ToLong(unsigned char *bytes) {
    long long addr = bytes[0] & 0xFF;
    addr |= (((long long)bytes[1] << 8) & 0xFF00);
    return addr;
  }

  // LittleEndian
  long long bytes8ToLong(unsigned char *bytes) {
    long long addr = bytes[0] & 0xFF;
    addr |= (((long long)bytes[1] << 8) & 0xFF00);
    addr |= (((long long)bytes[2] << 16) & 0xFF0000);
    addr |= (((long long)bytes[3] << 24) & 0xFF000000);
    addr |= (((long long)bytes[4] << 32) & 0xFF00000000);
    addr |= (((long long)bytes[5] << 40) & 0xFF0000000000);
    addr |= (((long long)bytes[6] << 48) & 0xFF000000000000);
    addr |= (((long long)bytes[7] << 56) & 0xFF00000000000000);
    return addr;
  }

  // LittleEndian
  long long bytesNToLong(unsigned char *bytes, int buf_size) {
    int pos = 8;
    long long base = 0xFF;
    long long val = bytes[0] & base;
    for (int i = 0; i < buf_size; i++) {
      val |= (((long long)bytes[i] << (pos * i)) & (base << (2 * i)));
    }
    return val;
  }

  long long ReadBytesToLong(int len) {
    char buf[len];
    if (sizeof(long long) != 8) {
      throw "IOException";
    }
    uc_vec_iter++;
    for (int i = 0; i < len; i += 2) {
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      buf[len - 2 - i] = *uc_vec_iter;
      uc_vec_iter++;
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      buf[len - 1 - i] = *uc_vec_iter;
      uc_vec_iter++;
    }
    long long ret;
    std::stringstream ss;
    ss.str(buf);
    ss >> std::hex >> ret;
    return ret;
  }

public:
  void set_uc_vec(std::string &str) {
    // std::string hex_str = boost::algorithm::hex(str);
    uc_vec.clear();
    for (int i = 0; i < int(str.length()); i++) {
      uc_vec.push_back((unsigned char)str[i]);
    }
    uc_vec_iter = uc_vec.begin();
  }

  std::vector<unsigned char> toByteArray() { return uc_vec; }

  void read(std::vector<unsigned char> &buffer) {
    // TODO
    buffer.insert(buffer.begin(), uc_vec_iter, uc_vec_iter + buffer.size());
    uc_vec_iter += buffer.size();
  }

  long long readVarInt(long long max) {
    int tag;
    int tag_size = 2;
    char tag_buf[tag_size];
    tag_buf[0] = *uc_vec_iter;
    uc_vec_iter++;
    if (uc_vec_iter == uc_vec.end()) {
      throw "IOException";
    }
    tag_buf[1] = *uc_vec_iter;
    uc_vec_iter++;
    std::stringstream ss;
    ss.str(tag_buf);
    ss >> std::hex >> tag;

    long long value;
    if (tag == 0xFD) {
      int buf_size = 2;
      value = ReadBytesToLong(buf_size);
    } else if (tag == 0xFE) {
      int buf_size = 4;
      value = ReadBytesToLong(buf_size);
    } else if (tag == 0xFF) {
      int buf_size = 8;
      value = ReadBytesToLong(buf_size);
    } else {
      value = tag;
    }
    if (value > max) {
      throw "readVarInt Error! value > max!";
    }
    return value;
  }

  long long readVarInt() {
    int tag;
    int tag_size = 2;
    char tag_buf[tag_size];
    tag_buf[0] = *uc_vec_iter;
    uc_vec_iter++;
    if (uc_vec_iter == uc_vec.end()) {
      throw "IOException";
    }
    tag_buf[1] = *uc_vec_iter;
    uc_vec_iter++;
    std::stringstream ss;
    ss.str(tag_buf);
    ss >> std::hex >> tag;
    long long value;
    if (tag == 0xFD) {
      int buf_size = 2;
      value = ReadBytesToLong(buf_size);
    } else if (tag == 0xFE) {
      int buf_size = 4;
      value = ReadBytesToLong(buf_size);
    } else if (tag == 0xFF) {
      int buf_size = 8;
      value = ReadBytesToLong(buf_size);
    } else {
      value = tag;
    }
    return value;
  }

  int readByte() {
    int ret;
    std::stringstream ss;
    ss.str(readBytes(1));
    ss >> std::hex >> ret;
    return ret;
  }

  std::string readBytes(int count) {
    std::string str;
    for (int i = 0; i < 2 * count; i++) {
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      str.push_back(*uc_vec_iter);
      uc_vec_iter++;
    }
    return str;
  }

  std::vector<unsigned char> readBytes_vec(int count) {
    std::vector<unsigned char> ret_vec;
    for (int i = 0; i < 2 * count; i++) {
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      ret_vec.push_back(*uc_vec_iter);
      uc_vec_iter++;
    }
    return ret_vec;
  }

  std::string readVarBytes() { return readVarBytes(0X7fffffc7); }

  std::vector<unsigned char> readVarBytes_vec() {
    return readVarBytes_vec(0X7fffffc7);
  }

  std::string readVarBytes(int max) {
    int len = (int)readVarInt(max);
    return readBytes(len);
  }

  std::vector<unsigned char> readVarBytes_vec(int max) {
    int len = (int)readVarInt(max);
    return readBytes_vec(len);
  }

  float readFloat() {
    int array[8];
    for (int i = 0; i < 4; i++) {
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      uc_vec_iter++;
      array[i] = *uc_vec_iter;
    }
    if (sizeof(float) != 4) {
      throw "IOException";
    }
    float *ret = (float *)array;
    return *ret;
  }

  unsigned int readInt() {
    char buf[8];
    if (sizeof(int) != 4) {
      throw "IOException";
    }
    for (int i = 0; i < 8; i += 2) {
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }

      buf[6 - i] = *uc_vec_iter;
      uc_vec_iter++;
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      buf[7 - i] = *uc_vec_iter;
      uc_vec_iter++;
    }
    unsigned int ret;
    std::stringstream ss;
    ss.str(buf);
    ss >> hex >> ret;
    return ret;
  }

  long long readLong() {
    char buf[16];
    if (sizeof(int) != 4) {
      throw "IOException";
    }
    for (int i = 0; i < 16; i += 2) {
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      buf[14 - i] = *uc_vec_iter;
      uc_vec_iter++;
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      buf[15 - i] = *uc_vec_iter;
      uc_vec_iter++;
    }
    long long ret;
    std::stringstream ss;
    ss.str(buf);
    ss >> hex >> ret;
    return ret;
  }

  std::string Read8Bytes() {
    std::string str;
    for (int i = 0; i < 64; i++) {
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      str.push_back(*uc_vec_iter);
      uc_vec_iter++;
    }
    return str;
  }

  std::string Read5Bytes() {
    std::string str;
    for (int i = 0; i < 40; i++) {
      if (uc_vec_iter == uc_vec.end()) {
        throw "IOException";
      }
      str.push_back(*uc_vec_iter);
      uc_vec_iter++;
    }
    return str;
  }

  template <class T> void readSerializable(T &t_item) {
    t_item.deserialize(this);
  }

  template <class T> void readSerializableArray(std::vector<T> &t_vec) {
    int vec_len = (int)readVarInt(0x10000000);
    for (int i = 0; i < vec_len; i++) {
      T t_item;
      t_item.deserialize(this);
      t_vec.push_back(t_item);
    }
  }
};
#endif