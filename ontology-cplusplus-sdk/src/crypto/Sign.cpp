#include "Sign.h"

bool Sign::md_ctx_sign_init(const SignatureScheme sign_scheme,
                            EVP_MD_CTX *md_ctx) {
  // EVP_MD_CTX_init(md_ctx);
  switch (sign_scheme) {
  case SHA224withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha224(), NULL))) {
      return false;
    }
    break;
  case SHA256withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha256(), NULL))) {
      return false;
    }
    break;
  case SHA384withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha384(), NULL))) {
      return false;
    }
    break;
  case SHA512withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha512(), NULL))) {
      return false;
    }
    break;
  case SHA3_224withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_224(), NULL))) {
      return false;
    }
    break;
  case SHA3_256withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_256(), NULL))) {
      return false;
    }
    break;
  case SHA3_384withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_384(), NULL))) {
      return false;
    }
    break;
  case SHA3_512withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_512(), NULL))) {
      return false;
    }
    break;
  case RIPEMD160withECDSA:
    if (!(EVP_DigestInit_ex(md_ctx, EVP_ripemd160(), NULL))) {
      return false;
    }
    break;
  default:
    return false;
  }
  return true;
}

bool Sign::md_ctx_digest_init(const SignatureScheme sign_scheme,
                              EVP_MD_CTX *md_ctx) {
  EVP_MD_CTX_init(md_ctx);
  switch (sign_scheme) {
  case SHA224withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha224(), NULL) != 1) {
      return false;
    }
    break;
  case SHA256withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL) != 1) {
      return false;
    }
    break;
  case SHA384withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha384(), NULL) != 1) {
      return false;
    }
    break;
  case SHA512withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha512(), NULL) != 1) {
      return false;
    }
    break;
  case SHA3_224withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha3_224(), NULL) != 1) {
      return false;
    }
    break;
  case SHA3_256withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha3_256(), NULL) != 1) {
      return false;
    }
    break;
  case SHA3_384withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha3_384(), NULL) != 1) {
      return false;
    }
    break;
  case SHA3_512withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha3_512(), NULL) != 1) {
      return false;
    }
    break;
  case RIPEMD160withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_ripemd160(), NULL) != 1) {
      return false;
    }
    break;
  default:
    return false;
  }
  return true;
}

bool Sign::md_ctx_veri_init(const SignatureScheme sign_scheme,
                            EVP_MD_CTX *md_ctx) {
  EVP_MD_CTX_init(md_ctx);
  switch (sign_scheme) {
  case SHA224withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha224(), NULL))) {
      return false;
    }
    break;
  case SHA256withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha256(), NULL))) {
      return false;
    }
    break;
  case SHA384withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha384(), NULL))) {
      return false;
    }
    break;
  case SHA512withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha512(), NULL))) {
      return false;
    }
    break;
  case SHA3_224withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_224(), NULL))) {
      return false;
    }
    break;
  case SHA3_256withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_256(), NULL))) {
      return false;
    }
    break;
  case SHA3_384withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_384(), NULL))) {
      return false;
    }
    break;
  case SHA3_512withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_512(), NULL))) {
      return false;
    }
    break;
  case RIPEMD160withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_ripemd160(), NULL))) {
      return false;
    }
    break;
  default:
    return false;
  }
  return true;
}

// bool Sign::sign_hash(const std::string &msg, EVP_MD_CTX *md_ctx,
//                      string &str_dgst) {
//   size_t len;
//   unsigned char uc_dgst[EVP_MAX_MD_SIZE];
//   unsigned int dgstlen = (unsigned int)sizeof(uc_dgst);
//   if (!EVP_DigestUpdate(md_ctx, msg.c_str(), len)) {
//     EVP_MD_CTX_free(md_ctx);
//   }
//   if (!EVP_DigestFinal_ex(md_ctx, uc_dgst, &dgstlen)) {
//     return false;
//   }
//   str_dgst = std::string(reinterpret_cast<char *>(uc_dgst));
//   EVP_MD_CTX_free(md_ctx);
//   return true;
// }

