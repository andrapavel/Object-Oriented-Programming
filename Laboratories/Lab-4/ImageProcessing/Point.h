#pragma once

#include <iostream>

class Point 
{
public:
    Point();
    Point(unsigned int x, unsigned int y);

    int get_x()const;
    int get_y()const;

    void set_x(int x);
    void set_y(int y);

    friend std::ostream& operator<<(std::ostream& os, const Point& point);
    friend std::istream& operator>>(std::istream& is, Point& point);

private:
    unsigned int m_x;
    unsigned int m_y;
};
