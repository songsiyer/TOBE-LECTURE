#include "socketClass.h"

socketClass::socketClass()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		throw 0;
	}
	sock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&addr, 0, sizeof(addr));
}

socketClass::~socketClass()
{
	closesocket(sock);
	WSACleanup();
}

void socketClass::setSocket(PCSTR ip, int port)
{
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &addr.sin_addr.s_addr);
	addr.sin_port = htons(port);
}

int socketClass::connectSocket()
{
	if (connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		// 에러 콘솔 출력
		return 1;
	}
}
