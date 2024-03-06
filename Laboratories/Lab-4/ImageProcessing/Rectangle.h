#pragma once

#include <iostream>

#include "Point.h"

class Rectangle 
{
public:

    Rectangle();
    Rectangle(int x, int y, int width, int height);
    Rectangle(Point topLeft, Point bottomRight);

    Rectangle operator+(const Point& point);
    Rectangle operator-(const Point& point);
    Rectangle operator&(const Rectangle& other);
    Rectangle operator|(const Rectangle& other);

    int get_x() const;
    int get_y() const;

    int get_width() const;
    int get_height() const;

    void set_x(int x);
    void set_y(int y);

    void set_width(int w);
    void set_height(int h);

    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rect);
    friend std::istream& operator>>(std::istream& is, Rectangle& rect);


private:

    unsigned int m_x;
    unsigned int m_y;
    unsigned int m_width;
    unsigned int m_height;
};
