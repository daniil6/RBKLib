#pragma once

#include "win/socket/basesocket.h"

class CTCPServer : public CBaseSocket
{
private:
    void Listen(const SOCKET& socket_server);

    int Connect() override;

public:
    CTCPServer();
    ~CTCPServer() override;
};