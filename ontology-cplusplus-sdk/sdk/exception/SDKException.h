#ifndef SDKEXCEPTION_H
#define SDKEXCEPTION_H

#include <exception>
#include <string>

#include <nlohmann/json.hpp>

#include "../../common/ErrorCode.h"

class SDKException : virtual public std::exception
{
  public:
    SDKException(nlohmann::json)
    {
        int id = error["Error"];
        std::string what_arg = error["Desc"];
        exception(id, what_arg.c_str());
    }
};

#endif