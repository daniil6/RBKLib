#include "win/socket/tcpclient.h"

CTCPClient::CTCPClient()
{
}

CTCPClient::~CTCPClient()
{
}

int CTCPClient::Connect(const char* address, int port)
{
    int result = 0;
    WSADATA wsaData;
    SOCKADDR_IN clientAddr;

    ZeroMemory(&clientAddr, sizeof(SOCKADDR_IN));
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_addr.S_un.S_addr = inet_addr(address);
    clientAddr.sin_port = htons(port);

    printf("WSAStartup...");
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != NO_ERROR) {
        printf("\terror: code %d: wsa %d: result %d\n", (int)GetLastError(), WSAGetLastError(), result);
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\n");

    printf("socket...");
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == INVALID_SOCKET) {
        printf("\terror: code %d: wsa %d\n", (int)GetLastError(), WSAGetLastError());
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess: id %d\n", m_socket);

    printf("socket %d: connect...", m_socket);
    result = connect(m_socket, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
    if(result == SOCKET_ERROR) {
        printf("\terror: code %d: wsa %d: result %d: ", (int)GetLastError(), WSAGetLastError(), result);
        Disconnect(m_socket);
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\n");

    return result;
}