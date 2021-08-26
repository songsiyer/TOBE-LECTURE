#pragma comment(lib, "ws2_32")

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <string>

class socketClass
{
private :
	WSADATA wsaData;
	SOCKET sock;
	SOCKADDR_IN addr;
public :
	socketClass();
	~socketClass();
	void setSocket(PCSTR ip, int port);
	int connectSocket();
	SOCKET getSocket() {
		return sock;
	}
};

