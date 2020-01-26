#pragma once
#include <iostream>
using namespace std;

class A {
public:
    int mAge;
public:
    A(int age) :mAge(age) {
        cout << "A()���� p:" << this << endl;
    }

    A(const A& a) {
        mAge = a.mAge;
        cout << "A()�������� p:" << this << endl;
    }
    ~A() {
        cout << "~A()���� p:" << this << endl;
    }
};

class C {
private:
    A& a;
public:
    C(A& a) :a(a) {
        cout << "C()���� p:" << this << endl;
    }

    ~C() {
        cout << "~C()���� p:" << this << endl;
    }

};

class B {
private:
    A& a;
    C c;
public:
    B(A a) :a(a), c(a) {
        cout << "B()���� p:" << this << endl;
    }

    ~B() {
        cout << "~B()���� p:" << this << endl;
    }
    void run() {
        cout << "A age:" << a.mAge << endl;
    }
};