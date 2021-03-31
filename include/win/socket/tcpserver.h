#ifndef CTCPSERVER_H
#define CTCPSERVER_H

#include "win/socket/tcpbase.h"

class CTCPServer : public CTCPBase
{
public:
    CTCPServer();
    ~CTCPServer();

    int Connect(const char* address, int port);
    SOCKET Accept();
};

#endif // CTCPSERVER_H