#include "Signature.h"

Signature::Signature(SignatureScheme _scheme, CurveName _curve,
                     std::string private_key, std::string msg) {
  scheme = _scheme;
  curve = _curve;
  if (scheme == SignatureScheme::SHA224withECDSA ||
      scheme == SignatureScheme::SHA256withECDSA ||
      scheme == SignatureScheme::SHA384withECDSA ||
      scheme == SignatureScheme::SHA512withECDSA ||
      scheme == SignatureScheme::SHA3_224withECDSA ||
      scheme == SignatureScheme::SHA3_256withECDSA ||
      scheme == SignatureScheme::SHA3_384withECDSA ||
      scheme == SignatureScheme::SHA3_512withECDSA ||
      scheme == SignatureScheme::RIPEMD160withECDSA) {
    EC_set_private_key(private_key, curve);
    std::string str_sign_dgst;
    EC_sign(msg, str_sign_dgst, scheme);
    std::string utf8_str(str_sign_dgst);
    value.erase();
    value.assign((unsigned char *)str.c_str());
  } else if (scheme == SignatureScheme::SM3withSM2) {
    throw "scheme == SignatureScheme::SM3withSM2";
  } else {
    throw "unknown SignatureScheme";
  }
}

bool Signature::EC_init(CurveName curve_nid) {
  ec_key = EC_KEY_new_by_curve_name(curve_nid);

  return true;
}

bool Signature::md_ctx_sign_init(const SignatureScheme sign_scheme,
                                 EVP_MD_CTX *md_ctx) {
  EVP_MD_CTX_init(md_ctx);
  switch (sign_scheme) {
  case SignatureScheme::SHA224withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha224(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA256withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha256(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA384withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha384(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA512withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha512(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_224withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_224(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_256withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_256(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SignatureScheme::SHA3_384withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_384(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_512withECDSA:
    if (!(EVP_SignInit_ex(md_ctx, EVP_sha3_512(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::RIPEMD160withECDSA:
    if (!(EVP_DigestInit_ex(md_ctx, EVP_ripemd160(), NULL))) {
      return false;
    }
    break;
  default:
    return false;
  }
  return true;
}

bool Signature::md_ctx_digest_init(const SignatureScheme sign_scheme,
                                   EVP_MD_CTX *md_ctx) {
  EVP_MD_CTX_init(md_ctx);
  switch (sign_scheme) {
  case SignatureScheme::SHA224withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha224(), NULL) != 1) {
      return false;
    }
    break;
  case SignatureScheme::SHA256withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha256(), NULL) != 1) {
      return false;
    }
    break;
  case SignatureScheme::SHA384withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha384(), NULL) != 1) {
      return false;
    }
    break;
  case SignatureScheme::SHA512withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha512(), NULL) != 1) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_224withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha3_224(), NULL) != 1) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_256withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha3_256(), NULL) != 1) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_384withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha3_384(), NULL) != 1) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_512withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_sha3_512(), NULL) != 1) {
      return false;
    }
    break;
  case SignatureScheme::RIPEMD160withECDSA:
    if (EVP_DigestInit_ex(md_ctx, EVP_ripemd160(), NULL) != 1) {
      return false;
    }
    break;
  default:
    return false;
  }
  return true;
}

