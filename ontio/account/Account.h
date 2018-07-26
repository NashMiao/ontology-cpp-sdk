#ifndef ONTIO_ACCOUNT_ACCOUNT_H
#define ONTIO_ACCOUNT_ACCOUNT_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

#include <stdexcept>
#include <string>
#include <vector>

#include "../common/Address.h"
#include "../crypto/KeyType.h"
#include "../crypto/Signature.h"
#include "../crypto/SignatureHandler.h"
#include "../crypto/SignatureScheme.h"

class Account
{
private:
  std::string curveParams;
  std::string privateKey;
  std::string publicKey;
  KeyType keyType;
  Address addressU160;
  SignatureScheme signatureScheme;
  CurveName curveName;
  std::string sm2Param;

private:
  void parsePublicKey(const std::vector<unsigned char> &data)
  {
    if (data.size() == 0)
    {
      throw runtime_error(ErrorCode::StrNullInput);
    }
    if (data.size() < 2)
    {
      throw runtime_error(ErrorCode::StrInvalidData);
    }
    if (data.size() == 33)
    {
      keyType = KeyType::ECDSA;
    }
    else if (data.size() == 35)
    {
      keyType = KeyTypeMethod::fromLabel(data[0]);
    }
    switch (keyType)
    {
    case KeyType::ECDSA:
    {
      curveParams = CurveNameMethod::toString(CurveName::p256);
      break;
    }
    case KeyType::SM2:
      break;
    default:
      break;
    }
  }

public:
  Account() {}

  Account(SignatureScheme scheme)
  {
    addressU160 = Address::addressFromPubKey(serializePublicKey());
  }

  explicit Account(std::string private_key,
                   SignatureScheme scheme = SignatureScheme::SHA256withECDSA,
                   CurveName _curve_name = CurveName::p256,
                   std::string sm2_param = "")
      : privateKey(private_key), signatureScheme(scheme),
        curveName(_curve_name), sm2Param(sm2_param)
  {
    signatureScheme = scheme;
    if (signatureScheme == SignatureScheme::SM3withSM2)
    {
      keyType = KeyType::SM2;
    }
    else if (signatureScheme == SignatureScheme::SHA256withECDSA)
    {
      keyType = KeyType::ECDSA;
    }
    else
    {
      throw std::runtime_error("SignatureScheme Error!");
    }
    switch (signatureScheme)
    {
    case SignatureScheme::SHA256withECDSA:
    {
      privateKey = private_key;
      publicKey = Signature::EC_get_pubkey_by_prikey(privateKey, curveName);
      // ec_key = ec_sign.get_EC_key();
      std::vector<unsigned char> uc_pub_key;
      uc_pub_key = serializePublicKey();
      addressU160 = Address::addressFromPubKey(uc_pub_key);
      break;
    }
    case SignatureScheme::SM3withSM2:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA224withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA384withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA512withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_224withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_256withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_384withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_512withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::RIPEMD160withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    default:
    {
      throw "Exception(ErrorCode.UnsupportedKeyType)";
    }
    }
  }

  // construct an account from a serialized pubic key or private key
  Account(bool fromPrivate, std::vector<unsigned char> pubkey)
  {
    if (fromPrivate)
    {
      // parsePrivateKey(data);
    }
    else
    {
      parsePublicKey(pubkey);
    }
  }

  ~Account() {}

  Account operator=(Account &acct)
  {
    this->curveParams = acct.curveParams;
    this->privateKey = acct.privateKey;
    this->publicKey = acct.publicKey;
    this->keyType = acct.keyType;
    this->addressU160 = acct.addressU160;
    this->signatureScheme = acct.signatureScheme;
    this->curveName = acct.curveName;
    this->sm2Param = acct.sm2Param;
    return *this;
  }

  Account *operator=(Account *acct)
  {
    this->curveParams = acct->curveParams;
    this->privateKey = acct->privateKey;
    this->publicKey = acct->publicKey;
    this->keyType = acct->keyType;
    this->addressU160 = acct->addressU160;
    this->signatureScheme = acct->signatureScheme;
    this->curveName = acct->curveName;
    this->sm2Param = acct->sm2Param;
    return this;
  }

  bool equals(const Account &acct)
  {
    return this->addressU160.equals(acct.addressU160);
  }

