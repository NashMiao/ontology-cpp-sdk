#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <codecvt>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string.h>
#include <string>

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

public:
  BinaryWriter() { outfile.open("outfile", ios::out | ios::binary); }
  void set_ofstream(std::ofstream &ofstrm) { outfile.copyfmt(ofstrm); }
  bool writeVarInt(long long v) {
    if (!outfile.is_open()) {
      return false;
    }

    cout << v << endl;

    unsigned char buffer;
    if (v < 0xFD) {
      buffer = v;
      outfile.write((char *)&buffer, 1);
    } else if (v <= 0xFFFF) {
      buffer = 0xFD;
      outfile.write((char *)&buffer, 1);
      outfile.write((char *)&v, 2);
    } else if (v <= 0xFFFFFFFF) {
      buffer = 0xFE;
      cout << "!!!!!" << endl;
      cout << myhexStr((unsigned char *)&v, 4) << endl;
      outfile.write((char *)&buffer, 1);
      outfile.write((char *)&v, 4);
    } else {
      buffer = 0xFF;
      outfile.write((char *)&buffer, 1);
      outfile.write((char *)&v, 8);
    }
    return true;
  }

  bool writeVarBytes(const unsigned char *v) {
    long long len = (sizeof(v) / sizeof(unsigned char));
    if (!writeVarInt(len)) {
      return false;
    }
    if (!outfile.is_open()) {
      return false;
    }
    outfile.write((char *)v, len);
    return true;
  }

  bool writeVarString(const std::string &str) {
    int str_len = str.length();
    std::string utf8_str(str);
    writeVarInt(str_len);
    writeVarBytes((unsigned char *)str.c_str());
    return true;
  }
};
#endif
