#pragma once

#include "win/socket/basesocket.h"

class CTCPClient : public CBaseSocket
{
private:
    int Connect() override;

public:
    CTCPClient();
    ~CTCPClient();
};