  void setAccount(std::string private_key,
                  SignatureScheme scheme = SignatureScheme::SHA256withECDSA,
                  CurveName curveName = CurveName::p256)
  {
    signatureScheme = scheme;
    if (signatureScheme == SignatureScheme::SM3withSM2)
    {
      keyType = KeyType::SM2;
    }
    else if (signatureScheme == SignatureScheme::SHA256withECDSA)
    {
      keyType = KeyType::ECDSA;
    }
    else
    {
      throw "SignatureScheme Error!";
    }
    switch (signatureScheme)
    {
    case SignatureScheme::SHA256withECDSA:
    {
      privateKey = private_key;
      publicKey = Signature::EC_get_pubkey_by_prikey(privateKey, curveName);
      std::vector<unsigned char> uc_pub_key;
      uc_pub_key = serializePublicKey();
      addressU160 = Address::addressFromPubKey(uc_pub_key);
      break;
    }
    case SignatureScheme::SM3withSM2:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA224withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA384withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA512withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_224withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_256withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_384withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::SHA3_512withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    case SignatureScheme::RIPEMD160withECDSA:
    {
      throw std::runtime_error("SignatureScheme Unsupport");
      break;
    }
    default:
    {
      throw "Exception(ErrorCode.UnsupportedKeyType)";
    }
    }
  }

  Address getAddressU160() const { return addressU160; }

  SignatureScheme getSignatureScheme() { return signatureScheme; }

  CurveName getCurveName() { return curveName; }

  std::vector<unsigned char> generateSignature(std::vector<unsigned char> msg)
  {
    if (msg.empty())
    {
      throw new runtime_error(ErrorCode::StrInvalidMessage);
    }
    if (privateKey.empty())
    {
      throw new runtime_error(ErrorCode::StrWithoutPrivate);
    }
    if (signatureScheme == SignatureScheme::SM3withSM2)
    {
      if (sm2Param.empty())
      {
        sm2Param = "1234567812345678";
      }
    }
    std::vector<unsigned char> sign_data;
    SignatureHandler sign_handler(keyType, signatureScheme, curveName);
    sign_data = sign_handler.generateSignature(privateKey, msg, sm2Param);
    Signature signature(signatureScheme, sign_data, sm2Param);
    std::vector<unsigned char> uc_vec = signature.toBytes();
    return uc_vec;
  }

  std::vector<unsigned char> serializePublicKey() const
  {
    std::vector<unsigned char> act_uc_vec;
    switch (keyType)
    {
    case KeyType::ECDSA:
    {
      act_uc_vec = Helper::hexStringToByte(publicKey);
      break;
    }
    case KeyType::SM2:
    {
      throw std::runtime_error("Exception(KeyType::SM2)");
      break;
    }
    default:
    {
      throw runtime_error(ErrorCode::StrUnknownKeyType);
    }
    }

    return act_uc_vec;
  }

  std::vector<unsigned char> serializePrivateKey()
  {
    std::vector<unsigned char> act_uc_vec;
    switch (keyType)
    {
    case KeyType::ECDSA:
    case KeyType::SM2:
      act_uc_vec = Helper::hexStringToByte(publicKey);
      break;
    default:
      throw new std::runtime_error(ErrorCode::StrUnknownKeyType);
    }
    return act_uc_vec;
  }

  std::string serializePublicKey_str() const { return publicKey; }

  bool verifySignature(std::vector<unsigned char> msg,
                       std::vector<Signature> signature)
  {
    return true;
  }

  std::string exportWif()
  {
    std::vector<unsigned char> data;
    data[0] = (unsigned char)0x80;
    std::vector<unsigned char> prikey = serializePrivateKey();
    data.insert(data.end(), prikey.begin(), prikey.end());
    data[33] = (unsigned char)0x01;
    std::vector<unsigned char> checksum =
        Digest::hash256(data, 0, (int)data.size() - 4);
    data.insert(data.end(), checksum.begin(), checksum.begin() + 4);
    Helper::
    String wif = Base58.encode(data);
    Arrays.fill(data, (byte)0);
    return wif;
  }

