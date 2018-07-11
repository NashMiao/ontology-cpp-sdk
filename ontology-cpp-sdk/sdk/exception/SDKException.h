#ifndef SDKEXCEPTION_H
#define SDKEXCEPTION_H

#include <exception>
#include <string>

#include <nlohmann/json.hpp>

#include "../../common/ErrorCode.h"

class SDKException : virtual public std::exception
{
  protected:
    int id;
    std::string what_arg;

  public:
    SDKException(nlohmann::json error)
    {
        id = error["Error"];
        what_arg = error["Desc"];
    }

    virtual ~SDKException() throw() {}

    virtual int getErrorNumber() const throw() { return id; }

    virtual const char *what() const throw()
    {
        return what_arg.c_str();
    }
};

#endif