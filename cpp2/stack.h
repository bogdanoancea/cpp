#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
#include<string>
using namespace std;

namespace Stack {
    const int max_size = 20;
    const int max_stacks = 5;

    struct Rep{
        char v[max_size];
        int top = 0;
    };
    typedef Rep& stack;
    struct Bad_pop{};



    Rep stacks[max_stacks];
    bool used2[max_stacks];

    void init();
    stack create();
    void destroy(stack s);
    void push(stack s, char c);
    char pop(stack s);
    void error(std::string s);
}

#endif // STACK_H_INCLUDED
