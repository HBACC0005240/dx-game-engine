// console.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "类依赖构造.h"
#include "类中声明类.h"
using namespace std;



int main()
{
    //A a(10);
    //B b(a);
    //b.run();

    Person person;
    person.init();


}
