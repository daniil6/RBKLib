#include "win/socket/tcpclient.h"

CTCPClient::CTCPClient()
    : CBaseSocket(TCP)
{
}

CTCPClient::~CTCPClient() = default;

int CTCPClient::Connect()
{
    char* ip = nullptr;
    // int locale_port = 0;
    int remote_port = 0;

    int result = 0;
    WSADATA wsaData;
    SOCKET socket_client = 0;
    SOCKADDR_IN locale_addr;
    SOCKADDR_IN remote_addr;

    ZeroMemory(&locale_addr, sizeof(SOCKADDR_IN));
    // locale_addr.sin_family = AF_INET;
    // locale_addr.sin_port = htons(m_locale_port);
    // locale_addr.sin_addr.S_un.S_addr = m_address == nullptr ? INADDR_ANY : inet_addr(m_address);

    ZeroMemory(&remote_addr, sizeof(SOCKADDR_IN));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(m_remote_port);
    remote_addr.sin_addr.S_un.S_addr = m_remote_address == nullptr ? INADDR_ANY : inet_addr(m_remote_address);

    printf("WSAStartup...");
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != NO_ERROR) {
        printf("\terror code:%lu wsa:%d result:%d\n", GetLastError(), WSAGetLastError(), result);
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\n");

    printf("socket...");
    socket_client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_client == INVALID_SOCKET) {
        printf("\terror code:%lu wsa:%d\n", GetLastError(), WSAGetLastError());
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess id:%llu\n", socket_client);

    /*printf("bind... ");
    result = bind(socket_client, (SOCKADDR*)&locale_addr, sizeof(locale_addr));
    if(result == SOCKET_ERROR) {
        printf("\terror\tid:%llu code:%lu wsa:%d result:%d\n", socket_client, GetLastError(), WSAGetLastError(),
    result); CloseSocket(socket_client); WSACleanup(); return 1; } else {

        ip = inet_ntoa(locale_addr.sin_addr);
        locale_port = htons(locale_addr.sin_port);

        printf("\tsuccess\tid:%llu ip:%s port:%d\n", socket_client, ip, locale_port);
    }*/

    printf("connect...");
    result = connect(socket_client, (SOCKADDR*)&remote_addr, sizeof(remote_addr));
    if(result == SOCKET_ERROR) {
        printf("\terror code:%lu wsa:%d result:%d\n", GetLastError(), WSAGetLastError(), result);
        CloseSocket(socket_client);
        WSACleanup();
        return 1;
    } else {

        ip = inet_ntoa(remote_addr.sin_addr);
        remote_port = htons(remote_addr.sin_port);

        printf("\tsuccess id:%llu ip:%s port:%d\n", socket_client, ip, remote_port);
    }

    m_list_link.push_back({ socket_client, CLIENT, locale_addr, remote_addr,
        new std::thread(&CTCPClient::RecvSocket, this, socket_client, remote_addr) });

    return result;
}