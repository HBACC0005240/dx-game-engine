#pragma once
#include <iostream>
using namespace std;

class A {
public:
    int mAge;
public:
    A(int age) :mAge(age) {
        cout << "A()构造 p:" << this << endl;
    }

    A(const A& a) {
        mAge = a.mAge;
        cout << "A()拷贝构造 p:" << this << endl;
    }
    ~A() {
        cout << "~A()析构 p:" << this << endl;
    }
};

class C {
private:
    A& a;
public:
    C(A& a) :a(a) {
        cout << "C()构造 p:" << this << endl;
    }

    ~C() {
        cout << "~C()析构 p:" << this << endl;
    }

};

class B {
private:
    A& a;
    C c;
public:
    B(A a) :a(a), c(a) {
        cout << "B()构造 p:" << this << endl;
    }

    ~B() {
        cout << "~B()析构 p:" << this << endl;
    }
    void run() {
        cout << "A age:" << a.mAge << endl;
    }
};