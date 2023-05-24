#pragma once

#include "win/socket/basesocket.h"

class CUDPServer : public CBaseSocket
{
public:
    CUDPServer();
    ~CUDPServer();

    int Connect() override;
};