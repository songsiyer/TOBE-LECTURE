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
	// ���� ����. +1�� \0�� �ֱ� ���� ũ��
	char out[BUFFERSIZE + 1];

	cout << "From server message : ";
	for (int n = 0; n < (str->size() / BUFFERSIZE) + 1; n++)
	{
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
		}
		// �ܼ� �޽��� �ܼ� ���.
		cout << out;
	}
}

int main()
{
	// ���� ���� ������ ����
	WSADATA wsaData;
	// ���� ����.
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return 1;
	}
	// Internet�� Stream ������� ���� ����
	SOCKET sock = socket(PF_INET, SOCK_STREAM, 0);
	// ���� �ּ� ����
	SOCKADDR_IN addr;
	// ����ü �ʱ�ȭ
	memset(&addr, 0, sizeof(addr));
	// ������ Internet Ÿ��
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
	addr.sin_port = htons(PORT);

	// ����
	if (connect(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		// ���� �ܼ� ���
		cout << "error" << endl;
		return 1;
	}



	// telent�� �ѱ��ھ� �����Ͱ� ���� ������ ���ڸ� ���� buffer�� �ʿ��ϴ�.
	vector<char> buffer;
	// ���� ������
	char x;
	while (true)
	{
		// �����͸� �޴´�. ������ �߻��ϸ� �����.
		if (recv(sock, &x, sizeof(char), 0) == SOCKET_ERROR)
		{
			// ���� �ܼ� ���
			cout << "error" << endl;
			break;
		}
		// ���ۿ� ���ڸ� �ϳ� �ִ´�.
		buffer.push_back(x);
		// \r\n>\0�� ������ �ֿܼ� ����ϰ� �ַܼ� ���� �޽����� ��ٸ���.
		if (buffer.size() > 4 && *(buffer.end() - 4) == '\r' && *(buffer.end() - 3) == '\n' && *(buffer.end() - 2) == '>' && *(buffer.end() - 1) == '\0')
		{
			// �޽��� ���
			print(&buffer);
			// ���� �ʱ�ȭ
			buffer.clear();
			// �ַܼ� ���� �Է��� �޴´�.
			char input[BUFFERSIZE];
			// ������ ���� �Է� �ޱ�
			cin >> input;
			// �Է¹��� ���̸� �޴´�.
			int size = strlen(input);
			// ������ �ִ´�.
			*(input + size + 1) = '\r';
			*(input + size + 2) = '\n';
			// ������ ������
			send(sock, input, size + 3, 0);
			// �޽����� exit��� ����
			if (*input == 'e' && *(input + 1) == 'x' && *(input + 2) == 'i' && *(input + 3) == 't')
			{
				break;
			}
			continue;
		}
	}

	// ���� ���� ����
	closesocket(sock);
	// ���� ����
	WSACleanup();
	return 0;
}