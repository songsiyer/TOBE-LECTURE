#pragma once
#include <iostream>
#include <string>

// 시퀀스 컨테이너
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
		cpp_basic(); // 생성자
		~cpp_basic(); // 소멸자 & 정적할당 동적할당 설명
		cpp_basic operator<<(const int add);
		bool operator<(const cpp_basic &compare) const;
		void set_a(int a) {
			this->a = a;
		}
		int get_a(){
			return a;
		}
		virtual void someFunction();
		void 어려운함수(int a);
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

