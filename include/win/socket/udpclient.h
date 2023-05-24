#pragma once

#include "win/socket//basesocket.h"

class CUDPClient : public CBaseSocket
{
public:
    CUDPClient();
    ~CUDPClient();

    int Connect() override;
};