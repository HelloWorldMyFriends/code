#include<iostream>
#include<string>
using namespace std;


class MyClass {

public:
	void showme() {
		cout << "this is me" << endl;
	}

};

////定一个模板类
template <typename T>
class MyTest {

public:
	void zhixing() {
		T obj;
		obj.showme(); //这里并没有报错
	}
};


int main() {
	MyTest<MyClass> myobj;
	myobj.zhixing();
	cout << "ddddddddddddd"<< endl;
	//return 0;
}