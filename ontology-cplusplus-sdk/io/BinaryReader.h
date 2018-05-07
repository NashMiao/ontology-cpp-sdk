#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <fstream>

class BinaryReader {
  // LittleEndian
  long long bytes8ToInt(unsigned char *bytes) {
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

public:
  long long readVarInt(long long max, std::ifstream &infile) {
    int buf_size = sizeof(long long) / sizeof(unsigned char);
    unsigned char *buffer = new unsigned char[buf_size];
    infile.read((char *)(&buffer[0]), buf_size);

    delete[] buffer;
  }
};
#endif