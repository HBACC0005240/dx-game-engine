#include "����������.h"

class Person::Animal {
public:
	int age;
	void doSomething() {
		cout << "���������ɶ age => "<< age << endl;
	}

	Animal(int _age) {
		age = _age;
	}
};

Person::~Person()
{
	cout << "~Person()��������" << endl;
	delete animal;
}

void Person::init()
{
	animal = new Animal(100);
	animal->doSomething();
}
