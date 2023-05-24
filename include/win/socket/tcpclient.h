#pragma once

#include "win/socket/basesocket.h"

class CTCPClient : public CBaseSocket
{
public:
    CTCPClient();
    ~CTCPClient();

    int Connect() override;
};