  std::string exportCtrEncryptedPrikey(std::string passphrase, int n)
  {
    int N = n;
    int r = 8;
    int p = 8;
    int dkLen = 64;

    int salt_len = 4;
    unsigned char salt[] = {0xfa, 0xa4, 0x88, 0x3d};

    std::string hex_derivedkey;
    hex_derivedkey = hexStr(derivedkey, outlen);
    cout << hex_derivedkey << endl
         << hex_derivedkey.length() << endl;
    if (hex_derivedkey.empty())
    {
      return NULL;
    }

    // std::string str_derivedkey =
    //     std::string(reinterpret_cast<char *>(derivedkey));
    // cout << "str_derivedkey:\n"
    //      << str_derivedkey << endl
    //      << "outlen:" << outlen << endl
    //      << str_derivedkey.length() << endl;

    unsigned char uc_iv[AES_BLOCK_SIZE];
    unsigned char uc_key[AES_256_KEY_SIZE];
    memcpy(uc_iv, &derivedkey[0], AES_BLOCK_SIZE * sizeof(unsigned char));
    memcpy(uc_key, &derivedkey[32], AES_256_KEY_SIZE * sizeof(unsigned char));

    cout << "uc_iv:\n"
         << hexStr(uc_iv, 16) << endl
         << sizeof(uc_iv) << endl;
    cout << "uc_key:\n"
         << hexStr(uc_key, 32) << endl
         << sizeof(uc_key) << endl;

    AES aes;

    aes.set_params(uc_key, uc_iv, AEAD_mode::AES_CTR);

    unsigned char uc_private_key[] = {
        0xc1, 0x9f, 0x16, 0x78, 0x5b, 0x8f, 0x35, 0x43, 0xbb, 0xaf, 0x5e,
        0x1d, 0xbb, 0x5d, 0x39, 0x8d, 0xfa, 0x6c, 0x85, 0xaa, 0xad, 0x54,
        0xfc, 0x9d, 0x71, 0x20, 0x3c, 0xe8, 0x3e, 0x50, 0x5c, 0x07};

    cout << "uc_private_key:\n"
         << hexStr(uc_private_key, 32) << endl;
    // cout << "uc_private_key:\n"
    //      << uc_private_key << endl
    //      << sizeof(uc_private_key) << endl;

    // std::string private_key =
    // std::string(reinterpret_cast<char *>(uc_private_key));
    // std::string enc_private_key;

    cout << "aes.get_iv():\n"
         << hexStr(aes.get_iv(), 16) << endl;
    cout << "aes.get_key():\n"
         << hexStr(aes.get_key(), 32) << endl;

    int enc_private_key_sz = 32;
    unsigned char *enc_private_key = new unsigned char(enc_private_key_sz);
    aes.auth_encry(uc_private_key, enc_private_key);
    cout << "enc_private_key:\n"
         << enc_private_key << endl;
    string str_enc_private_key;
    // str_enc_private_key = hexStr(enc_private_key, 48);
    // cout << "str_enc_private_key:\n" << str_enc_private_key << endl;
    // cout << Base64Encode(str_enc_private_key.c_str(),
    //                      str_enc_private_key.length(), false)
    //      << endl;
    cout << "base64(enc_private_key, 48):\n"
         << base64(enc_private_key, enc_private_key_sz) << endl;

    char test_key[] = "3JZLD/X45qSFjmRRvRVhcEjKgCJQDPWOsjx2dcTEj58=";
    int o_l;
    unsigned char *uc_tset_key = unbase64(test_key, 45, &o_l);

    cout << "test_key:\n"
         << unbase64(test_key, 45, &o_l) << endl;

    cout << hexStr(enc_private_key, 48) << endl;
    cout << hexStr(uc_tset_key, 48) << endl;

    EVP_PKEY_CTX_free(pctx);

    return "test";
  }

  std::string exportGcmEncryptedPrikey(std::string passphrase,
                                       std::vector<unsigned char> salt,
                                       const int n) throw SDKException
  {
    int r = 8;
    int p = 8;
    int dkLen = 64;
    if (salt.size() != 16)
    {
      throw new SDKException(ErrorCode.ParamError);
    }
    Security.addProvider(new BouncyCastleProvider());
    byte[] derivedkey = SCrypt.generate(
        passphrase.getBytes(StandardCharsets.UTF_8), salt, N, r, p, dkLen);
    byte[] derivedhalf2 = new byte[32];
    byte[] iv = new byte[12];
    System.arraycopy(derivedkey, 0, iv, 0, 12);
    System.arraycopy(derivedkey, 32, derivedhalf2, 0, 32);
    try
    {
      SecretKeySpec skeySpec = new SecretKeySpec(derivedhalf2, "AES");
      Cipher cipher = Cipher.getInstance("AES/GCM/NoPadding");
      cipher.init(Cipher.ENCRYPT_MODE, skeySpec, new GCMParameterSpec(128, iv));
      cipher.updateAAD(getAddressU160().toBase58().getBytes());
      byte[] encryptedkey = cipher.doFinal(serializePrivateKey());
      return new String(Base64.getEncoder().encode(encryptedkey));
    }
    catch (Exception e)
    {
      e.printStackTrace();
      throw new SDKException(ErrorCode.EncriptPrivateKeyError);
    }
  }
};

#endif