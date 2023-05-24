#pragma once

#include "win/socket/basesocket.h"

class CTCPServer : public CBaseSocket
{
private:
    std::function<int(const SOCKET&)> m_accept_func;

    void Listen(const SOCKET& socket_server);

public:
    CTCPServer();
    ~CTCPServer() override;

    int Connect() override;

    void SetAcceptFunction(std::function<int(const SOCKET&)> func)
    {
        m_accept_func = func;
    }
};