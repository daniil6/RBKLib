#ifndef CTCPBASE_H
#define CTCPBASE_H

#ifdef UNIX
#include <arpa/inet.h>
#endif // UNIX

#ifdef WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#endif

#include <cstring>
#include <functional>
#include <unistd.h>
#include <cstdint>

#include <stdio.h>

#define SIZE_DIO 30
#define SIZE_TRAFFIC 1100
#define MAX_SIZE_SEND 1024 * 1024
#define MIN_SIZE_SEND 1024

class CTCPBase
{
protected:
    int m_socket;

public:
    CTCPBase();
    ~CTCPBase();

    /**
     * @brief
     * @param sock
     * @param data
     * @param size
     */
    void Send(const int& sock, const uint8_t* data, const int& size);

    /**
     * @brief
     * @param sock
     * @param func
     */
    void Recv(const int& sock, std::function<void(const uint8_t*, const int&)> func = nullptr);

    /**
     * @brief
     * @param sock
     */
    static void Disconnect(int sock);

    /**
     * @brief
     * @return
     */
    int GetSocket();
};

#endif // CTCPBASE_H