bool Sign::ECDSA_key_generate(CurveName curve_nid) {
  // EVP_PKEY_CTX *pk_ctx = NULL;
  // if(!(pk_ctx==EVP_PKEY_CTX_new(ENGINE_METHOD_DIGESTS)){
  //   return false;
  // }

  // EC_KEY *ec_key;
  // EC_GROUP *group;
  // group = EC_GROUP_new_by_curve_name(curve_nid);
  // if (group == NULL) {
  //   return false;
  // }
  EC_KEY *ec_key;
  ec_key = EC_KEY_new_by_curve_name(curve_nid);
  if (ec_key == NULL) {
    // EC_GROUP_free(group);
    return false;
  }

  // EC_GROUP_set_asn1_flag(group, OPENSSL_EC_NAMED_CURVE);

  // EC_KEY_set_asn1_flag(ec_key, OPENSSL_EC_NAMED_CURVE);

  // if (EC_KEY_set_group(ec_key, group) != 1) {
  //   EC_KEY_free(ec_key);
  //   // EC_GROUP_free(group);
  //   return false;
  // }
  if (EC_KEY_generate_key(ec_key) != 1) {
    EC_KEY_free(ec_key);
    // EC_GROUP_free(group);
    return false;
  }

  EVP_PKEY_assign_EC_KEY(key, ec_key);

  BIO *pri_bp = BIO_new_file("prikey.pem", "w");
  EVP_PKEY_print_private(pri_bp, key, 0, NULL);
  BIO_free_all(pri_bp);

  BIO *pub_bp = BIO_new_file("pubkey.pem", "w");
  EVP_PKEY_print_public(pub_bp, key, 0, NULL);
  BIO_free_all(pub_bp);
  // const BIGNUM *EC_KEY_get0_private_key(const EC_KEY *key);
  // int EC_KEY_set_private_key(EC_KEY * key, const BIGNUM *prv);
  // const EC_POINT *EC_KEY_get0_public_key(const EC_KEY *key);
  // int EC_KEY_set_public_key(EC_KEY * key, const EC_POINT *pub);

  // EC_KEY_free(ec_key);
  // EC_GROUP_free(group);
  return true;
}

bool Sign::EC_get_public_key(string &public_key) {
  // const EC_POINT *EC_KEY_get0_public_key(const EC_KEY *key);
  EC_KEY *ec_key = EVP_PKEY_get0_EC_KEY(key);
  if (ec_key == NULL) {
    return false;
  }
  EC_POINT *pub = NULL;
  pub = (EC_POINT *)EC_KEY_get0_public_key(ec_key);
  if (pub == NULL) {
    return false;
  }

  // char *EC_POINT_point2hex(const EC_GROUP *, const EC_POINT *,
  //                          point_conversion_form_t form, BN_CTX *);

  const EC_GROUP *group;
  group = EC_KEY_get0_group(ec_key);
  if (group == NULL) {
    return false;
  }
  public_key =
      EC_POINT_point2hex(group, pub, POINT_CONVERSION_COMPRESSED, NULL);
  if (public_key.length() == 0) {
    return false;
  }
  return true;
}

