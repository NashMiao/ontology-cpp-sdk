#ifndef ECC_H
#define ECC_H

#include <openssl/ec.h>

class ECC {
public:
  static int compare(EC_POINT *a, EC_POINT *b) {
    if (a == b) {
      return 0;
    }
    int result = 0;
    // TODO
    return result;
  }
};

#endif