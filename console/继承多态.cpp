#include <iostream>
using namespace std;

//动物类
class Animal {
protected:
	string name;
public:
	Animal(string _name) {
		name = _name;
	}

	//虚函数
	virtual void run() {
		cout << name << " 正在奔跑" << endl;
	}

	//纯虚函数
	//virtual void eat() = 0;

	~Animal() {
		cout << "Animal()析构" << endl;
	}
};

//猫
class Cat :public Animal{
public:
	Cat(string _name) :Animal(_name){

	}

	virtual void eat() {
		cout << "猫吃猫粮" << endl;
	};

	//虚函数
	virtual void run() {
		cout << name << "喵喵喵 正在奔跑" << endl;
	}

	~Cat() {
		cout << "~Cat()析构" << endl;
	}
};

//这里是多态
void show(Animal* animal) {
	animal->run();
}


int _2main() {
	//Animal* anm = new Animal("动物");
	//show(anm);

	Animal* anm1 = new Cat("小猫");
	show(anm1);

	delete anm1;

	return 0;
}