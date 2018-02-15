#include <string>
namespace Stack { // interface
void push (char );
char pop ();
void error(std::string s);
}

void f ()
{
    Stack :: push ('c');
    if (Stack::pop() != 'c')
        Stack::error("impossible");
}
