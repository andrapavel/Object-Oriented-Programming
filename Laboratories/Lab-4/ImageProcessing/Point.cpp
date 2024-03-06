#pragma once

#include "Point.h"


/**
 * @brief Default constructor for the Point class.
 *
 * Initializes a new Point object with x-coordinate, y-coordinate.
 */
Point::Point() : m_x{ 0 }, m_y{ 0 }
{

}

/**
 * @brief Constructor for the Rectangle class with x, y, width, and height parameters.
 *
 * Initializes a new Rectangle object with the specified x-coordinate, y-coordinate, width, and height values.
 *
 * @param x: The x-coordinate.
 * @param y: The y-coordinate.
 */
Point::Point(unsigned int x, unsigned int y) : m_x{ x }, m_y{ y }
{

}


/**
 * @brief Get the x-coordinate.
 *
 * @return The x-coordinate.
 */
int Point::get_x() const
{
    return this->m_x;
}


/**
 * @brief Get the y-coordinate.
 *
 * @return The y-coordinate.
 */
int Point::get_y() const
{
    return this->m_y;
}


/**
 * @brief Set the x-coordinate.
 *
 * @param x: The new x-coordinate.
 */
void Point::set_x(int x)
{
    m_x = x;
}


/**
 * @brief Set the y-coordinate.
 *
 * @param y: The new y-coordinate.
 */
void Point::set_y(int y)
{
    m_y = y;
}


/**
 * @brief Output stream insertion operator for Point.
 *
 * Inserts the point into the output stream in the format (x, y).
 *
 * @param os: The output stream to insert the point into.
 * @param point: The point to be inserted into the output stream.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Point& point) 
{
    os << "(" << point.m_x << "," << point.m_y << ")";
    return os;
}


/**
 * @brief Input stream extraction operator for Point.
 *
 * Extracts a point from the input stream. Expects the input to be in the format "x y".
 *
 * @param is: The input stream to extract the point from.
 * @param rect: The point to be extracted from the input stream.
 * @return A reference to the input stream.
 */
std::istream& operator>>(std::istream& is, Point& point) 
{
    is >> point.m_x >> point.m_y;
    return is;
}

