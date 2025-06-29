#ifndef CTCPCLIENT_H
#define CTCPCLIENT_H

#include "unix/socket/tcpbase.h"

class CTCPClientU : public CTCPBase
{
public:
	CTCPClientU();
	~CTCPClientU();

	int Connect(const char* address, int port);
};

#endif // CTCPCLIENT_H
