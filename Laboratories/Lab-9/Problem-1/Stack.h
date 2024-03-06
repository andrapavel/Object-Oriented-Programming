#pragma once

#include <iostream>
#include <vector>

template<typename T>

class Stack
{
private:
    std::vector<T> data;

public:

    Stack()
    {

    }

    ~Stack()
    {
        data.clear();
    }

    void push(const T& element)
    {
        data.push_back(element);
    }

    T pop()
    {
        if (data.empty())
        {
            throw std::out_of_range("Stack is empty");
        }

        T element = data.back();
        data.pop_back();
        return element;
    }

    bool isEmpty() const
    {
        return data.empty();
    }

    int size() const
    {
        return data.size();
    }

    T top() const
    {
        if (data.empty())
        {
            throw std::out_of_range("Stack is empty");
        }
        return data.back();
    }
};
