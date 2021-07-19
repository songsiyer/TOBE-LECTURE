#pragma comment(lib, "ws2_32")

#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>
#include <WinSock2.h>
#include <WS2tcpip.h>

#define BUFFERSIZE 1024
#define PORT 12312

using namespace std;

void print(vector<char>* str)
{
	int p = 0;
	// 버퍼 설정. +1은 \0를 넣기 위한 크기
	char out[BUFFERSIZE + 1];

	cout << "From server message : ";
	for (int n = 0; n < (str->size() / BUFFERSIZE) + 1; n++)
	{
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
		}
		// 콘솔 메시지 콘솔 출력.
		cout << out;
	}
}

int main()
{
	// 소켓 정보 데이터 설정
	WSADATA wsaData;
	// 소켓 실행.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}
	// Internet의 Stream 방식으로 소켓 생성
	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
	// 소켓 주소 설정
	SOCKADDR_IN addr;
	// 구조체 초기화
	memset(&addr, 0, sizeof(addr));
	// 소켓은 Internet 타입
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
	addr.sin_port = htons(PORT);

	// 접속
	if (connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		// 에러 콘솔 출력
		cout << "error" << endl;
		return 1;
	}



	// telent은 한글자씩 데이터가 오기 때문에 글자를 모을 buffer가 필요하다.
	vector<char> buffer;
	// 수신 데이터
	char x;
	while (true)
	{
		// 데이터를 받는다. 에러가 발생하면 멈춘다.
		if (recv(sock, &x, sizeof(char), 0) == SOCKET_ERROR)
		{
			// 에러 콘솔 출력
			cout << "error" << endl;
			break;
		}
		// 버퍼에 글자를 하나 넣는다.
		buffer.push_back(x);
		// \r\n>\0가 나오면 콘솔에 출력하고 콘솔로 부터 메시지를 기다린다.
		if (buffer.size() > 4 && *(buffer.end() - 4) == '\r' && *(buffer.end() - 3) == '\n' && *(buffer.end() - 2) == '>' && *(buffer.end() - 1) == '\0')
		{
			// 메시지 출력
			print(&buffer);
			// 버퍼 초기화
			buffer.clear();
			// 콘솔로 부터 입력을 받는다.
			char input[BUFFERSIZE];
			// 유저로 부터 입력 받기
			cin >> input;
			// 입력받은 길이를 받는다.
			int size = strlen(input);
			// 개행을 넣는다.
			*(input + size + 1) = '\r';
			*(input + size + 2) = '\n';
			// 서버로 보내기
			send(sock, input, size + 3, 0);
			// 메시지가 exit라면 종료
			if (*input == 'e' && *(input + 1) == 'x' && *(input + 2) == 'i' && *(input + 3) == 't')
			{
				break;
			}
			continue;
		}
	}

	// 서버 소켓 종료
	closesocket(sock);
	// 소켓 종료
	WSACleanup();
	return 0;
}