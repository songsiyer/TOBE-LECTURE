#pragma once
#include <iostream>
#include <string>

// ������ �����̳�
#include <vector>
#include <list>
#include <deque>

namespace lll {
	class cpp_basic
	{
	private :
		int a;
		char b;
		std::string c;
	public :
		cpp_basic(); // ������
		~cpp_basic(); // �Ҹ��� & �����Ҵ� �����Ҵ� ����
		cpp_basic operator<<(const int add);
		void someFunction();
		void ������Լ�(int a);
	};
}

