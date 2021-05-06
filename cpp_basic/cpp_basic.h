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
		int a;
		char b;
		std::string c;
	public :
		cpp_basic(); // 생성자
		~cpp_basic(); // 소멸자 & 정적할당 동적할당 설명
		cpp_basic operator<<(const int add);
		void someFunction();
		void 어려운함수(int a);
	};
}

