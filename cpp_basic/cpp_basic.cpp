#include "cpp_basic.h"

using namespace lll;

	cpp_basic::cpp_basic() {
		a = 0;
		aa = 100;
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

	sangsock::sangsock() : cpp_basic()
	{
		val.push_back(aa); //a는 안됨 왜?
		someFunction();
	}

	void sangsock::someFunction()
	{
		std::cout << "vector aa : " << val.at(0) << std::endl;
	}

	bool sangsock::operator<(const sangsock& compare) const
	{
		return (val.at(0) < compare.val.at(0));
	}
