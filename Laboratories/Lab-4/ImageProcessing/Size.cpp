/**
* @file Size.h
* 
* @brief Header file for the Size class.
*/
#include "Size.h"


/**
* @brief Default constructor for Size class.
*
* Initializes width and height to 0.
*/
Size::Size() : m_width{ 0 }, m_height{ 0 }
{

}


/**
* @brief Constructor for Size class.
* 
*Initializes width and height to the provided values.
* 
* @param w The width value to be set.
* @param h The height value to be set.
*/
Size::Size(unsigned int w, unsigned int h) : m_width{ w }, m_height{ h }
{

}


/**
* @brief Returns the width of the Size object.
* 
* @return The width value of the Size object.
*/
unsigned int Size::width() const
{
    return m_width;
}


/**
*@brief Returns the height of the Size object.
* 
*@return The height value of the Size object.
*/
unsigned int Size::height() const
{
    return m_height;
}