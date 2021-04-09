#include "win/socket/tcpbase.h"

CTCPBase::CTCPBase()
{
}

CTCPBase::~CTCPBase()
{
}

void CTCPBase::Send(SOCKET sock, const uint8_t* data, const int& size)
{
    int result = 0;

#ifdef RBK_DEBUG
    printf("socket %d: send...", sock);
#endif // RBK_DEBUG

    result = send(sock, (char*)data, size, 0);

    if(result != SOCKET_ERROR) {

#ifdef RBK_DEBUG
        printf("\tsucces: size: %d\n", result);

#ifdef RBK_DEBUG_DATA_ARRAY
        printf("\n\tdata array:\n");

        for(int i = 0; i < result; i++)
            printf("0x%d ", (int)data[i]);

        printf("\n");
#endif // RBK_DEBUG_DATA_ARRAY

#ifdef RBK_DEBUG_DATA_CHAR
        printf("\n\tdata char:\n");

        printf("%s", data);

        printf("\n");
#endif // RBK_DEBUG_DATA_CHAR

#endif // RBK_DEBUG

    } else
        printf("\terror: code %d: wsa %d: result %d: ", GetLastError(), WSAGetLastError(), result);

    std::this_thread::sleep_for(std::chrono::milliseconds(1));
}

void CTCPBase::Recv(SOCKET sock, std::function<void(const uint8_t*, const int&)> func)
{
    int result = 0;
    uint8_t data[SIZE_BUFFER] = { 0 };
    int size = SIZE_BUFFER;

    do {

#ifdef RBK_DEBUG
        printf("socket %d: recv...", sock);
#endif // RBK_DEBUG

        result = recv(sock, (char*)data, size, 0);
        if(result > 0) {

#ifdef RBK_DEBUG
            printf("\tsucces: size: %d\n", result);

#ifdef RBK_DEBUG_DATA_ARRAY
            printf("\n\tdata array:\n");

            for(int i = 0; i < result; i++)
                printf("0x%d ", (int)data[i]);

            printf("\n");
#endif // RBK_DEBUG_DATA_ARRAY

#ifdef RBK_DEBUG_DATA_CHAR
            printf("\n\tdata char:\n");

            printf("%s", data);

            printf("\n");
#endif // RBK_DEBUG_DATA_CHAR

#endif // RBK_DEBUG

            if(func != nullptr)
                func(data, result);
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

SOCKET CTCPBase::GetSocket()
{
    return m_socket;
}
