#ifndef CBASELINK_H
#define CBASELINK_H

#ifndef WX_SOCK
#include <winsock2.h>
#endif // WX_SOCK

#include <functional>
#include <stdint.h>
#include <stdio.h>
#include <thread>

#define SIZE_BUFFER 50000 // 1100

class CTCPBase
{
protected:
    SOCKET m_socket;

public:
    CTCPBase();
    virtual ~CTCPBase();

    void Send(SOCKET sock, const uint8_t* data, const int& size);
    void Recv(SOCKET sock, std::function<void(const uint8_t*, const int&)> func);

    void Disconnect(SOCKET socket);
    virtual int Connect(const char* address, int port) = 0;

    SOCKET GetSocket();
};

#endif // CBASELINK_H
