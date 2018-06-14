#ifndef ONTASSETTX_H
#define ONTASSETTX_H

#include <string>
#include "../../OntSdk.h"

class OntAssetTx
{
  private:
    OntSdk sdk;
    std::string ontContract;
    std::string ongContract;
    int precision;

  public:
    OntAssetTx()
    {
        ontContract = "ff00000000000000000000000000000000000001";
        ongContract = "ff00000000000000000000000000000000000002";
        precision = 1;
    }
};
#endif // !ONTASSETTX_H