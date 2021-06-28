#pragma comment(lib, "ws2_32")

#include <iostream>
#include <vector>
#include <thread>
#include <winsock2.h>
#include <WS2tcpip.h>

using namespace std;

#define BUFFERSIZE 1024

#define PORT 12312

char* print(vector<char>* str)
{
	int p = 0;
	// ���� ����. +1�� \0�� �ֱ� ���� ũ��
	char out[BUFFERSIZE + 1];

	char* ret = new char[str->size() + 10];
	memcpy(ret, "echo - ", 7);
	cout << "From Client message : ";

	for (int n = 0; n < (str->size() / BUFFERSIZE) + 1; n++)
	{
		// ���� ������ ����
		int size = str->size();
		// ���� �����Ͱ� ���� ����� �Ѿ��� ���.
		if (size > BUFFERSIZE) {
			if (str->size() < (n + 1) * BUFFERSIZE)
			{
				size = str->size() % BUFFERSIZE;
			}
			else
			{
				size = BUFFERSIZE;
			}
		}
		// echo �޽����� �ܼ� �޽����� �ۼ��Ѵ�.
		for (int i = 0; i < size; i++, p++)
		{
			out[i] = *(str->begin() + p);
			if (out[i] == '\0')
			{
				out[i] = ' ';
			}
			*(ret + p + 7) = out[i];
		}
		out[size] = '\0';
		// �ܼ� �޽��� �ܼ� ���.
		cout << out;
	}
	cout << endl;

	memcpy(ret + p + 7, "\n>\0", 3);
	return ret;
}
void clientThread(SOCKET clientSock, SOCKADDR_IN clientAddr, vector<thread*>* clientlist)
{
	char buf[20] = { 0, };
	// ���� ������ �ֿܼ� ����Ѵ�.
	cout << "Client connected IP address = " << inet_ntop(AF_INET, &clientAddr.sin_addr, buf,sizeof(buf)) << ":" << ntohs(clientAddr.sin_port) << endl;
	// client�� �޽����� ������.
	const char* message = "Welcome server!\r\n>\0";
	send(clientSock, message, strlen(message) + 1, 0);

	vector<char> buffer;
	char x;
	while (true)
	{
		// �����͸� �޴´�. ������ �߻��ϸ� �����.
		if (recv(clientSock, &x, sizeof(char), 0) == SOCKET_ERROR)
		{
			// ���� �ܼ� ���
			cout << "error" << endl;
			break;
		}
		// ���� buffer�� ���ڸ��� ������ ���
		if (buffer.size() > 0 && *(buffer.end() - 1) == '\r' && x == '\n')
		{
			// �޽����� exit�� ���� ���Ŵ�⸦ �����.
			if (*buffer.begin() == 'e' && *(buffer.begin() + 1) == 'x' && *(buffer.begin() + 2) == 'i' && *(buffer.begin() + 3) == 't') {
				break;
			}
			// �ֿܼ� ����ϰ� ���� �޽����� �޴´�.
			const char* echo = print(&buffer);
			// client�� ���� �޽��� ������.
			send(clientSock, echo, buffer.size() + 10, 0);

			// ���� �޽����� ��(new�� ����� ����)�� �����߱� ������ �޸� �����Ѵ�.
			delete echo;
			// ���۸� ����.
			buffer.clear();
			// ���� �޽��� ���� ���
			continue;
		}
		// ���ۿ� ���ڸ� �ϳ� �ִ´�.
		buffer.push_back(x);
	}

	closesocket(clientSock);
	cout << "Client disconnected IP address = " << inet_ntop(AF_INET, &clientAddr.sin_addr, buf, sizeof(buf)) << ":" << ntohs(clientAddr.sin_port) << endl;
	
	// threadlist���� ���� �����带 �����Ѵ�.
	for (auto ptr = clientlist->begin(); ptr < clientlist->end(); ptr++)
	{
		// thread ���̵� ���� ���� ã�Ƽ�
		if ((*ptr)->get_id() == this_thread::get_id())
		{
			// ����Ʈ���� ����.
			clientlist->erase(ptr);
			break;
		}
	}
}

int main()
{
	vector<thread*> clientlist;

	// ���� ���� ����ü ����
	WSADATA wsaData;
	// ����ü�� ���Ϲ��� ���� �Է� �� ������ ���ϵ��� �غ���¸����
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}

	// Internet�� Stream ������� ���� ����
	SOCKET serverSock = socket(PF_INET, SOCK_STREAM, 0); //PF_INET �������� ���ǰ� IPv4

	SOCKADDR_IN addr = {};
	//memset(&addr, 0, sizeof(addr));

	// ������ Internet Ÿ��
	addr.sin_family = AF_INET; //AF_INET �ּ�ü�� ���ǰ� IPv4
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	// ������ ���� ������ ���Ͽ� ���ε��Ѵ�.
	if (bind(serverSock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		// ���� �ܼ� ���
		cout << "error" << endl;
		return 1;
	}

	// ������ ��� ���·� ��ٸ���.
	if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR)
	{
		// ���� �ܼ� ���
		cout << "error" << endl;
		return 1;
	}

	cout << "Server Start" << endl;

	// ���� ������ ���� while�� ������ ����Ѵ�.
	while (true)
	{
		// ���� ���� ����ü ������
		int len = sizeof(SOCKADDR_IN);
		// ���� ���� ����ü
		SOCKADDR_IN clientAddr;
		// client�� ������ �ϸ� SOCKET�� �޴´�.
		SOCKET clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &len);
		// �����带 �����ϰ� ������ ����Ʈ�� �ִ´�.
		clientlist.push_back(new thread(clientThread, clientSock, clientAddr, &clientlist));
	}

	// ���ᰡ �Ǹ� ������ ����Ʈ�� ���� �ִ� �����带 ������ ������ ��ٸ���.
	for (auto ptr = clientlist.begin(); ptr < clientlist.end(); ptr++)
	{
		(*ptr)->join();
	}

	closesocket(serverSock);
	// ���� ����
	WSACleanup();
	return 0;
}