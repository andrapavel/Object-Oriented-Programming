#include "Rectangle.h"


/**
 * @brief Default constructor for the Rectangle class.
 *
 * Initializes a new Rectangle object with x-coordinate, y-coordinate, width, and height values of zero.
 */
Rectangle::Rectangle() : m_x{ 0 }, m_y{ 0 }, m_width{ 0 }, m_height{ 0 }
{

}


/**
 * @brief Constructor for the Rectangle class with x, y, width, and height parameters.
 *
 * Initializes a new Rectangle object with the specified x-coordinate, y-coordinate, width, and height values.
 *
 * @param x: The x-coordinate of the top-left corner of the rectangle.
 * @param y: The y-coordinate of the top-left corner of the rectangle.
 * @param width: The width of the rectangle.
 * @param height: The height of the rectangle.
 */
Rectangle::Rectangle(int x, int y, int width, int height)
{
    this->m_x = x;
    this->m_y = y;
    this->m_width = width;
    this->m_height = height;
}


/**
 * @brief Construct a rectangle from two points: the top-left corner and the bottom-right corner.
 *
 * @param topLeft: The top-left corner of the rectangle.
 * @param bottomRight: The bottom-right corner of the rectangle.
 */
Rectangle::Rectangle(Point topLeft, Point bottomRight)
{
    m_x = topLeft.get_x();
    m_y = topLeft.get_y();
    m_width = bottomRight.get_x() - topLeft.get_x();
    m_height = bottomRight.get_y() - topLeft.get_y();
}


/**
 * @brief Get the x-coordinate of the top-left corner of the rectangle.
 *
 * @return The x-coordinate of the top-left corner of the rectangle.
 */
int Rectangle::get_x() const 
{
    return this->m_x;
}


/**
 * @brief Get the y-coordinate of the top-left corner of the rectangle.
 *
 * @return The y-coordinate of the top-left corner of the rectangle.
 */
int Rectangle::get_y() const 
{
    return this->m_y;
}


/**
 * @brief Get the width of the rectangle.
 *
 * @return The width of the rectangle.
 */
int Rectangle::get_width() const 
{
    return this->m_width;
}


/**
 * @brief Get the height of the rectangle.
 *
 * @return The height of the rectangle.
 */
int Rectangle::get_height() const 
{
    return this->m_height;
}


/**
 * @brief Set the x-coordinate of the top-left corner of the rectangle.
 *
 * @param x: The new x-coordinate of the top-left corner of the rectangle.
 */
void Rectangle::set_x(int x)
{
    this->m_x = x;
}


/**
 * @brief Set the y-coordinate of the top-left corner of the rectangle.
 *
 * @param y: The new y-coordinate of the top-left corner of the rectangle.
 */
void Rectangle::set_y(int y)
{
    this->m_y = y;
}

/**
*@brief Set the width of the rectangle.
*
* @param w: The new width of the rectangle.
*/
void Rectangle::set_width(int w)
{
    this->m_width = w;
}


/**
 * @brief Set the height of the rectangle.
 *
 * @param h: The new height of the rectangle.
 */
void Rectangle::set_height(int h)
{
    this->m_height = h;
}


/**
 * @brief Output stream insertion operator for Rectangle.
 *
 * Inserts the rectangle into the output stream in the format (x, y, w, h).
 *
 * @param os: The output stream to insert the rectangle into.
 * @param rect: The rectangle to be inserted into the output stream.
 * @return A reference to the output stream.
 */
std::ostream& operator<<(std::ostream& os, const Rectangle& rect) 
{
    os << "(" << rect.get_x() << "," << rect.get_y() << "," << rect.get_width() << "," << rect.get_height() << ")";
    return os;
}


/**
 * @brief Input stream extraction operator for Rectangle.
 *
 * Extracts a rectangle from the input stream. Expects the input to be in the format "x y width height".
 *
 * @param is: The input stream to extract the rectangle from.
 * @param rect: The rectangle to be extracted from the input stream.
 * @return A reference to the input stream.
 */
std::istream& operator>>(std::istream& is, Rectangle& rect) 
{
    /*is >> rect.get_x() >> rect.get_y() >> rect.get_width() >> rect.get_height();
    return is;*/

    int x, y, width, height;
    is >> x >> y >> width >> height;
    rect = Rectangle(x, y, width, height);
    return is;
}


/**
* @brief Overloads the addition operator to add a point to a rectangle.
* 
* @param point: the point to add to the rectangle
* @return a new rectangle that is the sum of the original rectangle and the point
*/
Rectangle Rectangle::operator+(const Point& point)
{
    Rectangle result = *this;
    result.set_x(result.get_x() + point.get_x());
    result.set_y(result.get_y() + point.get_y());
    return result;
}


/**
* @brief Subtracts a point from the coordinates of a Rectangle and returns a new Rectangle.
* 
* @param point: The point to be subtracted.
* @return Rectangle A new Rectangle with the coordinates of the original Rectangle minus the point.
*/
Rectangle Rectangle::operator-(const Point& point)
{
    Rectangle result = *this;
    result.set_x(result.get_x() - point.get_x());
    result.set_y(result.get_y() - point.get_y());
    return result;
}


/**
* @briefComputes the intersection of two rectangles.
* 
* @param other: The other rectangle to compute the intersection with.
* @return The intersection of this rectangle and the other rectangle. If the rectangles do not intersect, returns an empty rectangle.
*/
Rectangle Rectangle::operator&(const Rectangle& other) 
{
    int leftX = std::max(m_x, other.m_x);
    int topY = std::min(m_y, other.m_y);
    int rightX = std::min(m_x + m_width, other.m_x + other.m_width);
    int bottomY = std::max(m_y - m_height, other.m_y - other.m_height);

    if (rightX - leftX < 0 || topY - bottomY < 0)
    {
        Rectangle rez(0, 0, 0, 0);

        return rez;
    }

    Rectangle rez(leftX, topY, rightX - leftX, topY - bottomY);

    return rez;
}


/**
* @brief Overloaded | operator to compute the bounding box of two rectangles.
* 
* @param other: The other rectangle to compute the bounding box with.
* @return Rectangle The bounding box rectangle.
*/
Rectangle Rectangle::operator|(const Rectangle& other)
{
  
    // Determine the bounding box coordinates
    int leftX = std::min(get_x(), other.get_x());
    int topY = std::max(get_y(), other.get_y());
    int rightX = std::max(get_x() + get_width(), other.get_x() + other.get_width());
    int bottomY = std::min(get_y() - get_height(), other.get_y() - other.get_height());

    return Rectangle(leftX, topY,  rightX - leftX,  topY - bottomY);
}