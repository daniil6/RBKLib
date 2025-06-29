#include "socket/tcpbase.h"

CTCPBase::CTCPBase()
{
    m_socket = 0;
}

CTCPBase::~CTCPBase()
{
}

void CTCPBase::Send(const int& sock, const uint8_t* data, const int& size)
{
#ifdef STDIO
    printf("socket %d: send...", sock);
#endif

    int result = send(sock, (char*)data, size, 0);

#ifdef STDIO
    if(result == -1) {
        perror("send");
        return;
    } else
        printf("\tsuccess: size %d\n", result);
        // printf("\tsuccess: size %d: data %s\n", result, data);
#endif
}

void CTCPBase::Recv(const int& sock, std::function<void(const uint8_t*, const int&)> func)
{
    int result = 0;

    int size = SIZE_TRAFFIC;
    uint8_t data[SIZE_TRAFFIC] = { 0 };

    do {

#ifdef STDIO
        printf("socket %d: recv...", sock);
#endif

        result = recv(sock, (char*)data, size, 0);

        if(result > 0) {

#ifdef STDIO
            printf("\tsuccess: size %d\n", result);
            // printf("\tsuccess: size %d: data %s\n", result, data);
#endif

            if(func != nullptr)
                func(data, result);

        } else {
#ifdef STDIO
            if(result == 0)
                printf("\tsuccess: close socket\n");
            else
                perror("recv");
#endif
        }

    } while(result > 0);
}

void CTCPBase::Disconnect(int sock)
{
    char array[20] = { 0 };

    close(sock);

#ifdef STDIO
    sprintf(array, "socket_%d: close", sock);
    perror(array);
#endif
}

int CTCPBase::GetSocket()
{
    return m_socket;
}