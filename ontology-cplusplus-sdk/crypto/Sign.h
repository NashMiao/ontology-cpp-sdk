#ifndef SIGN_H
#define SIGN_H

#include <openssl/bio.h>
#include <openssl/conf.h>
#include <openssl/ec.h>    // for EC_GROUP_new_by_curve_name, EC_GROUP_free, EC_KEY_new, EC_KEY_set_group, EC_KEY_generate_key, EC_KEY_free
#include <openssl/ecdsa.h> // for ECDSA_do_sign, ECDSA_do_verify
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/obj_mac.h> // for NID_secp192k1
#include <openssl/pem.h>

#include <cstring>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

enum SignatureScheme {
  SHA224withECDSA,
  SHA256withECDSA,
  SHA384withECDSA,
  SHA512withECDSA,
  SHA3_224withECDSA,
  SHA3_256withECDSA,
  SHA3_384withECDSA,
  SHA3_512withECDSA,
  RIPEMD160withECDSA,
  SM3withSM2
};

enum CurveName {
  p224 = NID_secp224k1,
  p256 = NID_X9_62_prime256v1,
  p384 = NID_secp384r1,
  p521 = NID_secp521r1,
  SM2P256V1 = NID_sm2
};

/* some tests from the X9.62 draft */
// int x9_62_test_internal(BIO *out, int nid, const char *r_in, const char
// *s_in) {
//   int ret = 0;
//   const char message[] = "abc";
//   unsigned char digest[20];
//   unsigned int dgst_len = 0;
//   EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
//   EC_KEY *key = NULL;
//   ECDSA_SIG *signature = NULL;
//   BIGNUM *r = NULL, *s = NULL;
//   BIGNUM *kinv = NULL, *rp = NULL;
//   const BIGNUM *sig_r, *sig_s;

//   if (md_ctx == NULL)
//     goto x962_int_err;

//   /* get the message digest */
//   if (!EVP_DigestInit(md_ctx, EVP_sha1()) ||
//       !EVP_DigestUpdate(md_ctx, (const void *)message, 3) ||
//       !EVP_DigestFinal(md_ctx, digest, &dgst_len))
//     goto x962_int_err;

//   BIO_printf(out, "testing %s: ", OBJ_nid2sn(nid));
//   /* create the key */
//   if ((key = EC_KEY_new_by_curve_name(nid)) == NULL)
//     goto x962_int_err;
//   use_fake = 1;
//   if (!EC_KEY_generate_key(keify))
//     goto x962_int_err;
//   BIO_printf(out, ".");
//   (void)BIO_flush(out);
//   /* create the signature */
//   use_fake = 1;
//   /* Use ECDSA_sign_setup to avoid use of ECDSA nonces */
//   if (!ECDSA_sign_setup(key, NULL, &kinv, &rp))
//     goto x962_int_err;
//   signature = ECDSA_do_sign_ex(digest, 20, kinv, rp, key);
//   if (signature == NULL)
//     goto x962_int_err;
//   BIO_printf(out, ".");
//   (void)BIO_flush(out);
//   /* compare the created signature with the expected signature */
//   if ((r = BN_new()) == NULL || (s = BN_new()) == NULL)
//     goto x962_int_err;
//   if (!BN_dec2bn(&r, r_in) || !BN_dec2bn(&s, s_in))
//     goto x962_int_err;
//   ECDSA_SIG_get0(signature, &sig_r, &sig_s);
//   if (BN_cmp(sig_r, r) || BN_cmp(sig_s, s))
//     goto x962_int_err;
//   BIO_printf(out, ".");
//   (void)BIO_flush(out);
//   /* verify the signature */
//   if (ECDSA_do_verify(digest, 20, signature, key) != 1)
//     goto x962_int_err;
//   BIO_printf(out, ".");
//   (void)BIO_flush(out);

//   BIO_printf(out, " ok\n");
//   ret = 1;
// x962_int_err:
//   if (!ret)
//     BIO_printf(out, " failed\n");
//   EC_KEY_free(key);
//   ECDSA_SIG_free(signature);
//   BN_free(r);
//   BN_free(s);
//   EVP_MD_CTX_free(md_ctx);
//   BN_clear_free(kinv);
//   BN_clear_free(rp);
//   return ret;
// }

// static int create_signature(unsigned char *hash) {
//   int function_status = -1;
//   EC_KEY *eckey = EC_KEY_new();
//   if (NULL == eckey) {
//     printf("Failed to create new EC Key\n");
//     function_status = -1;
//   } else {
//     EC_GROUP *ecgroup = EC_GROUP_new_by_curve_name(NID_secp192k1);
//     if (NULL == ecgroup) {
//       printf("Failed to create new EC Group\n");
//       function_status = -1;
//     } else {
//       int set_group_status = EC_KEY_set_group(eckey, ecgroup);
//       const int set_group_success = 1;
//       if (set_group_success != set_group_status) {
//         printf("Failed to set group for EC Key\n");
//         function_status = -1;
//       } else {
//         const int gen_success = 1;
//         int gen_status = EC_KEY_generate_key(eckey);
//         if (gen_success != gen_status) {
//           printf("Failed to generate EC Key\n");
//           function_status = -1;
//         } else {
//           ECDSA_SIG *signature = ECDSA_do_sign(hash, strlen(hash), eckey);
//           if (NULL == signature) {
//             printf("Failed to generate EC Signature\n");
//             function_status = -1;
//           } else {

//             int verify_status =
//                 ECDSA_do_verify(hash, strlen(hash), signature, eckey);
//             const int verify_success = 1;
//             if (verify_success != verify_status) {
//               printf("Failed to verify EC Signature\n");
//               function_status = -1;
//             } else {
//               printf("Verifed EC Signature\n");
//               function_status = 1;
//             }
//           }
//         }
//       }
//       EC_GROUP_free(ecgroup);
//     }
//     EC_KEY_free(eckey);
//   }

//   return function_status;
// }

class Sign {
private:
  EVP_PKEY *key;
  bool md_ctx_sign_init(const SignatureScheme sign_scheme, EVP_MD_CTX *md_ctx);
  bool md_ctx_veri_init(const SignatureScheme sign_scheme, EVP_MD_CTX *md_ctx);
  bool md_ctx_digest_init(const SignatureScheme sign_scheme,
                          EVP_MD_CTX *md_ctx);
  // bool sign_hash(const std::string &msg, EVP_MD_CTX *md_ctx, string
  // &str_dgst);

public:
  Sign() { key = EVP_PKEY_new(); }
  ~Sign() { EVP_cleanup(); }

  bool ECDSA_key_generate(CurveName curve_nid = p256);
  bool EC_get_public_key(string &str_public_key);
  bool EC_set_public_key(const string &str_public_key, CurveName curve_nid);
  bool EC_get_private_key(string &str_private_key);
  bool EC_set_private_key(const string &str_private_key, CurveName curve_nid);
  bool EC_get_pubkey_by_prikey(const string &str_private_key,
                               string &str_public_key, CurveName curve_nid);
  bool EC_sign(const std::string &msg, std::string &str_sign_dgst,
               SignatureScheme sign_scheme = SHA256withECDSA);
  bool EC_veri(const std::string &msg, std::string &str_sign_dgst,
               SignatureScheme sign_scheme = SHA256withECDSA);

  bool SM_sign(const std::string &msg, std::string str_sign_dgst,
               SignatureScheme sign_scheme = SM3withSM2);
};

#endif