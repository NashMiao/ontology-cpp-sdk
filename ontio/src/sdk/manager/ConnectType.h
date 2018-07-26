#ifndef CONNECTTYPE_H
#define CONNECTTYPE_H

#if __cplusplus < 201103L
#error "use --std=c++11 option for compile."
#endif

enum class ConnectType : int
{
    WebSocket,
    RPC,
    RESTful
};

#endif