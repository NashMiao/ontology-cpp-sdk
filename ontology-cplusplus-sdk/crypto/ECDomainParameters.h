#ifndef ECDOMAINPARAMETERS_H
#define ECDOMAINPARAMETERS_H

#include <vector>

#include <openssl/ec.h>
#include <string>

#include "Curve.h"

class ECDomainParameters
{
  private:
    CurveName curve_name;
    EC_POINT *ec_point;
    EC_GROUP *group;

  public:
    ECDomainParameters() {}
    ECDomainParameters(CurveName curve) : curve_name(curve)
    {
        group =
            EC_GROUP_new_by_curve_name(CurveNameMethod::get_curve_nid(curve_name));
        ec_point = EC_POINT_new(group);
    }

    ~ECDomainParameters()
    {
        EC_POINT_free(ec_point);
        EC_GROUP_free(group);
    }

    ECDomainParameters &operator=(const ECDomainParameters &param)
    {
        this->curve_name = param.curve_name;
        this->ec_point = param.ec_point;
        this->group = param.group;
        return *this;
    }

    void set_EC_Point(const std::string &pubkey)
    {
        ec_point = EC_POINT_hex2point(group, pubkey.c_str(), NULL, NULL);
    }

    EC_POINT *convert_EC_Point(const std::string &pubkey)
    {
        EC_POINT *point;
        point = EC_POINT_new(group);
        point = EC_POINT_hex2point(group, pubkey.c_str(), NULL, NULL);
        return point;
    }

    EC_POINT *get_EC_Point() { return ec_point; }

    int compare(EC_POINT *a, EC_POINT *b)
    {
        int result;
        // return 1 on success and 0 if an error occurred
        result = EC_POINT_cmp(group, a, b, NULL);
        if (result == 0)
        {
            return result;
        }
        BIGNUM *a_x = BN_new();
        BIGNUM *a_y = BN_new();
        BIGNUM *b_x = BN_new();
        BIGNUM *b_y = BN_new();
        if (!EC_POINT_get_affine_coordinates_GFp(group, a, a_x, a_y, NULL))
        {
            throw new runtime_error("EC_POINT_get_affine_coordinates_GFp failed.");
        }
        if (!EC_POINT_get_affine_coordinates_GFp(group, b, b_x, b_y, NULL))
        {
            throw new runtime_error("EC_POINT_get_affine_coordinates_GFp failed.");
        }
        EC_GROUP_free(group);
        result = BN_cmp(a_x, b_x);
        if (result != 0)
        {
            return result;
        }
        result = BN_cmp(a_y, b_y);
        return result;
    }

    int compare(std::string a, std::string b)
    {
        return a.compare(b);
    }

    std::string
    toString(EC_POINT *p,
             point_conversion_form_t from = POINT_CONVERSION_UNCOMPRESSED)
    {
        std::string str_p;
        str_p = EC_POINT_point2hex(group, p, from, NULL);
        return str_p;
    }
};

#endif