#include "win/socket/udpclient.h"

CUDPClient::CUDPClient()
    : CBaseSocket(UDP)
{
}

CUDPClient::~CUDPClient() = default;

int CUDPClient::Connect()
{
    const char* locale_ip = nullptr;
    const char* remote_ip = nullptr;
    int locale_port = 0;
    int remote_port = 0;

    char host_name[255] = { 0 };
    struct hostent* host_entry = nullptr;

    int result = 0;
    WSADATA wsaData;
    SOCKET socket_client = 0;
    SOCKADDR_IN locale_addr;
    SOCKADDR_IN remote_addr;

    printf("WSAStartup...");
    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != NO_ERROR) {
        printf("\terror code:%lu wsa:%d result:%d\n", GetLastError(), WSAGetLastError(), result);
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\n");

    {
        gethostname(host_name, 255);
        host_entry = gethostbyname(host_name);
        locale_ip = inet_ntoa(*(struct in_addr*)*host_entry->h_addr_list);
    }

    ZeroMemory(&locale_addr, sizeof(SOCKADDR_IN));
    locale_addr.sin_family = AF_INET;
    locale_addr.sin_port = htons(m_locale_port);
    locale_addr.sin_addr.S_un.S_addr = inet_addr(locale_ip);

    ZeroMemory(&remote_addr, sizeof(SOCKADDR_IN));
    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(m_remote_port);
    remote_addr.sin_addr.S_un.S_addr = m_address == nullptr ? INADDR_ANY : inet_addr(m_address);

    printf("socket...");
    socket_client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(socket_client == INVALID_SOCKET) {
        printf("\terror\tcode:%lu wsa:%d\n", GetLastError(), WSAGetLastError());
        WSACleanup();
        return 1;
    } else
        printf("\tsuccess\tid:%llu\n", socket_client);

    printf("bind... ");
    result = bind(socket_client, (SOCKADDR*)&locale_addr, sizeof(locale_addr));
    if(result == SOCKET_ERROR) {
        printf(
            "\terror\tid:%llu code:%lu wsa:%d result:%d\n", socket_client, GetLastError(), WSAGetLastError(), result);
        CloseSocket(socket_client);
        WSACleanup();
        return 1;
    }

    printf("\tsuccess\tid:%llu ", socket_client);

    locale_ip = inet_ntoa(locale_addr.sin_addr);
    locale_port = htons(locale_addr.sin_port);

    printf("locale ip:%s locale port:%d ", locale_ip, locale_port);

    remote_ip = inet_ntoa(remote_addr.sin_addr);
    remote_port = htons(remote_addr.sin_port);

    printf("remote ip:%s remote port:%d\n", remote_ip, remote_port);

    m_list_link.push_back({ socket_client, CLIENT, locale_addr, remote_addr,
        new std::thread(&CUDPClient::RecvSocket, this, socket_client, locale_addr) });

    return result;
}