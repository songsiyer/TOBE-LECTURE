#include "cpp_basic.h"

using namespace lll;

	cpp_basic::cpp_basic() {
		a = 0;
		b = 'k';
		c = "asdasdasd";
	}
	cpp_basic::~cpp_basic() {

	}


	cpp_basic cpp_basic::operator<<(const int add)
	{
		this->a += add;
		return *this;
	}

	bool cpp_basic::operator<(const cpp_basic& compare) const
	{
		return (a < compare.a);
	}

	void cpp_basic::someFunction() {
		std::cout << "a : " << a << std::endl << "b : " << b << std::endl << "c : " << c << std::endl;
	}

	void cpp_basic::어려운함수(int a)
	{

	}

