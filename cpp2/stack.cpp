#include "stack.h"
#include<stdexcept>
using namespace std;
using namespace Stack;


    void Stack::init() {
        for(int i = 0; i < max_stacks; i++) {
            Stack::used2[i] = false;
        }
    }

    Stack::stack Stack::create(){
        stack result = Stack::stacks[0];
        for(int i = 0; i < max_stacks; i++) {
 //           if(Stack::used2[i] == false) {
//                Stack::used2[i] = true;
//                result = Stack::stacks[i];
                break;
//            }
        }
        return result;
    }

    void Stack::destroy(stack s) {
        for(int i = 0; i < max_stacks; i++) {
            if(stacks[i].v == s.v)
                Stack::used2[i] = false;
                break;
        }
    }

    void Stack::push(stack s, char c) {
        if (s.top >= max_size )
            error("Overflow");
        else {
            s.v[s.top++] = c;
        }
    }

    char Stack::pop(stack s) {
        char result;
        if(s.top < 0)
            error ("underflow");
        else {
            result = s.v[--s.top];
            if (s.top < 0)
                s.top = 0;
        }
        return result;
    }

     void Stack::error(std::string s) {
        throw std::runtime_error (s);
    }

