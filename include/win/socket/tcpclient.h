#ifndef CCLIENT_H
#define CCLIENT_H

#include "win/socket/tcpbase.h"

class CTCPClient : public CTCPBase
{
public:
    CTCPClient();
    ~CTCPClient();

    int Connect(const char* address, int port) override;
};

#endif // CCLIENT_H