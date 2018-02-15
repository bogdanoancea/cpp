#include <stdexcept>
#include<iostream>
#include"namespace.h"
using namespace std;

int main()
{
    for(int i = 0; i <20; i++) {
        cout << i << endl;
        Stack::push('c');
        cout << Stack::pop() << endl;;

    }

//    Stack::push('c');
//    char c = Stack::pop();
//    cout << 'c';
    return 0;
}

namespace Stack {
    const int max_size = 20;
    char v[max_size];
    int top = 0;

    void push(char c) {
        if (top >= max_size )
            error("Overflow");
        else {
            v[top++] = 'c';
        }
    }

    char pop() {
        char result;
        if(top < 0)
            error ("underflow");
        else {
            result = v[--top];
            if (top < 0)
                top = 0;
        }
        return result;
    }

     void error(std::string s) {
        throw std::runtime_error (s);
    }
}
