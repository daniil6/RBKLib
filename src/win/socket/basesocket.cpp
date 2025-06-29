#include "win/socket/basesocket.h"

#include <printx.h>

CBaseSocket::CBaseSocket(const int& type_protocol)
    : m_type_protocol(type_protocol)
{
    m_locale_port = 0;
    m_remote_port = 0;
    m_locale_address = nullptr;
    m_remote_address = nullptr;

    m_print_hex = false;
    m_print_message = false;
    m_receive_func = nullptr;
    m_close_func = nullptr;

    m_process_check = true;
    m_thr_check = new std::thread(&CBaseSocket::CheckThread, this);
}

CBaseSocket::~CBaseSocket()
{
    Disconnect();

    m_process_check = false;
    if(m_thr_check != nullptr) {
        m_thr_check->join();
        delete m_thr_check;
        m_thr_check = nullptr;
    }
}

void CBaseSocket::CheckThread()
{
    int result = 0;
    int error_code = 0;
    int length_error_code = sizeof(error_code);

    while(m_process_check == true) {

        std::this_thread::sleep_for(std::chrono::seconds(1));

        for(auto ritr = m_list_link.rbegin(); ritr != m_list_link.rend();) {

            result = getsockopt(ritr->socket, SOL_SOCKET, SO_ERROR, (char*)&error_code, &length_error_code);
            if(result == SOCKET_ERROR) {

                if(ritr->thread != nullptr) {

                    if(ritr->thread->joinable() == true)
                        ritr->thread->join();

                    delete ritr->thread;
                    ritr->thread = nullptr;

                    ritr = decltype(ritr) { m_list_link.erase(std::next(ritr).base()) };
                }
            } else
                ++ritr;
        }
    }
}

int CBaseSocket::Send(const char* data_send, const int& size_send)
{
    int result = 0;

    if(m_list_link.empty() == false) {

        for(auto& p : m_list_link)
            if(p.type == CLIENT)
                result |= SendSocket(p.socket, p.remote_addr, data_send, size_send);

        return result;
    } else
        printf("error: list architecture is empty");

    return 1;
}

int CBaseSocket::SendSocket(const SOCKET& socket_client,
    SOCKADDR_IN& remote_addr,
    const char* data_send,
    const int& size_send)
{
    int remote_port = 0;
    char* ip = nullptr;

    int size_question = 0;
    int length_address = sizeof(remote_addr);

    printf("send... ");

    if(m_type_protocol == UDP) {
        size_question = sendto(socket_client, data_send, size_send, 0, (SOCKADDR*)&remote_addr, length_address);
    } else if(m_type_protocol == TCP) {
        size_question = send(socket_client, data_send, size_send, 0);
    }

    if(size_question != SOCKET_ERROR) {

        ip = inet_ntoa(remote_addr.sin_addr);
        remote_port = htons(remote_addr.sin_port);

        printf("\tsuccess\tid:%llu ip:%s port:%d size:%d", socket_client, ip, remote_port, size_question);

        if(m_print_message == true) {

            printf(" message: ");
            if(m_print_hex == true)
                printx(data_send, size_question);
            else
                printf("%s\n", data_send);
        } else
            printf("\n");

        return 0;
    }

    printf(
        "\terror\tid:%llu code:%lu wsa:%d result%d\n", socket_client, GetLastError(), WSAGetLastError(), size_question);
    return 1;
}

void CBaseSocket::RecvSocket(const SOCKET& socket_client, const SOCKADDR_IN& remote_addr)
{
    int remote_port = 0;
    char* ip = nullptr;

    int size_answer = 0;
    int length_address = sizeof(remote_addr);

    const int size_recv = SIZE_TCP_BUFFER;
    char* data_recv = new char[SIZE_TCP_BUFFER] { 0 };

    do {

        if(m_type_protocol == UDP) {
            size_answer = recvfrom(socket_client, data_recv, size_recv, 0, (SOCKADDR*)&remote_addr, &length_address);
        } else if(m_type_protocol == TCP) {
            size_answer = recv(socket_client, data_recv, size_recv, 0); // value "size_recv" not change!!!
        }

        if(size_answer > 0) {

            ip = inet_ntoa(remote_addr.sin_addr);
            remote_port = htons(remote_addr.sin_port);

            printf("recv... \tsuccess\tid:%llu ip:%s port:%d size:%d", socket_client, ip, remote_port, size_answer);

            if(m_print_message == true) {

                printf(" message: ");
                if(m_print_hex == true)
                    printx(data_recv, size_answer);
                else
                    printf("%s\n", data_recv);
            } else
                printf("\n");

            if(m_receive_func != nullptr)
                m_receive_func(socket_client, data_recv, size_answer);

        } else if(size_answer == 0) {
            printf("recv... \tsuccess\tid:%llu connection closed\n", socket_client);
        } else {
            printf("recv... \terror\tid:%llu code:%lu wsa:%d result:%d\n", socket_client, GetLastError(),
                WSAGetLastError(), size_answer);
        }

    } while(size_answer > 0);

    CloseSocket(socket_client);

    delete[] data_recv;

    if(m_close_func != nullptr && m_list_link.empty() == false && m_list_link.at(0).socket == socket_client)
        m_close_func(socket_client);
}

int CBaseSocket::Disconnect()
{
    int result = 0;

    for(auto ritr = m_list_link.rbegin(); ritr != m_list_link.rend(); ++ritr) {

        if(m_type_protocol == TCP) {
            if(ritr->type == CLIENT)
                result |= ShutdownSocket(ritr->socket, SD_BOTH);
            if(ritr->type == SERVER)
                result |= CloseSocket(ritr->socket);
        }

        if(m_type_protocol == UDP) {

            result |= ShutdownSocket(ritr->socket, SD_RECEIVE);

            SendSocket(ritr->socket, ritr->locale_addr, "", 0);

            result |= ShutdownSocket(ritr->socket, SD_SEND);
        }

        if(ritr->thread->joinable() == true)
            ritr->thread->join();

        if(ritr == m_list_link.rend() - 1) {

            if(WSACleanup() == SOCKET_ERROR) {
                printf("WSACleanup...\terror\tcode:%lu wsa:%d result:%d\n", GetLastError(), WSAGetLastError(), result);
            }
            printf("WSACleanup...\tsuccess\n");
        }
    }

    return result;
}

int CBaseSocket::ShutdownSocket(const SOCKET& socket, const int& how)
{
    int result = shutdown(socket, how);
    if(result == SOCKET_ERROR) {
        printf("shutdown...\terror\tid:%llu code:%lu wsa:%d result:%d\n", socket, GetLastError(), WSAGetLastError(),
            result);
        return 1;
    }

    printf("shutdown...\tsuccess\tid:%llu\n", socket);
    return 0;
}

int CBaseSocket::CloseSocket(const SOCKET& socket)
{
    int result = closesocket(socket);
    if(result == SOCKET_ERROR) {
        printf(
            "close...\terror\tid:%llu code:%lu wsa:%d result:%d\n", socket, GetLastError(), WSAGetLastError(), result);
        return 1;
    }

    printf("close...\tsuccess\tid:%llu\n", socket);
    return 0;
}