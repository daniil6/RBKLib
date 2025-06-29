#include "socket/tcpclient.h"

CTCPClientU::CTCPClientU()
{
}

CTCPClientU::~CTCPClientU()
{
}

int CTCPClientU::Connect(const char* address, int port)
{
	char array[20] = { 0 };
	int result = 0;

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = inet_addr(address);

	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	// memset(array, 0, 20);
	sprintf(array,"socket_%d", m_socket);
	perror(array);
	if(m_socket < 0)
		return 1;

	result = connect(m_socket, (struct sockaddr*)&addr, sizeof(addr));
	perror("connect");
	if(result < 0)
		return 1;

	// if(send(socketClient, message, sizeSend, 0) == false)
	// 	return 1;
	// perror("send");
	//
	// if(close(socketClient) == true)
	// 	return 1;
	// perror("close");

	return 0;
}
