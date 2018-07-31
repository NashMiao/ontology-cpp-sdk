#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <vector>
#include <string>

#include "crypto/AES.h"

int main()
{
    std::string plaintext_1 = "Hello world!";
    std::string key_1 = "SixteenbyteskeyplSixteenbyteskey";
    std::string iv_1 = "Firsttetbytesiv";
    std::string target_cipher_1 =
        "0x12c533d803a6bb9024ff8deb6849af1e465fc1414f0f60d86fd08c94";
    std::vector<unsigned char> byte_plaintext_1(plaintext_1.begin(),
                                                plaintext_1.end());
    std::vector<unsigned char> byte_key_1(key_1.begin(), key_1.end());
    std::vector<unsigned char> byte_iv_1(iv_1.begin(), iv_1.end());
    std::vector<unsigned char> encryptext_1;
    encryptext_1 =
        AES::gcmEncrypt(byte_plaintext_1, byte_key_1, byte_iv_1, false);

    std::vector<unsigned char> add;
    std::vector<unsigned char> encryptext_2;
    std::vector<unsigned char> tag;
    AES::encrypt(byte_plaintext_1, byte_plaintext_1, byte_key_1, byte_iv_1, encryptext_2, tag);
    std::cout << Helper::toHexString(encryptext_2) << std::endl;
    std::cout << Helper::toHexString(tag) << std::endl;
}