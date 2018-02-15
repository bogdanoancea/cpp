#include <iostream>
#include "stack.h"
using namespace std;

void f();

int main()
{
    f();

    return 0;
}

void f() {
    Stack::init();
    Stack::stack s1 = Stack::create();
    Stack::stack s2 = Stack::create();


    Stack::push(s1, 'c');
    Stack::push(s2, 'd');
    char c1, c2;
    //if((Stack::pop(s1)) != 'c' ) throw Stack::Bad_pop();
    //if(Stack::pop(s2) != 'd' ) throw Stack::Bad_pop();
    //cout << c1 <<endl;

    Stack::destroy(s1);
    //Stack::destroy(s2);
}
