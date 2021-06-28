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
	// 버퍼 설정. +1은 \0를 넣기 위한 크기
	char out[BUFFERSIZE + 1];

	char* ret = new char[str->size() + 10];
	memcpy(ret, "echo - ", 7);
	cout << "From Client message : ";

	for (int n = 0; n < (str->size() / BUFFERSIZE) + 1; n++)
	{
		// 버퍼 사이즈 설정
		int size = str->size();
		// 수신 데이터가 버퍼 사이즈를 넘었을 경우.
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
		// echo 메시지와 콘솔 메시지를 작성한다.
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
		// 콘솔 메시지 콘솔 출력.
		cout << out;
	}
	cout << endl;

	memcpy(ret + p + 7, "\n>\0", 3);
	return ret;
}
void clientThread(SOCKET clientSock, SOCKADDR_IN clientAddr, vector<thread*>* clientlist)
{
	char buf[20] = { 0, };
	// 접속 정보를 콘솔에 출력한다.
	cout << "Client connected IP address = " << inet_ntop(AF_INET, &clientAddr.sin_addr, buf,sizeof(buf)) << ":" << ntohs(clientAddr.sin_port) << endl;
	// client로 메시지를 보낸다.
	const char* message = "Welcome server!\r\n>\0";
	send(clientSock, message, strlen(message) + 1, 0);

	vector<char> buffer;
	char x;
	while (true)
	{
		// 데이터를 받는다. 에러가 발생하면 멈춘다.
		if (recv(clientSock, &x, sizeof(char), 0) == SOCKET_ERROR)
		{
			// 에러 콘솔 출력
			cout << "error" << endl;
			break;
		}
		// 만약 buffer의 끝자리가 개행일 경우
		if (buffer.size() > 0 && *(buffer.end() - 1) == '\r' && x == '\n')
		{
			// 메시지가 exit일 경우는 수신대기를 멈춘다.
			if (*buffer.begin() == 'e' && *(buffer.begin() + 1) == 'x' && *(buffer.begin() + 2) == 'i' && *(buffer.begin() + 3) == 't') {
				break;
			}
			// 콘솔에 출력하고 에코 메시지를 받는다.
			const char* echo = print(&buffer);
			// client로 에코 메시지 보낸다.
			send(clientSock, echo, buffer.size() + 10, 0);

			// 에코 메시지를 힙(new을 사용한 선언)에 선언했기 때문에 메모리 해지한다.
			delete echo;
			// 버퍼를 비운다.
			buffer.clear();
			// 다음 메시지 수신 대기
			continue;
		}
		// 버퍼에 글자를 하나 넣는다.
		buffer.push_back(x);
	}

	closesocket(clientSock);
	cout << "Client disconnected IP address = " << inet_ntop(AF_INET, &clientAddr.sin_addr, buf, sizeof(buf)) << ":" << ntohs(clientAddr.sin_port) << endl;
	
	// threadlist에서 현재 쓰레드를 제거한다.
	for (auto ptr = clientlist->begin(); ptr < clientlist->end(); ptr++)
	{
		// thread 아이디가 같은 것을 찾아서
		if ((*ptr)->get_id() == this_thread::get_id())
		{
			// 리스트에서 뺀다.
			clientlist->erase(ptr);
			break;
		}
	}
}

int main()
{
	vector<thread*> clientlist;

	// 소켓 정보 구조체 생성
	WSADATA wsaData;
	// 구조체에 소켓버전 정보 입력 및 윈도우 소켓동작 준비상태만들기
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}

	// Internet의 Stream 방식으로 소켓 생성
	SOCKET serverSock = socket(PF_INET, SOCK_STREAM, 0); //PF_INET 프로토콜 정의값 IPv4

	SOCKADDR_IN addr = {};
	//memset(&addr, 0, sizeof(addr));

	// 소켓은 Internet 타입
	addr.sin_family = AF_INET; //AF_INET 주소체계 정의값 IPv4
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(PORT);

	// 설정된 소켓 정보를 소켓에 바인딩한다.
	if (bind(serverSock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		// 에러 콘솔 출력
		cout << "error" << endl;
		return 1;
	}

	// 소켓을 대기 상태로 기다린다.
	if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR)
	{
		// 에러 콘솔 출력
		cout << "error" << endl;
		return 1;
	}

	cout << "Server Start" << endl;

	// 다중 접속을 위해 while로 소켓을 대기한다.
	while (true)
	{
		// 접속 설정 구조체 사이즈
		int len = sizeof(SOCKADDR_IN);
		// 접속 설정 구조체
		SOCKADDR_IN clientAddr;
		// client가 접속을 하면 SOCKET을 받는다.
		SOCKET clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &len);
		// 쓰레드를 실행하고 쓰레드 리스트에 넣는다.
		clientlist.push_back(new thread(clientThread, clientSock, clientAddr, &clientlist));
	}

	// 종료가 되면 쓰레드 리스트에 남아 있는 쓰레드를 종료할 때까지 기다린다.
	for (auto ptr = clientlist.begin(); ptr < clientlist.end(); ptr++)
	{
		(*ptr)->join();
	}

	closesocket(serverSock);
	// 소켓 종료
	WSACleanup();
	return 0;
}