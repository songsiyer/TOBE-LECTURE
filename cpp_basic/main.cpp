#include <iostream>
#include "cpp_basic.h"

using namespace std;

int main() {
	using namespace lll;
	vector<cpp_basic> test_vector;
	int size;
	cout << "입력해라 숫자 : ";
	cin >> size;
	for (int i = 0; i < size; i++) {
		cpp_basic temp_class;
		test_vector.push_back(temp_class<<i);
	}

	for (int i = 0; i < test_vector.size(); i++) {
		cout << "current vector iterator - " << i << endl;
		test_vector.at(i).someFunction();
	}
	
	return 0;
}