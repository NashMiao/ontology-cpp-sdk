#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <fstream>
#include <iostream>

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

public:
  BinaryReader() {
    infile.open("outfile", std::ios::in | std::ios::binary);
  }
  void set_ifstream(std::ifstream &ifstrm) { infile.copyfmt(ifstrm); }
  bool readVarInt(long long max, long long &value) {
    if (!infile.is_open()) {
      return false;
    }
    unsigned char uc_buffer;
    infile.read((char *)(&uc_buffer), 1);
    cout << uc_buffer << endl;

    if (uc_buffer == 0xFD) {
      int buf_size = 2;
      unsigned char *buffer = new unsigned char[buf_size];
      infile.read((char *)&buffer[0], buf_size);
      value = bytesNToLong(buffer, buf_size);
      delete[] buffer;
    } else if (uc_buffer == 0xFE) {
      int buf_size = 4;
      unsigned char *buffer = new unsigned char[buf_size];
      infile.read((char *)&buffer[0], buf_size);
      value = bytesNToLong(buffer, buf_size);
      delete[] buffer;
    } else if (uc_buffer == 0xFF) {
      int buf_size = 8;
      unsigned char *buffer = new unsigned char[buf_size];
      infile.read((char *)&buffer[0], buf_size);
      value = bytesNToLong(buffer, buf_size);
      delete[] buffer;
    } else {
      value = (long long)uc_buffer;
    }
    return true;
  }

  unsigned char *readBytes(int count) {
    unsigned char *buffer = new unsigned char[count];
    infile.read((char *)buffer, count);
    return buffer;
  }

  bool readVarBytes() {
    long long value;
    readVarInt(0X7fffffc7, value);
    readBytes((int)value);
    return true;
  }
};
#endif