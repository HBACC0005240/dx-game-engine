#include "类中声明类.h"

class Person::Animal {
public:
	int age;
	void doSomething() {
		cout << "就随便做点啥 age => "<< age << endl;
	}

	Animal(int _age) {
		age = _age;
	}
};

Person::~Person()
{
	cout << "~Person()析构函数" << endl;
	delete animal;
}

void Person::init()
{
	animal = new Animal(100);
	animal->doSomething();
}
