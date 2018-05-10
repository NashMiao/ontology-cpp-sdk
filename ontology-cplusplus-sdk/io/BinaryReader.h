#ifndef BINARYREADER_H
#define BINARYREADER_H

#include <boost/algorithm/hex.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// LittleEndian
long long bytes2ToLong(unsigned char *bytes)
{
  long long addr = bytes[0] & 0xFF;
  addr |= (((long long)bytes[1] << 8) & 0xFF00);
  return addr;
}

// LittleEndian
long long bytes8ToLong(unsigned char *bytes)
{
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

class BinaryReader
{
private:
  std::vector<unsigned char> uc_vec;
  std::vector<unsigned char>::iterator uc_vec_iter;

  // LittleEndian
  long long bytesNToLong(unsigned char *bytes, int buf_size)
  {
    int pos = 8;
    long long base = 0xFF;
    long long val = bytes[0] & base;
    for (int i = 0; i < buf_size; i++)
    {
      val |= (((long long)bytes[i] << (pos * i)) & (base << (2 * i)));
    }
    return val;
  }

  long long ReadBytesToLong(int len)
  {
    unsigned char *buffer = new unsigned char[len];
    if (len == 1)
    {
      buffer[0] = *uc_vec_iter;
    }
    else
    {
      for (int i = 0; i < len; i++)
      {
        if (uc_vec_iter != uc_vec.end())
        {
          uc_vec_iter++;
          buffer[i] = *uc_vec_iter;
        }
        else
        {
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
  void set_uc_vec(std::string &str)
  {
    // std::string hex_str = boost::algorithm::hex(str);
    uc_vec.clear();
    for (int i = 0; i < str.length(); i++)
    {
      uc_vec.push_back((unsigned char)str[i]);
    }
    uc_vec_iter = uc_vec.begin();
  }
  BinaryReader() { uc_vec_iter = uc_vec.begin(); }

  long long readVarInt(long long max)
  {
    int buf_size;
    long long value;
    if (*uc_vec_iter == 0xFD)
    {
      buf_size = 2;
      value = ReadBytesToLong(buf_size);
    }
    else if (*uc_vec_iter == 0xFE)
    {
      buf_size = 4;
      value = ReadBytesToLong(buf_size);
    }
    else if (*uc_vec_iter == 0xFF)
    {
      buf_size = 8;
      value = ReadBytesToLong(buf_size);
    }
    else
    {
      buf_size = 1;
      value = ReadBytesToLong(buf_size);
    }
    if (value > max)
    {
      throw "readVarInt Error! value > max!";
    }
    return value;
  }

  unsigned char *readBytes(int count)
  {
    unsigned char *buffer = new unsigned char[count];
    for (int i = 0; i < count; i++)
    {
      if (uc_vec_iter != uc_vec.end())
      {
        uc_vec_iter++;
        buffer[i] = *uc_vec_iter;
      }
      else
      {
        throw "readBytes Error!";
      }
    }
    return buffer;
  }

  long long readVarBytes()
  {
    long long value;
    value = readVarInt(0X7fffffc7);
    return value;
  }

  float readFloat()
  {
    int array[8];
    for (int i = 0; i < 4; i++)
    {
      if (uc_vec_iter == uc_vec.end())
      {
        throw "IOException";
      }
      uc_vec_iter++;
      array[i] = *uc_vec_iter;
    }
    if (sizeof(float) != 4)
    {
      throw "IOException";
    }
    float *ret = (float *)array;
    return *ret;
  }

  int readInt()
  {
    char buf[8];
    if (sizeof(int) != 4)
    {
      throw "IOException";
    }
    for (int i = 0; i < 8; i += 2)
    {
      if (uc_vec_iter == uc_vec.end())
      {
        throw "IOException";
      }

      buf[6 - i] = *uc_vec_iter;
      uc_vec_iter++;
      if (uc_vec_iter == uc_vec.end())
      {
        throw "IOException";
      }
      buf[7 - i] = *uc_vec_iter;
      uc_vec_iter++;
    }
    int ret;
        std::stringstream ss;
    ss.str(buf);
    ss >> hex >> ret;
    return ret;
  }

  long long readLong()
  {
    char buf[16];
    if (sizeof(int) != 4)
    {
      throw "IOException";
    }
    for (int i = 0; i < 16; i += 2)
    {
      if (uc_vec_iter == uc_vec.end())
      {
        throw "IOException";
      }
      buf[14 - i] = *uc_vec_iter;
      uc_vec_iter++;
      if (uc_vec_iter == uc_vec.end())
      {
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

  std::string Read8Bytes()
  {
    std::string str;
    for (int i = 0; i < 64; i++)
    {
      if (uc_vec_iter == uc_vec.end())
      {
        throw "IOException";
      }
      str.push_back(*uc_vec_iter);
      uc_vec_iter++;
    }
    return str;
  }
};
#endif