bool Sign::EC_set_public_key(const string &str_public_key,
                             CurveName curve_nid) {
  EC_GROUP *group;
  group = EC_GROUP_new_by_curve_name(curve_nid);
  if (group == NULL) {
    return false;
  }

  // EC_POINT *EC_POINT_hex2point(const EC_GROUP *, const char *, EC_POINT *,
  //                              BN_CTX *);
  EC_POINT *pub = NULL;
  EC_POINT_hex2point(group, str_public_key.c_str(), pub, NULL);

  EC_KEY *ec_key;
  ec_key = EC_KEY_new_by_curve_name(curve_nid);
  if (ec_key == NULL) {
    EC_GROUP_free(group);
    return false;
  }
  if (!EC_KEY_set_public_key(ec_key, pub)) {
    EC_KEY_free(ec_key);
    EC_GROUP_free(group);
    return false;
  }
  EVP_PKEY_assign_EC_KEY(key, ec_key);

  BIO *pub_bp = BIO_new_file("set_pubkey.pem", "w");
  EVP_PKEY_print_public(pub_bp, key, 0, NULL);
  BIO_free_all(pub_bp);

  // EC_KEY_free(ec_key);
  // EC_GROUP_free(group);
  return true;
}

bool Sign::EC_get_private_key(string &str_private_key) {
  // const EC_POINT *EC_KEY_get0_public_key(const EC_KEY *key);
  EC_KEY *tmp_ec_key = EVP_PKEY_get0_EC_KEY(key);
  if (tmp_ec_key == NULL) {
    return false;
  }

  const BIGNUM *prv;
  prv = EC_KEY_get0_private_key(tmp_ec_key);

  if (!prv) {
    EC_KEY_free(tmp_ec_key);
    return false;
  }

  str_private_key = BN_bn2hex(prv);
  return true;
}

bool Sign::EC_set_private_key(const string &str_private_key,
                              CurveName curve_nid) {
  EC_GROUP *group;
  group = EC_GROUP_new_by_curve_name(curve_nid);
  if (group == NULL) {
    return false;
  }

  // EC_POINT *EC_POINT_hex2point(const EC_GROUP *, const char *, EC_POINT *,
  //                              BN_CTX *);
  // EC_POINT *pub = NULL;
  // EC_POINT_hex2point(group, str_private_key.c_str(), pub, NULL);
  EC_KEY *ec_key;
  ec_key = EC_KEY_new_by_curve_name(curve_nid);
  if (ec_key == NULL) {
    EC_GROUP_free(group);
    return false;
  }
  BIGNUM *prv = BN_new();
  BN_hex2bn(&prv, str_private_key.c_str());
  if (!EC_KEY_set_private_key(ec_key, prv)) {
    EC_KEY_print_fp(stdout, ec_key, 0);
    EC_KEY_free(ec_key);
    EC_GROUP_free(group);
    return false;
  }
  EVP_PKEY_assign_EC_KEY(key, ec_key);

  BIO *pri_bp = BIO_new_file("set_prikey.pem", "w");
  EVP_PKEY_print_private(pri_bp, key, 0, NULL);
  BIO_free_all(pri_bp);

  // EC_KEY_free(ec_key);
  // EC_GROUP_free(group);
  return true;
}

bool Sign::EC_get_pubkey_by_prikey(const string &str_private_key,
                                   string &str_public_key,
                                   CurveName curve_nid) {
  BIGNUM *prv = BN_new();
  BN_hex2bn(&prv, str_private_key.c_str());

  // string str;
  // cout << str_private_key << endl;
  // str = BN_bn2hex(prv);
  // cout << str << endl;

  EC_KEY *tmp_ec_key = EC_KEY_new_by_curve_name(curve_nid);
  const EC_GROUP *group;
  group = EC_KEY_get0_group(tmp_ec_key);
  EC_KEY_set_private_key(tmp_ec_key, prv);
  const EC_POINT *p2 = EC_GROUP_get0_generator(group);
  cout << "EC_POINT_point2hex:\n"
       << EC_POINT_point2hex(group, p2, POINT_CONVERSION_COMPRESSED, NULL)
       << endl;

  BIGNUM *p = BN_new();
  BIGNUM *a = BN_new();
  BIGNUM *b = BN_new();
  EC_GROUP_get_curve_GFp(group, p, a, b, NULL);
  cout << "p:" << BN_bn2hex(p) << endl;
  cout << "a:" << BN_bn2hex(a) << endl;
  cout << "b:" << BN_bn2hex(b) << endl;

  const BIGNUM *bn = EC_GROUP_get0_order(group);
  cout << "BN_bn2hex(bn): \n" << BN_bn2hex(bn) << endl;

  EC_POINT *pub = EC_POINT_new(group);
  BN_CTX *ctx;
  ctx = BN_CTX_new();
  if (EC_POINT_mul(group, pub, prv, NULL, NULL, ctx) != 1) {
    return false;
  }

  EC_KEY_set_public_key(tmp_ec_key, pub);
  str_public_key =
      EC_POINT_point2hex(group, pub, POINT_CONVERSION_COMPRESSED, ctx);
  return true;
}

