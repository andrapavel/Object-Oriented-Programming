#include <iostream>

#include "Stack.h"

int main()
{
    // create a stack of integers
    Stack<int> int_stack;
    int_stack.push(1);
    int_stack.push(2);
    int_stack.push(3);

    std::cout << "Stack size: " << int_stack.size() << std::endl;

    while (!int_stack.isEmpty())
    {
        std::cout << int_stack.pop() << " ";
    }

    std::cout << std::endl;

    // create a stack of doubles
    Stack<double> double_stack;
    double_stack.push(1.23);
    double_stack.push(4.56);
    double_stack.push(7.89);

    std::cout << "Stack size: " << double_stack.size() << std::endl;

    while (!double_stack.isEmpty())
    {
        std::cout << double_stack.pop() << " ";
    }

    std::cout << std::endl;

    // create a stack of strings
    Stack<std::string> string_stack;
    string_stack.push("foo");
    string_stack.push("bar");
    string_stack.push("baz");

    std::cout << "Stack size: " << string_stack.size() << std::endl;

    while (!string_stack.isEmpty())
    {
        std::cout << string_stack.pop() << " ";
    }

    std::cout << std::endl;
}