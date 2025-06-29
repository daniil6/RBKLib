#include "unix/socket/tcpserver.h"

CTCPServer::CTCPServer()
{
}

CTCPServer::~CTCPServer()
{
}

int CTCPServer::Connect(const char* address, int port)
{
	char array[20] = { 0 };

	int result = 0;
	struct sockaddr_in serv_addr;

	memset(&serv_addr, '0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	// serv_addr.sin_addr.s_addr = inet_addr(address);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	m_socket = socket(AF_INET, SOCK_STREAM, 0);

	// memset(array, 0, 20);
	sprintf(array,"socket_%d", m_socket);

	perror(array);
	if(m_socket < 0)
		return 1;

	result = bind(m_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
	perror("bind");
	if(result < 0) {
		Disconnect(m_socket);
		return 1;
	}

	result = listen(m_socket, 3);
	perror("listen");
	if(result < 0) {
		Disconnect(m_socket);
		return 1;
	}

	return 0;
}

int CTCPServer::Accept()
{
	int socketClient = 0;
	struct sockaddr_in cli_addr;
	socklen_t cli_addr_size = sizeof(cli_addr);

	socketClient = accept(m_socket, (struct sockaddr*)&cli_addr, &cli_addr_size);
	if(socketClient != -1)
		perror("accept");

	return socketClient;
}
