#ifndef BINARYWRITER_H
#define BINARYWRITER_H

#include <fstream>
#include <math.h>
#include <string.h>

class BinaryWriter {
private:
  // LittleEndian
  long int bytes4ToInt(unsigned char *bytes) {
    long int addr = bytes[0] & 0xFF;
    addr |= (bytes[1] << 8 & 0xFF00);
    addr |= ((bytes[2] << 16) & 0xFF0000);
    addr |= ((bytes[3] << 24) & 0xFF000000);
    return addr;
  }

public:
  bool writeVarInt(long long v, std::ofstream &outfile) {
    if (!outfile.is_open()) {
      return false;
    }

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
      outfile.write((char *)&buffer, 1);
      outfile.write((char *)&v, 4);
    } else {
      buffer = 0xFF;
      outfile.write((char *)&buffer, 1);
      outfile.write((char *)&v, 8);
    }
    return true;
  }

  
};
#endif
