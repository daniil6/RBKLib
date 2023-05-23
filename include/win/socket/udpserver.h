#pragma once

#include "win/socket/basesocket.h"

class CUDPServer : public CBaseSocket
{
private:
    int Connect() override;

public:
    CUDPServer();
    ~CUDPServer();
};