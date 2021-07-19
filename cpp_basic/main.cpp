#include <iostream>
#include <thread>
#include <mutex>

#include <fstream>

#include "cpp_basic.h"
//c++ stl 위키 https://ko.wikipedia.org/wiki/%ED%91%9C%EC%A4%80_%ED%85%9C%ED%94%8C%EB%A6%BF_%EB%9D%BC%EC%9D%B4%EB%B8%8C%EB%9F%AC%EB%A6%AC
//정렬 알고리즘  bubble sorting
//thread pool 간략 설명
using namespace std;
bool thread_run;
mutex m;
int z = 0;
int total_value = 0;

void counter() {
	int i = 0;
	while (thread_run) {
		cout << "thread Counter Running -- " << i++ << endl;
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

void threadAdd(int thread_num) {
	for (int i = 0; i < 100; i++) {
		//total_value+=1;
		m.lock();
		cout << "thread #"<< thread_num<< " Add val -- " << total_value++ << endl;
		m.unlock();
	}
}

int main() {
	using namespace lll;
	thread_run = true;
	//thread thread_test = thread(counter);
	//thread thread_test1 = thread(threadAdd, 1);
	//thread thread_test2 = thread(threadAdd, 2);
	//thread thread_test3 = thread(threadAdd, 3);
	//thread thread_test4 = thread(threadAdd, 4);
	//thread thread_test5 = thread(threadAdd, 5);

	ifstream fileReader;
	fileReader.open("c:\\aaaaa.txt");
	if (fileReader.is_open()) {
		while (!fileReader.eof()) {
			int i;
			fileReader >> i;
			cout << "파일 읽은 값 - " << i << endl;
		}
	}
	else {
		cout << "파일 열기 실패 - " << endl;
	}
	fileReader.close();

	ofstream fileWriter;
	fileWriter.open("c:\\test.txt");
	srand((unsigned)time(NULL));
	if (fileWriter.is_open()) {
		for (int i = 0; i < 3000; i++) {
			int num = rand();
			fileWriter << num << " ";
		}

	}
	else {
		cout << "파일 열기 실패 - " << endl;
	}

	vector<cpp_basic> test_vector;
	int size;
	cout << "입력해라 숫자 : " ;
	cin >> size;
	for (int i = 0; i < size; i++) {
		cpp_basic temp_class;
		test_vector.push_back(temp_class<<i);
	}
	sangsock s;
	test_vector.push_back(s<< 1);
	s.someFunction();

	for (int i = 0; i < test_vector.size(); i++) {
		cout << "current vector iterator - " << i << endl;
		test_vector.at(i).someFunction();
	}
	cout << "list - " << endl;
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
	//thread_test1.join();
	//thread_test2.join();
	//thread_test3.join();
	//thread_test4.join();
	//thread_test5.join();
	cout << total_value << endl;
	//thread_test.join();
	return 0;
}