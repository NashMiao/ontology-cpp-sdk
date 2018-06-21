#ifndef ICONNECTOR_H
#define ICONNECTOR_H

#include "boost/any.hpp"

class IConnector{
    virtual boost::any sendRawTransaction(bool preExec, std::string userid, std::string hexData);
};

#endif