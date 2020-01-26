#pragma once
#include <iostream>
using namespace std;

#define construct(_class)							\
	public:											\
		static void show();							\
		_class(const _class&) = delete;				\
		_class& operator=(const _class&) = delete;	\
		_class()


class Person {
	construct(Person) {
		cout << "Person()¹¹Ôìº¯Êý" << endl;
		animal = nullptr;
	}
public:
	~Person();
	void init();
private:
	class Animal;
	Animal* animal;
};