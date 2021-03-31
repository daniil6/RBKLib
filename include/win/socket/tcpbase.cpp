#include "win/socket/tcpbase.h"

CTCPBase::CTCPBase()
{
}

CTCPBase::~CTCPBase()
{
}

void CTCPBase::Send(const uint8_t* data, const int& size)
{
    int result = 0;

    printf("socket %d: send...", m_socket);
    result = send(m_socket, (char*)data, size, 0);
    if(result == SOCKET_ERROR)
        printf("\terror: code %d: wsa %d: result %d: ", GetLastError(), WSAGetLastError(), result);
    else
        printf("\tsuccess: size %d: data: %s\n", result, data);
}

void CTCPBase::Recv(std::function<void(const uint8_t*, const int&)> func)
{
    int result = 0;
    uint8_t data[SIZE_BUFFER] = { 0 };
    const int& size = SIZE_BUFFER;

    do {

        printf("socket %d: recv...", m_socket);
        result = recv(m_socket, (char*)data, size, 0);
        if(result > 0) {
            printf("\tsucces: size: %d: data: %s\n", result, data);
            if(func != nullptr)
                func(data, size);
        } else if(result == 0)
            printf("\tsucces: close socket\n");
        else
            printf("\terror: code: %d: wsa: %d: result: %d\n", GetLastError(), WSAGetLastError(), result);

    } while(result > 0);
}

void CTCPBase::Disconnect(SOCKET socket)
{
    printf("socket: %d: close", socket);
    int result = closesocket(socket);
    if(result == SOCKET_ERROR) {
        printf("\terror: code: %d: wsa: %d: result: %d\n", GetLastError(), WSAGetLastError(), result);
    } else
        printf("\tsuccess\n");
}