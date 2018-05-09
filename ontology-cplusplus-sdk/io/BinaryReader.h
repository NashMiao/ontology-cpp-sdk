#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

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

class BinaryReader {
private:
  std::ifstream infile;
  std::vector<unsigned char> uc_vec;
  std::vector<unsigned char>::iterator uc_vec_iter;

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
    unsigned char *buffer = new unsigned char[len];
    if (len == 1) {
      buffer[0] = *uc_vec_iter;
    } else {
      for (int i = 0; i < len; i++) {
        if (uc_vec_iter != uc_vec.end()) {
          uc_vec_iter++;
          buffer[i] = *uc_vec_iter;
        } else {
          throw "ReadBytesToLong Error!";
        }
      }
    }
    long long value;
    value = bytesNToLong(buffer, len);
    delete[] buffer;
    return value;
  }

public:
  BinaryReader() { uc_vec_iter = uc_vec.begin(); }
  long long readVarInt(long long max) {
    int buf_size;
    long long value;
    if (*uc_vec_iter == 0xFD) {
      buf_size = 2;
      value = ReadBytesToLong(buf_size);
    } else if (*uc_vec_iter == 0xFE) {
      buf_size = 4;
      value = ReadBytesToLong(buf_size);
    } else if (*uc_vec_iter == 0xFF) {
      buf_size = 8;
      value = ReadBytesToLong(buf_size);
    } else {
      buf_size = 1;
      value = ReadBytesToLong(buf_size);
    }
    if (value > max) {
      throw "readVarInt Error! value > max!";
    }
    return value;
  }

  unsigned char *readBytes(int count) {
    unsigned char *buffer = new unsigned char[count];
    for (int i = 0; i < count; i++) {
      if (uc_vec_iter != uc_vec.end()) {
        uc_vec_iter++;
        buffer[i] = *uc_vec_iter;
      } else {
        throw "readBytes Error!";
      }
    }
    return buffer;
  }

  long long readVarBytes() {
    long long value;
    value = readVarInt(0X7fffffc7);
    return value;
  }
};
#endif