#include <iostream>
#include <thread>
#include "cpp_basic.h"
//c++ stl 위키 https://ko.wikipedia.org/wiki/%ED%91%9C%EC%A4%80_%ED%85%9C%ED%94%8C%EB%A6%BF_%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC
using namespace std;

bool thread_run;
void counter() {
	int i = 0;
	while (thread_run) {
		cout << "thread Counter Running -- " << i++ << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

int main() {
	using namespace lll;
	thread_run = true;
	thread thread_test = thread(counter);
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


	list<cpp_basic> test_list;
	list<cpp_basic>::iterator list_iter;
	for (int i = size; i > 0; i--) {
		cpp_basic temp_class;
		test_list.push_back(temp_class << i);
	}

	for (list_iter = test_list.begin(); list_iter != test_list.end(); list_iter++) {
		(*list_iter).someFunction();
	}

	test_list.sort();

	for (list_iter = test_list.begin(); list_iter != test_list.end(); list_iter++) {
		(*list_iter).someFunction();
	}

	try { //try catch
		throw 3;
	}
	catch (int exception) {
		cout << "ERROR (error code :" <<exception << ")" << endl;
	}
	thread_run = false;
	thread_test.join();
	return 0;
}