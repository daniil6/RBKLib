#ifndef CBASELINK_H
#define CBASELINK_H

#ifndef WX_SOCK
#include <winsock2.h>
#endif // WX_SOCK

#include <functional>
#include <stdint.h>
#include <stdio.h>
#include <thread>

#define SIZE_BUFFER 1100

class CTCPBase
{
protected:
    SOCKET m_socket;

public:
    CTCPBase();
    ~CTCPBase();

    void Send(SOCKET sock, const uint8_t* data, const int& size);
    void Recv(SOCKET sock, std::function<void(const uint8_t*, const int&)> func);
    void Disconnect(SOCKET socket);

    SOCKET GetSocket();
};

#endif // CBASELINK_H
