#ifndef CBASELINK_H
#define CBASELINK_H

#ifndef WX_SOCK
#include <winsock2.h>
#endif // WX_SOCK

#include <functional>
#include <stdint.h>
#include <stdio.h>
#include <thread>
#include <vector>

#include <printx.h>

#define UNUSED(identifier)

#define SIZE_TRAFFIC 1100
#define MAX_SIZE_SEND 1024 * 1024
#define MIN_SIZE_SEND 1024

#define SIZE_TCP_BUFFER 100

enum : int { CLIENT, SERVER };
enum : int { TCP, UDP, TCP_SSL };

struct TItemLink
{
    SOCKET socket;
    int type = 0;
    SOCKADDR_IN locale_addr;
    SOCKADDR_IN remote_addr;
    std::thread* thread = nullptr;
};

class CBaseSocket
{
private:
    int m_type_protocol;
    bool m_print_hex;
    bool m_print_message;
    std::function<void(const SOCKET&, const char*, const int&)> m_print_func;

    // -------------------------------------------------------------------

    bool m_process_check;
    std::thread* m_thr_check;

    void CheckThread();

protected:

    std::function<void(const SOCKET&)> m_close_func;

    // -------------------------------------------------------------------

    int m_locale_port;
    int m_remote_port;
    const char* m_address;

    std::vector<TItemLink> m_list_link;

    // -------------------------------------------------------------------

    void RecvSocket(const SOCKET& socket_client, const SOCKADDR_IN& remote_addr);

    int SendSocket(const SOCKET& socket_client, SOCKADDR_IN& remote_addr, const char* data_send, const int& size_send);

    int CloseSocket(const SOCKET& socket);

    int ShutdownSocket(const SOCKET& socket, const int& how);

public:
    CBaseSocket(const int& type_protocol);
	virtual ~CBaseSocket();

    int Send(const char* data_send, const int& size_send);

    int Disconnect();

    virtual int Connect() = 0;

    // -------------------------------------------------------------------

    void SetPrintHex(bool enable)
    {
        m_print_hex = enable;
    }

    void SetPrintMessage(bool enable)
    {
        m_print_message = enable;
    }

    void SetPrintFunction(std::function<void(const SOCKET&, const char*, const int&)> func)
    {
        m_print_func = func;
    }

    void SetCloseFunction(std::function<void(const SOCKET&)> func)
    {
        m_close_func = func;
    }

    void SetRemotePort(const int& remote_port)
    {
        m_remote_port = remote_port;
    }

    void SetLocalPort(const int& locale_port)
    {
        m_locale_port = locale_port;
    }

    void SetAddress(const char* address)
    {
        m_address = address;
    }

    std::vector<TItemLink>& GetListLink()
    {
        return m_list_link;
    }
};

#endif // CBASELINK_H
