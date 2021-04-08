#ifndef CBASELINK_H
#define CBASELINK_H

#include <functional>
#include <stdint.h>
#include <stdio.h>
#include <winsock2.h>

#define SIZE_BUFFER 50000 // 1100

class CTCPBase
{
protected:
    SOCKET m_socket;

public:
    CTCPBase();
    virtual ~CTCPBase();

    SOCKET GetSocket();

    void Send(SOCKET socket, const uint8_t* data, const int& size);
    void Recv(SOCKET socket, std::function<void(const uint8_t*, const int&)> func);
    void Disconnect(SOCKET socket);
    virtual int Connect(const char* address, int port) = 0;
};

#endif // CBASELINK_H
