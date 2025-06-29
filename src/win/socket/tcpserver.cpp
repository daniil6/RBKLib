#include "win/socket/tcpserver.h"

CTCPServer::CTCPServer()
    : CBaseSocket(TCP)
{
    m_accept_func = nullptr;
}

CTCPServer::~CTCPServer() = default;

int CTCPServer::Connect()
{
    char* ip = nullptr;
    int locale_port = 0;

    int result = 0;
    WSADATA wsaData;
    SOCKET socket_server = 0;
    SOCKADDR_IN locale_addr;
    SOCKADDR_IN remote_addr;

    ZeroMemory(&locale_addr, sizeof(SOCKADDR_IN));
    locale_addr.sin_family = AF_INET;
    locale_addr.sin_port = htons(m_locale_port);
    locale_addr.sin_addr.S_un.S_addr = m_locale_address == nullptr ? INADDR_ANY : inet_addr(m_locale_address);

    ZeroMemory(&remote_addr, sizeof(SOCKADDR_IN));

    printf("WSAStartup...");
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != NO_ERROR) {
        printf("\terror: code %lu: wsa %d: result %d\n", GetLastError(), WSAGetLastError(), result);
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\n");

    printf("socket...");
    socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(socket_server == INVALID_SOCKET) {
        printf("\terror\tcode:%lu wsa:%d\n", GetLastError(), WSAGetLastError());
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\tid:%llu\n", socket_server);

    printf("bind... ");
    result = bind(socket_server, (SOCKADDR*)&locale_addr, sizeof(locale_addr));
    if(result == SOCKET_ERROR) {
        printf(
            "\terror\tid:%llu code:%lu wsa:%d result:%d\n", socket_server, GetLastError(), WSAGetLastError(), result);
        CloseSocket(socket_server);
        WSACleanup();
        return 1;
    } else {

        ip = inet_ntoa(locale_addr.sin_addr);
        locale_port = htons(locale_addr.sin_port);

        printf("\tsuccess\tid:%llu ip:%s port:%d\n", socket_server, ip, locale_port);
    }

    printf("listen...");
    result = listen(socket_server, SOMAXCONN);
    if(result == SOCKET_ERROR) {
        printf(
            "\terror\tid:%llu code:%lu wsa:%d result:%d\n", socket_server, GetLastError(), WSAGetLastError(), result);
        CloseSocket(socket_server);
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\tid:%llu\n", socket_server);

    m_list_link.push_back(
        { socket_server, SERVER, locale_addr, remote_addr, new std::thread(&CTCPServer::Listen, this, socket_server) });

    return result;
}

void CTCPServer::Listen(const SOCKET& socket_server)
{
    int result = 0;
    int remote_port = 0;
    char* ip = nullptr;

    SOCKET socket_client = 0;
    SOCKADDR_IN locale_addr;
    SOCKADDR_IN remote_addr;
    int length_address = sizeof(SOCKADDR_IN);

    ZeroMemory(&locale_addr, sizeof(SOCKADDR_IN));
    ZeroMemory(&remote_addr, sizeof(SOCKADDR_IN));

    while(socket_client != INVALID_SOCKET) {

        socket_client = accept(socket_server, (SOCKADDR*)&remote_addr, &length_address); // remote_addr change !!!
        if(socket_client != INVALID_SOCKET) {

            ip = inet_ntoa(remote_addr.sin_addr);
            remote_port = htons(remote_addr.sin_port);

            printf("accept... \tsuccess id:%llu ip:%s port:%d\n", socket_client, ip, remote_port);

            if(m_accept_func != nullptr)
                result = m_accept_func(socket_client);

            if(result == 0) {

                std::thread* thr = new std::thread(&CTCPServer::RecvSocket, this, socket_client, remote_addr);
                m_list_link.push_back({ socket_client, CLIENT, locale_addr, remote_addr, thr });
            }

        } else {
            printf("accept...\terror: code %lu: wsa %d: id %llu\n", GetLastError(), WSAGetLastError(), socket_client);
        }
    }

    if(m_close_func != nullptr && m_list_link.empty() == false && m_list_link.at(0).socket == socket_server)
        m_close_func(socket_client);
}