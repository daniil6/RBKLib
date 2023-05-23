#pragma once

#include "win/socket//basesocket.h"

class CUDPClient : public CBaseSocket
{
private:
    int Connect() override;

public:
    CUDPClient();
    ~CUDPClient();
};