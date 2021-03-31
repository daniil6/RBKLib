#ifndef CBASELINK_H
#define CBASELINK_H

#include <functional>
#include <stdint.h>
#include <stdio.h>
#include <winsock2.h>

#define SIZE_BUFFER 1100

class CTCPBase
{
protected:
    SOCKET m_socket;

public:
    CTCPBase();
    ~CTCPBase();

    void Send(const uint8_t* data, const int& size);
    void Recv(std::function<void(const uint8_t*, const int&)> func);
    void Disconnect(SOCKET socket);
};

#endif // CBASELINK_H
