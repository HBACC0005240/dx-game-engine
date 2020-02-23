#include <iostream>
using namespace std;

//������
class Animal {
protected:
	string name;
public:
	Animal(string _name) {
		name = _name;
	}

	//�麯��
	virtual void run() {
		cout << name << " ���ڱ���" << endl;
	}

	//���麯��
	//virtual void eat() = 0;

	~Animal() {
		cout << "Animal()����" << endl;
	}
};

//è
class Cat :public Animal{
public:
	Cat(string _name) :Animal(_name){

	}

	virtual void eat() {
		cout << "è��è��" << endl;
	};

	//�麯��
	virtual void run() {
		cout << name << "������ ���ڱ���" << endl;
	}

	~Cat() {
		cout << "~Cat()����" << endl;
	}
};

//�����Ƕ�̬
void show(Animal* animal) {
	animal->run();
}


int _2main() {
	//Animal* anm = new Animal("����");
	//show(anm);

	Animal* anm1 = new Cat("Сè");
	show(anm1);

	delete anm1;

	return 0;
}