bool Sign::EC_sign(const std::string &msg, std::string &str_sign_dgst,
                   SignatureScheme sign_scheme) {

  EVP_MD_CTX *md_ctx;
  md_ctx = EVP_MD_CTX_new();
  if (md_ctx == NULL) {
    return false;
  }

  if (md_ctx_sign_init(sign_scheme, md_ctx) != 1) {
    return false;
  }

  // sign_hash(msg, md_ctx, str_dgst);
  if (EVP_SignUpdate(md_ctx, (unsigned char *)msg.c_str(), msg.length()) != 1) {
    return false;
  }

  // unsigned int evp_key_size = EVP_PKEY_size(key);
  // char *uc_sign_dgst = (char *)malloc(evp_key_size + 1);

  // BIO *bp = BIO_new_file("prikey.pem", "w");
  // EVP_PKEY_print_private(bp, key, 0, NULL);
  // BIO_free_all(bp);

  unsigned int slen;
  if (EVP_SignFinal(md_ctx, NULL, &slen, key) != 1) {
    return false;
  }
  cout << "slen: " << slen << endl;
  char *uc_sign_dgst = (char *)malloc(slen);
  if (EVP_SignFinal(md_ctx, (unsigned char *)uc_sign_dgst, &slen, key) != 1) {
    return false;
  }
  cout << uc_sign_dgst << endl;
  cout << "slen: " << slen << endl;
  cout << "strlen(uc_sign_dgst): " << (unsigned)strlen(uc_sign_dgst) << endl;
  str_sign_dgst = std::string(reinterpret_cast<char *>(uc_sign_dgst));
  cout << str_sign_dgst << endl;
  cout << "str_sign_dgst:" << str_sign_dgst.length() << endl;
  return true;
}

bool Sign::EC_veri(const std::string &msg, std::string &str_sign_dgst,
                   SignatureScheme sign_scheme) {
  EVP_MD_CTX *md_ctx;
  md_ctx = EVP_MD_CTX_new();
  if (md_ctx == NULL) {
    return false;
  }

  if ((md_ctx_veri_init(sign_scheme, md_ctx)) != 1) {
    return false;
  }
  // sign_hash(msg, md_ctx, str_dgst);
  cout << "EC_veri msg.c_str():" << msg.c_str() << endl;
  cout << "EC_veri msg.length():" << msg.length() << endl;
  if (EVP_VerifyUpdate(md_ctx, (unsigned char *)msg.c_str(), msg.length()) !=
      1) {
    return false;
  }

  cout << "EC_veri str_sign_dgst.c_str():" << str_sign_dgst.c_str() << endl;
  cout << "EC_veri str_sign_dgst.length():" << str_sign_dgst.length() << endl;
  // unsigned int evp_key_size = EVP_PKEY_size(key);
  // char *uc_sign_dgst = (char *)malloc(evp_key_size + 1);
  int ret;
  ret = EVP_VerifyFinal(md_ctx, (unsigned char *)str_sign_dgst.c_str(),
                        str_sign_dgst.length(), key);
  cout << "EC_veri EVP_VerifyFinal(): " << ret << endl;
  if (ret != 1) {
    return false;
  }
  return true;
}