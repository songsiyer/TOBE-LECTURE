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
		int a=3;
		char b;
		std::string c;
	protected :
		int aa;
	public :
		cpp_basic(); // ������
		~cpp_basic(); // �Ҹ��� & �����Ҵ� �����Ҵ� ����
		cpp_basic operator<<(const int add);
		bool operator<(const cpp_basic &compare) const;
		void set_a(int a) {
			this->a = a;
		}
		int get_a(){
			return a;
		}
		virtual void someFunction();
		void ������Լ�(int a);
	};

	class sangsock : public cpp_basic { //inheritance
	private :
		std::vector<int> val;
	public :
		sangsock();
		void someFunction();
		bool operator<(const sangsock& compare) const;
	};
}

