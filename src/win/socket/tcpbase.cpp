#include "win/socket/tcpbase.h"

CTCPBase::CTCPBase()
{
    m_socket = 0;
}

CTCPBase::~CTCPBase()
{
}

void CTCPBase::Send(SOCKET socket, const uint8_t* data, const int& size)
{
    int result = 0;

    printf("socket %d: send...", socket);
    result = send(socket, (char*)data, size, 0);
    if(result == SOCKET_ERROR)
        printf("\terror: code %d: wsa %d: result %d: ", (int)GetLastError(), WSAGetLastError(), result);
    else
        printf("\tsuccess: size %d: data: %s\n", result, data);
}

void CTCPBase::Recv(SOCKET socket, std::function<void(const uint8_t*, const int&)> func)
{
    int result = 0;
    uint8_t data[SIZE_BUFFER] = { 0 };
    const int size = SIZE_BUFFER;

    do {

        printf("socket %d: recv...", socket);
        result = recv(socket, (char*)data, size, 0); // value "size" not change!!!
        if(result > 0) {
            printf("\tsucces: size: %d: data: %s\n", result, data);
            if(func != nullptr)
                func(data, result);
        } else if(result == 0)
            printf("\tsucces: close socket\n");
        else
            printf("\terror: code: %d: wsa: %d: result: %d\n", (int)GetLastError(), WSAGetLastError(), result);

    } while(result > 0);
}

void CTCPBase::Disconnect(SOCKET socket)
{
    printf("socket: %d: close", socket);
    int result = closesocket(socket);
    if(result == SOCKET_ERROR) {
        printf("\terror: code: %d: wsa: %d: result: %d\n", (int)GetLastError(), WSAGetLastError(), result);
    } else
        printf("\tsuccess\n");
}

SOCKET CTCPBase::GetSocket()
{
    return m_socket;
}