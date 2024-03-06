#pragma once

#include <iostream>

class Size
{
public:
    Size();
    Size(unsigned int w, unsigned int h);

    unsigned int width() const;
    unsigned int height() const;

private:
    unsigned int m_width;
    unsigned int m_height;
};