bool Signature::md_ctx_veri_init(const SignatureScheme sign_scheme,
                                 EVP_MD_CTX *md_ctx) {
  EVP_MD_CTX_init(md_ctx);
  switch (sign_scheme) {
  case SignatureScheme::SHA224withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha224(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA256withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha256(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA384withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha384(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA512withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha512(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_224withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_224(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_256withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_256(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_384withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_384(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::SHA3_512withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_sha3_512(), NULL))) {
      return false;
    }
    break;
  case SignatureScheme::RIPEMD160withECDSA:
    if (!(EVP_VerifyInit_ex(md_ctx, EVP_ripemd160(), NULL))) {
      return false;
    }
    break;
  default:
    return false;
  }
  return true;
}

bool Signature::ECDSA_key_generate(CurveName curve_nid) {

  EVP_PKEY_CTX *pctx, *kctx;
  EVP_PKEY *pkey = NULL, *params = NULL;

  /* Create the context for parameter generation */
  if (NULL == (pctx = EVP_PKEY_CTX_new_id(EVP_PKEY_EC, NULL))) {
    return false;
  }

  /* Initialise the parameter generation */
  if (1 != EVP_PKEY_paramgen_init(pctx)) {
    return false;
  }

  if (1 != EVP_PKEY_CTX_set_ec_paramgen_curve_nid(pctx, curve_nid)) {
    return false;
  }

  /* Create the parameter object params */
  if (!EVP_PKEY_paramgen(pctx, &params)) {
    return false;
  }

  /* Create the context for the key generation */
  if (NULL == (kctx = EVP_PKEY_CTX_new(params, NULL))) {
    return false;
  }

  /* Generate the key */
  if (1 != EVP_PKEY_keygen_init(kctx)) {
    return false;
  }
  if (1 != EVP_PKEY_keygen(kctx, &pkey)) {
    return false;
  }

  key = pkey;
  return true;
}

bool Signature::EC_get_public_key(string &public_key) {
  EC_KEY *ec_key = EVP_PKEY_get0_EC_KEY(key);
  if (ec_key == NULL) {
    return false;
  }
  EC_POINT *pub = NULL;
  pub = (EC_POINT *)EC_KEY_get0_public_key(ec_key);
  if (pub == NULL) {
    return false;
  }

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

bool Signature::EC_get_private_key(string &str_private_key) {
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

bool Signature::EC_set_public_key(const string &str_public_key,
                                  CurveName curve_nid) {
  EC_GROUP *group;
  group = EC_GROUP_new_by_curve_name(curve_nid);
  if (group == NULL) {
    return false;
  }

  EC_POINT *pub;
  pub = EC_POINT_new(group);
  pub = EC_POINT_hex2point(group, str_public_key.c_str(), NULL, NULL);

  if (ec_key == NULL) {
    EC_GROUP_free(group);
    return false;
  }
  if (EC_KEY_set_public_key(ec_key, pub) != 1) {
    EC_KEY_free(ec_key);
    EC_GROUP_free(group);
    return false;
  }
  return true;
}

bool Signature::EC_set_private_key(const string &str_private_key,
                                   CurveName curve_nid) {
  EC_GROUP *group;
  group = EC_GROUP_new_by_curve_name(curve_nid);
  if (group == NULL) {
    return false;
  }

  if (ec_key == NULL) {
    EC_GROUP_free(group);
    return false;
  }
  BIGNUM *prv = BN_new();
  BN_hex2bn(&prv, str_private_key.c_str());
  if (EC_KEY_set_private_key(ec_key, prv) != 1) {
    EC_KEY_free(ec_key);
    EC_GROUP_free(group);
    return false;
  }
  return true;
}

bool Signature::EC_set_key(const string &str_public_key,
                           const string &str_private_key, CurveName curve_nid) {
  bool ret;
  ret = EC_set_public_key(str_public_key, curve_nid);
  ret = ret && EC_set_private_key(str_private_key, curve_nid);
  ret = ret && EVP_PKEY_assign_EC_KEY(key, ec_key);
  return ret;
}

bool Signature::EC_get_pubkey_by_prikey(const string &str_private_key,
                                        string &str_public_key,
                                        CurveName curve_nid) {
  BIGNUM *prv = BN_new();
  BN_hex2bn(&prv, str_private_key.c_str());

  EC_KEY *ec_key;
  ec_key = EC_KEY_new_by_curve_name(curve_nid);
  if (ec_key == NULL) {
    return false;
  }

  const EC_GROUP *group;
  group = EC_GROUP_new_by_curve_name(curve_nid);
  EC_KEY_set_private_key(ec_key, prv);

  EC_POINT *pub;
  pub = EC_POINT_new(group);

  BN_CTX *bn_ctx;
  bn_ctx = BN_CTX_new();
  if (EC_POINT_mul(group, pub, prv, NULL, NULL, bn_ctx) != 1) {
    return false;
  }

  EC_KEY_set_public_key(ec_key, pub);
  if (EC_KEY_set_public_key(ec_key, pub) != 1) {
    EC_KEY_free(ec_key);
    return false;
  }
  str_public_key =
      EC_POINT_point2hex(group, pub, POINT_CONVERSION_COMPRESSED, bn_ctx);
  return true;
}

bool Signature::EC_sign(const std::string &msg, std::string &str_sign_dgst,
                        SignatureScheme sign_scheme) {

  EVP_MD_CTX *md_ctx;
  md_ctx = EVP_MD_CTX_new();
  if (md_ctx == NULL) {
    return false;
  }

  if (md_ctx_sign_init(sign_scheme, md_ctx) != 1) {
    return false;
  }

  if (EVP_SignUpdate(md_ctx, (unsigned char *)msg.c_str(), msg.length()) != 1) {
    return false;
  }
  unsigned int slen = 0;
  char *uc_sign_dgst = (char *)malloc(EVP_MAX_MD_SIZE);
  while (slen != strlen(uc_sign_dgst)) {
    if (EVP_SignFinal(md_ctx, (unsigned char *)uc_sign_dgst, &slen, key) != 1) {
      return false;
    }
  }

  str_sign_dgst = std::string(reinterpret_cast<char *>(uc_sign_dgst));
  return true;
}

bool Signature::EC_veri(const std::string &msg, std::string &str_sign_dgst,
                        SignatureScheme sign_scheme) {
  EVP_MD_CTX *md_ctx;
  md_ctx = EVP_MD_CTX_new();
  if (md_ctx == NULL) {
    return false;
  }

  if ((md_ctx_veri_init(sign_scheme, md_ctx)) != 1) {
    return false;
  }

  if (EVP_VerifyUpdate(md_ctx, (unsigned char *)msg.c_str(), msg.length()) !=
      1) {
    return false;
  }

  int ret;
  ret = EVP_VerifyFinal(md_ctx, (unsigned char *)str_sign_dgst.c_str(),
                        str_sign_dgst.length(), key);

  if (ret != 1) {
    return false;
  }
  return true;
}