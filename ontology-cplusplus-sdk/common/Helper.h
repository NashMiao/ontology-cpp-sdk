#ifndef HELPER_H
#define HELPER_H

#include <assert.h>
#include <iomanip>
#include <openssl/bn.h>
#include <sstream>
#include <string.h>
#include <string>
#include <vector>

/** All alphanumeric characters except for "0", "I", "O", and "l" */
static const char *pszBase58 =
    "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";
static const int8_t mapBase58[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0,  1,  2,  3,  4,  5,  6,  7,
    8,  -1, -1, -1, -1, -1, -1, -1, 9,  10, 11, 12, 13, 14, 15, 16, -1, 17, 18,
    19, 20, 21, -1, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, -1, -1, -1, -1,
    -1, -1, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, -1, 44, 45, 46, 47, 48,
    49, 50, 51, 52, 53, 54, 55, 56, 57, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

class Helper {
public:
  std::vector<unsigned char> addBytes(const std::vector<unsigned char> &data1,
                                      const std::vector<unsigned char> &data2) {
    std::vector<unsigned char> data3 = data1;
    data3.insert(data3.end(), data2, begin(), data2.end());
    return data3;
  }
  std::vector<unsigned char> addBytes(const unsigned char data1,
                                      const std::vector<unsigned char> &data2) {
    std::vector<unsigned char> data3;
    data3.push_back(data1);
    data3.insert(data3.end(), data2, begin(), data2.end());s
    return data3;
  }

  std::string toHexString(const std::vector<unsigned char> &value) {
    std::string hex_str;
    std::vector<unsigned char>::const_iterator value_cit;
    std::stringstream stream;
    stream << "0x";
    for (value_cit = value.cbegin(); value_cit != value.cend(); value_cit++) {
      stream << std::setfill('0') << std::setw(sizeof(unsigned char) * 2)
             << std::hex << (unsigned int)*value_cit;
    }
    return stream.str();
  }

  std::vector<unsigned char> hexToBytes(std::string value) {
    std::vector<unsigned char> ret_vec;
    if (value.empty()) {
      return ret_vec;
    }
    int len = value.length();
    if (len % 2 == 1) {
      throw "IllegalArgumentException";
    }
    len /= 2;
    for (int i = 0; i < len; i += 2) {
      ret_vec.push_back(
          (((unsigned char)value[i] << 4) && (unsigned char)value[i + 1]));
    }
    return ret_vec;
  }

  std::vector<unsigned char> BigInt2Bytes(BIGNUM *bn) {
    std::vector<unsigned char> ret_vec;
    if (BN_is_zero(bn)) {
      return ret_vec;
    }
  }

  bool DecodeBase58(const char *psz, std::vector<unsigned char> &vch) {
    // Skip leading spaces.
    while (*psz && isspace(*psz))
      psz++;
    // Skip and count leading '1's.
    int zeroes = 0;
    int length = 0;
    while (*psz == '1') {
      zeroes++;
      psz++;
    }
    // Allocate enough space in big-endian base256 representation.
    int size = strlen(psz) * 733 / 1000 + 1; // log(58) / log(256), rounded up.
    std::vector<unsigned char> b256(size);
    // Process the characters.
    static_assert(
        sizeof(mapBase58) / sizeof(mapBase58[0]) == 256,
        "mapBase58.size() should be 256"); // guarantee not out of range
    while (*psz && !isspace(*psz)) {
      // Decode base58 character
      int carry = mapBase58[(uint8_t)*psz];
      if (carry == -1) // Invalid b58 character
        return false;
      int i = 0;
      for (std::vector<unsigned char>::reverse_iterator it = b256.rbegin();
           (carry != 0 || i < length) && (it != b256.rend()); ++it, ++i) {
        carry += 58 * (*it);
        *it = carry % 256;
        carry /= 256;
      }
      assert(carry == 0);
      length = i;
      psz++;
    }
    // Skip trailing spaces.
    while (isspace(*psz))
      psz++;
    if (*psz != 0)
      return false;
    // Skip leading zeroes in b256.
    std::vector<unsigned char>::iterator it = b256.begin() + (size - length);
    while (it != b256.end() && *it == 0)
      it++;
    // Copy result into output vector.
    vch.reserve(zeroes + (b256.end() - it));
    vch.assign(zeroes, 0x00);
    while (it != b256.end())
      vch.push_back(*(it++));
    return true;
  }

  std::string EncodeBase58(const unsigned char *pbegin,
                           const unsigned char *pend) {
    // Skip & count leading zeroes.
    int zeroes = 0;
    int length = 0;
    while (pbegin != pend && *pbegin == 0) {
      pbegin++;
      zeroes++;
    }
    // Allocate enough space in big-endian base58 representation.
    int size =
        (pend - pbegin) * 138 / 100 + 1; // log(256) / log(58), rounded up.
    std::vector<unsigned char> b58(size);
    // Process the bytes.
    while (pbegin != pend) {
      int carry = *pbegin;
      int i = 0;
      // Apply "b58 = b58 * 256 + ch".
      for (std::vector<unsigned char>::reverse_iterator it = b58.rbegin();
           (carry != 0 || i < length) && (it != b58.rend()); it++, i++) {
        carry += 256 * (*it);
        *it = carry % 58;
        carry /= 58;
      }

      assert(carry == 0);
      length = i;
      pbegin++;
    }
    // Skip leading zeroes in base58 result.
    std::vector<unsigned char>::iterator it = b58.begin() + (size - length);
    while (it != b58.end() && *it == 0)
      it++;
    // Translate the result into a string.
    std::string str;
    str.reserve(zeroes + (b58.end() - it));
    str.assign(zeroes, '1');
    while (it != b58.end())
      str += pszBase58[*(it++)];
    return str;
  }

  std::string EncodeBase58(const std::vector<unsigned char> &vch) {
    return EncodeBase58(vch.data(), vch.data() + vch.size());
  }

  bool DecodeBase58(const std::string &str,
                    std::vector<unsigned char> &vchRet) {
    return DecodeBase58(str.c_str(), vchRet);
  }
};

#endif