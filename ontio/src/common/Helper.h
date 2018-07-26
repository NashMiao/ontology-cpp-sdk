#ifndef HELPER_H
#define HELPER_H

#include <assert.h>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>

#include <boost/any.hpp>
#include <nlohmann/json.hpp>
#include <openssl/bio.h>
#include <openssl/bn.h>
#include <openssl/buffer.h>
#include <openssl/evp.h>


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
  static std::vector<unsigned char>
  addBytes(const std::vector<unsigned char> &data1,
           const std::vector<unsigned char> &data2) {
    std::vector<unsigned char> data3 = data1;
    data3.insert(data3.end(), data2.begin(), data2.end());
    return data3;
  }
  std::vector<unsigned char> addBytes(const unsigned char data1,
                                      const std::vector<unsigned char> &data2) {
    std::vector<unsigned char> data3;
    data3.push_back(data1);
    data3.insert(data3.end(), data2.begin(), data2.end());
    return data3;
  }

  static std::vector<unsigned char> hexStringToByte(std::string str) {
    size_t str_sz = str.size();
    if (str_sz % 2 != 0) {
      throw std::runtime_error("hexStringToByte error");
    }
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
      str.assign(str, 2, str.size() - 2);
      str_sz -= 2;
    }
    std::vector<unsigned char> byte_vec;
    for (size_t i = 0; i < str_sz; i += 2) {
      unsigned char uch;
      if ('a' <= str[i] && str[i] <= 'z') {
        uch = ((str[i] - 'a' + 10) << 4) & 0xF0;
      } else if ('A' <= str[i] && str[i] <= 'Z') {
        uch = ((str[i] - 'A' + 10) << 4) & 0xF0;
      } else if ('0' <= str[i] && str[i] <= '9') {
        uch = ((str[i] - '0') << 4) & 0xF0;
      } else {
        throw std::runtime_error("string isn't hexString.");
      }
      unsigned char ucl;
      if ('a' <= str[i + 1] && str[i + 1] <= 'z') {
        ucl = (str[i + 1] - 'a' + 10) & 0x0F;
      } else if ('A' <= str[i + 1] && str[i + 1] <= 'Z') {
        ucl = (str[i + 1] - 'A' + 10) & 0x0F;
      } else if ('0' <= str[i + 1] && str[i + 1] <= '9') {
        ucl = (str[i + 1] - '0') & 0x0F;
      } else {
        throw std::runtime_error("string isn't hexString.");
      }
      unsigned char uc = uch | ucl;
      byte_vec.push_back(uc);
    }
    return byte_vec;
  }

  static std::vector<unsigned char>
  hexVecToByte(const std::vector<unsigned char> &vec) {
    size_t vec_sz = vec.size();
    if (vec_sz % 2 != 0) {
      throw "hexStringToByte error";
    }
    std::vector<unsigned char> byte_vec;
    for (size_t i = 0; i < vec_sz; i += 2) {
      unsigned char uch;
      if ('a' <= vec[i] && vec[i] <= 'f') {
        uch = ((vec[i] - 'a' + 10) << 4) & 0xF0;
      } else if ('A' <= vec[i] && vec[i] <= 'F') {
        uch = ((vec[i] - 'A' + 10) << 4) & 0xF0;
      } else if ('0' <= vec[i] && vec[i] <= '9') {
        uch = ((vec[i] - '0') << 4) & 0xF0;
      } else {
        throw "unsigned char isn't hex!";
      }
      unsigned char ucl;
      if ('a' <= vec[i + 1] && vec[i + 1] <= 'f') {
        ucl = (vec[i + 1] - 'a' + 10) & 0x0F;
      } else if ('A' <= vec[i + 1] && vec[i + 1] <= 'F') {
        ucl = (vec[i + 1] - 'A' + 10) & 0x0F;
      } else if ('0' <= vec[i + 1] && vec[i + 1] <= '9') {
        ucl = (vec[i + 1] - '0') & 0x0F;
      } else {
        throw "unsigned char isn't hex!";
      }
      unsigned char uc = uch | ucl;
      byte_vec.push_back(uc);
    }
    return byte_vec;
  }

  static std::string toHexString(const std::vector<unsigned char> &value) {
    std::string hex_str;
    std::vector<unsigned char>::const_iterator value_cit;
    std::stringstream stream;
    stream << "0x";
    for (value_cit = value.cbegin(); value_cit != value.cend(); value_cit++) {
      stream << std::setfill('0') << std::setw(sizeof(unsigned char) * 2)
             << std::hex << (unsigned int)*value_cit;
    }
    std::string str = stream.str();
    return str;
  }

  static std::string toHexString(unsigned char *data, int len) {
    char hexmap[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                     '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    std::string s(len * 2, ' ');
    for (int i = 0; i < len; ++i) {
      s[2 * i] = hexmap[(data[i] & 0xF0) >> 4];
      s[2 * i + 1] = hexmap[data[i] & 0x0F];
    }
    return s;
  }

  static std::vector<unsigned char> hexToBytes(std::string value) {
    std::vector<unsigned char> ret_vec;
    if (value.empty()) {
      return ret_vec;
    }
    int len = value.length();
    if (len % 2 == 1) {
      throw "IllegalArgumentException";
    }
    size_t i = 0;
    while (i < value.size()) {
      i += 2;
      value.insert(i, 1, ' ');
      i += 1;
    }
    std::istringstream hex_chars_stream(value);
    unsigned int c;
    while (hex_chars_stream >> std::hex >> c) {
      ret_vec.push_back(c);
    }
    return ret_vec;
  }

  static std::vector<unsigned char> BigInt2Bytes(BIGNUM *bn) {
    std::vector<unsigned char> ret_vec;
    if (BN_is_zero(bn)) {
      return ret_vec;
    }
  }

  static bool DecodeBase58(const char *psz, std::vector<unsigned char> &vch) {
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

  static std::string EncodeBase58(const unsigned char *pbegin,
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

  static std::string EncodeBase58(const std::vector<unsigned char> &vch) {
    return EncodeBase58(vch.data(), vch.data() + vch.size());
  }

  static bool DecodeBase58(const std::string &str,
                           std::vector<unsigned char> &vchRet) {
    return DecodeBase58(str.c_str(), vchRet);
  }

  std::string Base64Encode(const char *input, int length, bool with_new_line) {
    BIO *bmem = NULL;
    BIO *b64 = NULL;
    BUF_MEM *bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    if (!with_new_line) {
      BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, input, length);
    // BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = 0;

    BIO_free_all(b64);

    return std::string(buff);
  }

  std::string Base64Decode(char *input, int length, bool with_new_line) {
    BIO *b64 = NULL;
    BIO *bmem = NULL;
    char *buffer = (char *)malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    if (!with_new_line) {
      BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new_mem_buf(input, length);
    bmem = BIO_push(b64, bmem);
    BIO_read(bmem, buffer, length);

    BIO_free_all(bmem);

    return std::string(buffer);
  }

  static std::string
  ToJSONString(std::unordered_map<std::string, std::string> uord_map) {
    std::unordered_map<std::string, std::string>::const_iterator uord_map_it;
    nlohmann::json json_uord_map;
    for (uord_map_it = uord_map.cbegin(); uord_map_it != uord_map.cend();
         uord_map_it++) {
      json_uord_map[uord_map_it->first] = uord_map_it->second;
    }
    std::string str_uord_map = json_uord_map.dump();
    return str_uord_map;
  }

  static std::string ToJSONString(std::map<std::string, std::string> str_map) {
    std::map<std::string, std::string>::const_iterator str_map_it;
    nlohmann::json json_str_map;
    for (str_map_it = str_map.cbegin(); str_map_it != str_map.cend();
         str_map_it++) {
      json_str_map[str_map_it->first] = str_map_it->second;
    }
    std::string str_strmap = json_str_map.dump();
    return str_strmap;
  }

  static std::string ToJSONString(std::map<std::string, boost::any> any_map) {
    std::map<std::string, boost::any>::const_iterator any_map_it;
    nlohmann::json json_any_map;
    for (any_map_it = any_map.cbegin(); any_map_it != any_map.cend();
         any_map_it++) {
      boost::any val = any_map_it->second;
      if (val.type() == typeid(bool)) {
        bool value = boost::any_cast<bool>(val);
        json_any_map[any_map_it->first] = value;
      } else if (val.type() == typeid(int)) {
        int value = boost::any_cast<int>(val);
        json_any_map[any_map_it->first] = value;
      } else if (val.type() == typeid(long long)) {
        long long value = boost::any_cast<long long>(val);
        json_any_map[any_map_it->first] = value;
      } else if (val.type() == typeid(std::string)) {
        std::string value = boost::any_cast<std::string>(val);
        json_any_map[any_map_it->first] = value;
      } else {
        throw "ToJSONString Unsupport Type";
      }
    }
    std::string str_anymap = json_any_map.dump();
    return str_anymap;
  }
};

#endif