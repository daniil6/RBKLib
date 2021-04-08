#include "win/socket/tcpserver.h"

CTCPServer::CTCPServer()
{
}

CTCPServer::~CTCPServer()
{
}

int CTCPServer::Connect(const char* address, int port)
{
    int result = 0;
    WSADATA wsaData;
    SOCKADDR_IN serverAddr;

    ZeroMemory(&serverAddr, sizeof(SOCKADDR_IN));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.S_un.S_addr = inet_addr(address);
    serverAddr.sin_port = htons(port);

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

    printf("socket %d: bind...", m_socket);
    result = bind(m_socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if(result == SOCKET_ERROR) {
        printf("\terror: code %d: wsa %d: result %d\n", (int)GetLastError(), WSAGetLastError(), result);
        Disconnect(m_socket);
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\n");

    printf("socket %d: listen...", m_socket);
    result = listen(m_socket, SOMAXCONN);
    if(result == SOCKET_ERROR) {
        printf("\terror: code %d: wsa %d: result %d\n", (int)GetLastError(), WSAGetLastError(), result);
        Disconnect(m_socket);
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\n");

    return result;
}

SOCKET CTCPServer::Accept()
{
    SOCKET socketClient;
    SOCKADDR_IN clientAddr;
    int lenAddr = sizeof(clientAddr);

    socketClient = accept(m_socket, (SOCKADDR*)&clientAddr, &lenAddr);
    if(socketClient == INVALID_SOCKET) {
        printf("accept...\terror: code %d: wsa %d\n", (int)GetLastError(), WSAGetLastError());
    } else
        printf("accept...\tsuccess: id %d\n", socketClient);

    return socketClient;
}