#ifndef CTCPSERVER_H
#define CTCPSERVER_H

#include "unix/socket/tcpbase.h"

class CTCPServer : public CTCPBase
{
public:
	CTCPServer();
	~CTCPServer();

	int Connect(const char* address, int port);
	int Accept();

};

#endif // CTCPSERVER_H
