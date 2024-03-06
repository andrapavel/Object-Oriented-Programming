#include <fstream>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iomanip>

#include "image.h"
#include "Rectangle.h"
#include "Size.h"
#include "Point.h"


/**
 * @brief Constructs an empty Image object with null data and zero width and height.
 */
Image::Image() : m_data(nullptr), m_width{ 0 }, m_height{ 0 }
{

}


/**
 * @brief Constructs an Image object with the specified width and height.
 * 
 * @param w: The width of the image.
 * @param h: The height of the image.
 */
Image::Image(unsigned int w, unsigned int h) : m_width(w), m_height(h)
{
    // Allocate memory for the image data
    m_data = new unsigned char* [m_height];
    for (unsigned int i = 0; i < m_height; i++) 
    {
        m_data[i] = new unsigned char[m_width];
        //std::memset(m_data[i], 0, m_width);
    }
}


/**
 * @brief Constructs an Image object that is a copy of the specified Image object.
 * 
 * @param other: The Image object to be copied.
 */
Image::Image(const Image& other): m_width(other.m_width), m_height(other.m_height)
{
    // Allocate memory for the image data
    m_data = new unsigned char* [m_height];
    for (unsigned int i = 0; i < m_height; i++) 
    {
        m_data[i] = new unsigned char[m_width];
        //std::memcpy(m_data[i], other.m_data[i], m_width * sizeof(unsigned char));
        for (unsigned int i = 0; i < m_width; i++)
        {
            m_data[i] = other.m_data[i];
        }
    }
}


/**
 * @brief Destroys the Image object and frees the memory used by the image data.
 */
Image::~Image()
{
    // Free the memory used by the image data
    release();

}


/**

* @brief Gets the value of a pixel at a specified (x, y) coordinate.
* 
* @param x: The x-coordinate of the pixel.
* @param y: The y-coordinate of the pixel.
* 
* @return The value of the pixel at the given (x, y) coordinate.
* 
* @pre x < m_width and y < m_height
*/
unsigned char Image::get_pixel(unsigned int x, unsigned int y) const 
{
    /*assert(x < m_width&& y < m_height);
    return m_data[y][x];*/
    const unsigned char* pixel = &m_data[y][x];
    return *pixel;
}


/**
* @brief Sets the value of a pixel at a specified (x, y) coordinate.
* 
* @param x: The x-coordinate of the pixel.
* @param y: The y-coordinate of the pixel.
* @param value: The value to set the pixel to.
* @pre x < m_width and y < m_height
* @post The pixel at (x, y) is set to the given value.
*/
void Image::set_pixel(unsigned int x, unsigned int y, unsigned char value) 
{
    /*assert(x < m_width && y < m_height);
    m_data[y][x] = value;*/

    unsigned char* pixel = &m_data[y][x];
    *pixel = value;
}

/**
 * @brief Loads an image from the specified file path.
 * 
 * @param imagePath: The file path of the image to be loaded.
 * 
 * @return True, if the image was successfully loaded, false otherwise.
 */
bool Image::load(std::string imagePath)
{
    // Open the image file
    // std::ios::out flag used in the constructor specifies that the file should be opened for output (writing)
    // std::ios::binary flag specifies that the file should be treated as a binary file rather than a text file 
    // (non-textual data such as images)
    std::ifstream file(imagePath, std::ios::in);
    if (!file) 
    {
        std::cerr << "Error: Failed to open file \"" << imagePath << "\" for reading." << std::endl;
        return false;
    }

    // Read the image header (assume PGM format)
    std::string magic;
    //unsigned int maxVal;
    file >> magic >> m_width >> m_height >> maxVal;
    if (magic != "P2") 
    {
        std::cerr << "Error: File \"" << imagePath << "\" is not in PGM format." << std::endl;
        return false;
    }

    // Allocate memory for the image data
    release();
    this->m_data = new unsigned char* [m_height];
    int pixel;
    for (unsigned int i = 0; i < m_height; i++)
    {
        this->m_data[i] = new unsigned char[m_width];
        for (unsigned int j = 0; j < m_width; j++) 
        {
            file >> pixel;
            m_data[i][j] = pixel;

        }
    }

    // Read the image data
    //file.read(reinterpret_cast<char*>(m_data[0]), m_width * m_height * sizeof(unsigned char));

    // Check for errors
    //if (!file) 
    /*{
        std::cerr << "Error: Failed to read image data from file \"" << imagePath << "\"." << std::endl;
        release();
        return false;
    }*/

    // Close the file
    file.close();

    return true;
}


/**
 * @brief Saves the image data to a file in PGM format.
 * 
 * @param imagePath: the path to the output file.
 * 
 * @return True, if the image was successfully saved, false otherwise.
 */
bool Image::save(std::string imagePath)
{
    // Open the output file
    std::ofstream fout(imagePath, std::ios::out);
    if (!fout)
    {
        // It is always good practice to use cerr to display errors
        std::cerr << "Error: Failed to open file \"" << imagePath << "\" for writing." << std::endl;
        return false;
    }

    // Write the image header (PGM format)
    fout << "P2\n" << m_width << " " << m_height << "\n" << maxVal << "\n";

    // Write the image data
    for (unsigned int i = 0; i < m_height; i++) 
    {
        for (unsigned int j = 0; j < m_width; j++)
            fout << std::setw(3) << (int)m_data[i][j] << " ";
        fout << "\n";
    }


    // Check for errors
    if (!fout)
    {
        std::cerr << "Error: Failed to write image data to file \"" << imagePath << "\"." << std::endl;
        return false;
    }

    // Close the file
    fout.close();

    return true;
}

void Image::set_height(unsigned h)
{
    m_height = h;
}

void Image::set_width(unsigned w)
{
    m_width = w;
}


/**
* @brief Overloaded assignment operator for assigning one image object to another.
* 
* @param other: The image object to be copied.
* 
* @return Image& A reference to the current image object.
*/
Image& Image::operator=(const Image& other)
{
    if (this != &other)
    {
        release();
        m_width = other.m_width;
        m_height = other.m_height;

        m_data = new unsigned char* [m_height];
        for (unsigned int i = 0; i < m_height; i++)
        {
            m_data[i] = new unsigned char[m_width];
            for (unsigned int j = 0; j < m_width; j++)
            {
                m_data[i][j] = other.m_data[i][j];
            }
        }
    }

    return *this;
}


/**
* @brief Overloaded operator+ to perform element-wise addition of two images.
* 
* @param i: The input image to be added to the current image.
* 
* @return Image The resulting image after addition. If the input images have different dimensions, an empty image is returned.
*/
Image Image::operator+(const Image& i)
{
    // Check that the input images have the same dimensions
    if (m_width != i.m_width || m_height != i.m_height) 
    {
        // It is always good practice to use cerr to display errors
        std::cerr << "Error: Input images must have the same dimensions for addition." << std::endl;
        return Image();
    }

    // Create a new image with the same dimensions as the input images
    Image result(i.m_width, i.m_height);

    // Compute the element-wise sum of the pixel values
    for (unsigned int y = 0; y < m_height; y++) 
    {
        for (unsigned int x = 0; x < m_width; x++) 
        {
            int sum = static_cast<int>(m_data[y][x]) + static_cast<int>(i.m_data[y][x]);

            if (sum >= 0 && sum <= 255) 
            {
                result.m_data[y][x] = sum;
            }
            else if (sum > 255) 
            {
                // '?' - ternary operator (short hand If...Else)
                // (condition) ? (value_if_true) : (value_if_false)
                result.m_data[y][x] = sum > 255 ? 255 : static_cast<unsigned char>(sum);
            }
            else if (sum < 0) 
            {
                result.at(y, x) = static_cast<unsigned char>(std::max(0, sum));
            }
        }
    }

    return result;
}


/**
* @brief Performs element-wise addition between the image and a scalar.
* 
* @param scalar: The scalar value to add to each pixel of the image.
* 
* @return Image& A reference to the resulting image.
*/
Image Image::operator+(const int scalar)
{
    Image result(this->m_width, this->m_height);

    for (unsigned int i = 0; i < m_height; i++) 
    {
        for (unsigned int j = 0; j < m_width; j++)
        {
            int sum = this->m_data[i][j] + scalar;

            if (sum >= 0 && sum <= 255) 
            {
                result.m_data[i][j] = sum;
            }
            else if (sum > 255) 
            {
                result.m_data[i][j] = 255;
            }
            else if (sum < 0) 
            {
                result.m_data[i][j] = 0;
            }

        }
    }

    return result;
}


/**
* @brief Performs element-wise subtraction between two images of the same dimensions.
* 
* @param i: The image to subtract from the current image.
* 
* @return The resulting image after subtraction. If the input images do not have the same dimensions, returns an empty image.
*/
Image Image::operator-(const Image& i)
{
    // Check that the input images have the same dimensions
    if (m_width != i.m_width || m_height != i.m_height) 
    {
        // It is always good practice to use cerr to display errors
        std::cerr << "Error: Input images must have the same dimensions for subtraction." << std::endl;
        return Image();
    }

    // Create a new image with the same dimensions as the input images
    Image result(m_width, m_height);

    // Compute the element-wise difference of the pixel values
    for (unsigned int y = 0; y < m_height; y++) 
    {
        for (unsigned int x = 0; x < m_width; x++) 
        {
            int diff = static_cast<int>(m_data[y][x]) - static_cast<int>(i.m_data[y][x]);
            result.at(y, x) = static_cast<unsigned char>(std::max(0, diff));
        }
    }

    return result;
}


/**
* @brief Overloaded subtraction operator between an image and a scalar.
* 
* @param scalar: An integer scalar value to subtract from every pixel value in the image.
* 
* @return A new image object resulting from the subtraction operation.
*/
Image Image::operator-(const int scalar)
{
    Image result(this->m_width, this->m_height);

    for (unsigned int i = 0; i < m_height; i++)
        for (unsigned int j = 0; j < m_height; j++)
        {
            int diff = this->m_data[i][j] - scalar;

            if (diff >= 0 && diff <= 255) 
            {
                result.m_data[i][j] = diff;
            }
            else if (diff > 255) 
            {
                result.m_data[i][j] = 255;
            }
            else if (diff < 0) 
            {
                result.m_data[i][j] = 0;
            }

        }

    return result;
}


/**
* @brief Performs element-wise multiplication of two images.
* 
* @param i: The input image to multiply by.
* 
* @return A new Image object with the same dimensions as the input images, containing the result of the element-wise multiplication. 
* 
* If the input images have different dimensions, an empty Image object is returned and an error message is printed to the console.
* 
*/
Image Image::operator*(const Image& i)
{
    // Check that the input images have the same dimensions
    if (m_width != i.m_width || m_height != i.m_height || m_width != m_height) 
    {
        // It is always good practice to use cerr to display errors
        std::cerr << "Error: Input images must have the same dimensions for multiplication." << std::endl;
        return Image();
    }

    // Create a new image with the same dimensions as the input images
    Image result(i.m_width, i.m_height);

    // Compute the element-wise product of the pixel values
    for (unsigned int j = 0; j < m_height; j++)
    {
        int aux = 0;
        int k = 0;
        for (unsigned int x = 0; x < m_width; x++)
        { 
            for (int y = 0; y < m_width; y++)
            {
                aux += this->m_data[j][k % m_width] * i.m_data[y][x];

                k++;
            }

            if (aux >= 0 && aux <= 255) 
            {
                result.m_data[j][x] = (char)aux;
            }
            else if (aux < 0)
            {
                result.m_data[j][x] = '0';
            }
            else if (aux > 255) 
            {
                result.m_data[j][x] = '255';
            }

            aux = 0;

        }

    }
    return result;
}


/**
* @brief Multiply each pixel value of the image by a scalar.
* 
* @param scalar: The scalar value to multiply the pixel values by.
* 
* @return Image& A reference to the new image with the scaled pixel values.
*/
Image Image::operator*(const int scalar)
{
    // Create a new image with the same dimensions as this image
    Image result(this->m_width, this->m_height);

    // Multiply each pixel value by the scalar
    for (unsigned int i = 0; i < m_height; i++)
    {
        for (unsigned int j = 0; j < m_width; j++)
        {
            int product = this->m_data[i][j] * scalar;

            // Clamp the result to the range [0, 255]
            if (product < 0) 
            {
                product = 0;
            }
            else if (product > 255) 
            {
                product = 255;
            }

            result.m_data[i][j] = product;
        }
    }

    // Return the new image
    return result;
}


/**
* @brief Extracts a region of interest (ROI) from the image and returns it as a new image.
* 
* @param roiImg: The new image that will contain the ROI.
* @param roiRect: The rectangle that defines the ROI.
* 
* @return true if the ROI rectangle is valid and the ROI was successfully extracted, false otherwise.
*/
bool Image::getROI(Image& roiImg, Rectangle roiRect)
{
    // Check that the ROI rectangle is within the image bounds
    if (roiRect.get_x() < 0 || roiRect.get_y() < 0 || roiRect.get_width() < 0 || roiRect.get_height() < 0 ||
        roiRect.get_x() + roiRect.get_width() > m_width || roiRect.get_y() + roiRect.get_height() > m_height)
    {
        // It's always a good practice to use cerr to display errors
        std::cerr << "Error: Invalid ROI rectangle." << std::endl;
        return false;
    }

    // Create a new image with the ROI dimensions
    roiImg = Image(roiRect.get_width(), roiRect.get_height());

    // Copy the ROI pixels to the new image
    for (unsigned int i = 0; i < roiRect.get_height(); i++) 
        for (unsigned int j = 0; j < roiRect.get_width(); j++) 
            roiImg.at(i, j) = at(roiRect.get_x() + i, roiRect.get_y() + j);
        

    return true;
}


/**
* @brief Extracts a region of interest (ROI) from the image and saves it in a new image object.
* 
* @param[out] roiImg: The output image object that will contain the ROI.
* @param[in] x: The x-coordinate of the top-left corner of the ROI.
* @param[in] y: The y-coordinate of the top-left corner of the ROI.
* @param[in] width: The width of the ROI.
* @param[in] height: The height of the ROI.
* 
* @return True if the ROI is valid and was successfully extracted, false otherwise.
*/
bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height)
{
    if (x < 0 || y < 0 || x + width > m_width || y + height > m_height)
        return false;

    roiImg.release();
    roiImg.m_width = width;
    roiImg.m_height = height;
    roiImg.m_data = new unsigned char* [height];
    for (unsigned int i = 0; i < height; i++) 
    {
        roiImg.m_data[i] = new unsigned char[width];
        std::memcpy(roiImg.m_data[i], &m_data[y + i][x], width * sizeof(unsigned char));
    }

    return true;
}


/**
* @brief Check if the image is empty.
* 
* @return True, if the image has 0 width or height, false otherwise.
*/
bool Image::isEmpty() const 
{
    return m_width == 0 || m_height == 0;
}


/**
* @brief Returns the size of the image as a Size object.
* 
* @return Size: The size of the image.
*/
Size Image::size() const
{
    return Size(m_width, m_height);
}


/**
* @brief Get the width of the image.
* 
* @return unsigned int: The width of the image.
*/
unsigned int Image::width() const
{
    return m_width;
}


/**
* @brief Get the height of the image.
* 
* @return The height of the image in pixels.
*/
unsigned int Image::height() const
{
    return m_height;
}


/**
* @brief Returns a reference to the pixel value at the specified coordinates.
* 
* @param x: The x-coordinate of the pixel.
* @param y: The y-coordinate of the pixel.
* 
* @return A reference to the pixel value.
* 
* @throws std::out_of_range if the specified coordinates are out of bounds.
*/
unsigned char& Image::at(unsigned int y, unsigned int x)
{
    if (x >= m_width || y >= m_height) 
        throw std::out_of_range("Index out of bounds");

    return m_data[y][x];
}


/**
* @brief Get a reference to the pixel value at the given point.
* 
* @param pt: The point whose pixel value should be returned.
* 
* @return A reference to the pixel value at the given point.
* 
* @throw std::out_of_range if the point is outside the image bounds.
*/
unsigned char& Image::at(Point pt) 
{
    return m_data[pt.get_x()][pt.get_y()];
}


/**
* @brief Get a pointer to the start of the specified row in the image.
* 
* @param y: The index of the row to retrieve.
* 
* @return A pointer to the start of the row.
* 
* @throws std::out_of_range if the index is out of bounds.
*/
unsigned char* Image::row(int y)
{
    // Check if y is out of bounds
    if (y < 0 || y >= m_size.height() || m_data == nullptr)
        return nullptr;
       // throw std::out_of_range("Invalid row index");
    

    // Compute the pointer to the start of the row
    return m_data[y];
}


/**
* @brief Releases the memory used by the image. This function deletes the dynamically allocated memory used by the image, 
* setting the pixel data to nullptr and the image size to 0.
* 
* @return void
*/
void Image::release() 
{
    if (m_data) 
    {
        for (unsigned char i = 0; i < m_height; i++)
            if (m_data[i])
                delete[] m_data[i];

        delete[] m_data;
        m_data = nullptr;
    }
}


/**
* @brief Overloaded output stream operator for Image class.
* 
* @param os: The output stream object.
* @param dt: The Image object to be printed.
* 
* @return A reference to the output stream object.
*/
std::ostream& operator<<(std::ostream& os, const Image& dt)
{
    os << "Image size: " << dt.m_width << " x " << dt.m_height<< std::endl;

    for (unsigned int i = 0; i < dt.m_height; i++)
    {
        for (unsigned int j = 0; j < dt.m_width; j++)
            os << std::setw(3) << std::setfill(' ') << static_cast<int>(dt.m_data[i][j]) << " ";
      

        os << std::endl;
    }

    return os;
}


/**
* @brief Creates a new image with all pixels set to zero.
* 
* @param width: The width of the image.
* @param height: The height of the image.
* 
* @return Image: A new image with all pixels set to zero.
*/
Image Image::zeros(unsigned int width, unsigned int height)
{
    Image img(width, height);

    for (unsigned int y = 0; y < height; y++) 
    {
        unsigned char* row = img.row(y);

        for (unsigned int x = 0; x < width; x++) 
            row[x] = '0';
        
    }

    return img;
}


/**
* @brief Creates an image of the specified size filled with ones.
* 
* @param width: The width of the image.
* @param height: The height of the image.
* 
* @return The newly created image, with all the pixels set to one.
*/
Image Image::ones(unsigned int width, unsigned int height) 
{
    Image img(width, height);

    for (unsigned int y = 0; y < height; y++)
    {
        unsigned char* row = img.row(y);

        for (unsigned int x = 0; x < width; x++)
            row[x] = '1';

    }

    return img;
}


/**
* @brief Computes the sum of all the elements of a matrix.
* 
* @return The sum of all the elements of a matrix.
*/
int Image::sum()
{
    int s = 0;
    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
            s += m_data[i][j];
    }

    return s;
}

//---------------------ImageProcessing---------------------//

//
///**
//* @brief Virtual function.
//*/
//void ImageProcessing::process(Image& src, Image& dst)
//{
//    
//}

//---------------------BrightnessAndContrast---------------------//


/**
* @brief Default constructor for BrightnessAndContrast class. Initializes the alpha and beta values to 1 and 0 respectively.
*/
BrightnessAndContrast::BrightnessAndContrast()
{
    this->AlphaBeta[0] = 1;
    this->AlphaBeta[1] = 0;
}


/**
* @brief Get the alpha value of the BrightnessAndContrast object.
* 
* @return The alpha value of the BrightnessAndContrast object.
*/
int BrightnessAndContrast::get_alpha()
{
    return this->alpha;
}


/**
* @brief Get the beta value of the BrightnessAndContrast object.
* 
* @return The beta value of the BrightnessAndContrast object.
*/
int BrightnessAndContrast::get_beta()
{
    return this->beta;
}


/**
* @brief Set the alpha value of the BrightnessAndContrast object.
* 
* @param a: The new alpha value to be set.
*/
void BrightnessAndContrast::set_alpha(int a)
{
    AlphaBeta[0] = a;
}


/**
* @brief Set the beta value of the BrightnessAndContrast object.
* 
* @param b: The new beta value to be set.
*/
void BrightnessAndContrast::set_beta(int b)
{
    AlphaBeta[1] = b;
}


/**
* @brief Applies brightness and contrast adjustment to an input Image object and saves the result in an output Image object.
* 
* @param src: The input Image object to be adjusted.
* @param dst: The output Image object where the adjusted image will be saved.
*/
void BrightnessAndContrast::process(Image& src, Image& dst)
{
    dst.set_height(src.height());
    dst.set_width(src.width());

    for (int i = 0; i < src.height(); i++) 
    {
        for (int j = 0; j < src.width(); j++)
        {
            int aux = AlphaBeta[0] * int(src.at(i, j)) + AlphaBeta[1];

            if (aux >= 0 && aux <= 255) 
            {
                dst.at(i, j) = char(aux);
            }
            else if (aux < 0) 
            {
                dst.at(i, j) = 0;
            }
            else if (aux > 255) 
            {
                dst.at(i, j) = 255;
            }
        }
    }
}

//---------------------GammaCorrection---------------------//


/**
* @brief Default constructor for the GammaCorrection class. Initializes gamma value to 1.
*/
GammaCorrection::GammaCorrection() : gamma{ 1 }
{

}


/**
* @brief Get the gamma value of the GammaCorrection object.
* 
* @return The gamma value of the GammaCorrection object.
*/
float GammaCorrection::get_gamma()
{
    return this->gamma;
}


/**
* @brief Set the gamma value of the GammaCorrection object.
* 
* @param g: The new gamma value to be set.
*/
void GammaCorrection::set_gamma(float g)
{
    gamma = g;
}


/**
* @brief Applies gamma correction to an input Image object and saves the result in an output Image object.
* 
* @param src: The input Image object to be adjusted.
* @param dst: The output Image object where the adjusted image will be saved.
*/
void GammaCorrection::process(Image& src, Image& dst)
{
    dst.set_height(src.height());
    dst.set_width(src.width());

    // Iterates through all the pixels
    for (unsigned int i = 0; i < src.height(); i++)
        for (unsigned int j = 0; j < src.width(); j++)
        {
            // Applies the gamma correction to the pixel value
            float pixel_value = src.at(i, j);
            float corrected_value = pow(pixel_value, gamma);

            if (corrected_value > 255)
            {
                dst.at(i, j) = 255;
            }
            // Saves the modiffied pixel values
            else 
            {
                dst.at(i, j) = corrected_value;
            }
        }
}

//---------------------ImageConvolution---------------------//


/**
* @brief Default constructor for the ImageConvolution class. Initializes the kernel to the Identity kernel.
*/
ImageConvolution::ImageConvolution()
{
    value = 1;

    // Initializes the kernel with the Identity kernel
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (i == 1 && j == 1)
                kernel[i][j] = 1;
            else
                kernel[i][j] = 0;
        }
}


/**
* @brief Get the kernel used by the ImageConvolution object.
* 
* @return The kernel used by the ImageConvolution object.
*/
//std::vector<std::vector<int>> ImageConvolution::get_kernel()
//{
//    return this->kernel;
//}


/**
* @brief Sets the kernel of the ImageConvolution object according to a specified type.
* 
* @param type: The type of kernel to set. Possible values are "IK" (Identity kernel), "MBK" (Mean blur kernel), 
* "GBK" (3x3 Gaussian blur kernel), "HSK" (Horizontal Sobel kernel), and "VSK" (Vertical Sobel kernel).
* 
* @return void
*/
void ImageConvolution::set_kernel(std::string type)
{
    if (type == "IK") // Identity kernel
    {
        ImageConvolution ImageConvolution();
    }
    else if (type == "MBK") // Mean blur kernel
    {
        value = 9;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
               kernel[i][j] = 1;
    }
    else if (type == "GBK") // 3x3 Gaussian blur kernel
    {
        value = 16;

        // First row
        kernel[0][0] = 1;
        kernel[0][1] = 2;
        kernel[0][2] = 1;

        // Second row
        kernel[1][0] = 2;
        kernel[1][1] = 4;
        kernel[1][2] = 2;

        // Third row
        kernel[2][0] = 1;
        kernel[2][1] = 2;
        kernel[2][2] = 1;
    }
    else if (type == "HSK") // Horizontol Sobel kernel
    {
        // First row
        kernel[0][0] = 1;
        kernel[0][1] = 2;
        kernel[0][2] = 1;

        // Second row
        kernel[1][0] = 0;
        kernel[1][1] = 0;
        kernel[1][2] = 0;

        // Third row
        kernel[2][0] = -1;
        kernel[2][1] = -2;
        kernel[2][2] = -1;
    }
    else if (type == "VSK") // Vertical Sobel kernel
    {
        // First row
        kernel[0][0] = -1;
        kernel[0][1] = 0;
        kernel[0][2] = 1;

        // Second row
        kernel[1][0] = -2;
        kernel[1][1] = 0;
        kernel[1][2] = 2;

        // Third row
        kernel[2][0] = -1;
        kernel[2][1] = 0;
        kernel[2][2] = 1;
    }
}

Image ImageConvolution::transformToImage()
{
    Image NewImg(3, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            NewImg.at(i, j) = kernel[i][j];
        }
    }
    //std::cout <<"1: " << NewImg;
    return NewImg;
}



/**
* @brief Apply convolution to the source image using the current kernel and store the result in the destination image.
* 
* @param src: The source image.
* @param dst: The destination image.
*/
void ImageConvolution::process(Image& src, Image& dst)
{
    Size s = src.size();
    int x = s.height() - 2;
    int y = s.width() - 2;
    Image a(y,x);
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            Image d;
            src.getROI(d, i, j, 3, 3);
            Image t = transformToImage();

            a.at(i, j) = (float)((d * t).sum()) / value;

        }
    }

    dst = a;
}



//---------------------Drawing---------------------//


/**
* @brief Draws a circle on an image
* 
* @param img: The image to draw on
* @param center: The center point of the circle
* @param radius: The radius of the circle
* @param color: The color of the circle
*/
void Drawing::drawCircle(Image& img, Point center, int radius, unsigned char color)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    while (y >= x) 
    {
        img.set_pixel(center.get_x() + x, center.get_y() + y, color);
        img.set_pixel(center.get_x() + y, center.get_y() + x, color);
        img.set_pixel(center.get_x() - x, center.get_y() + y, color);
        img.set_pixel(center.get_x() - y, center.get_y() + x, color);
        img.set_pixel(center.get_x() + x, center.get_y() - y, color);
        img.set_pixel(center.get_x() + y, center.get_y() - x, color);
        img.set_pixel(center.get_x() - x, center.get_y() - y, color);
        img.set_pixel(center.get_x() - y, center.get_y() - x, color);

        if (d < 0) 
        {
            d = d + 4 * x + 6;
        }
        else 
        {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}


/**
 * @brief Draws a straight line on the given image between two points with the given color.
 *
 * This function implements the Bresenham's line algorithm to draw a straight line between two
 * points on a raster display (a grid of X and Y coordinates on a display place). It uses integer arithmetic to avoid 
 * floating-point calculations, and works by minimizing the error between the desired line and the line that is being drawn.
 *
 * @param img: The image on which to draw the line.
 * @param p1: The starting point of the line.
 * @param p2: The ending point of the line.
 * @param color: The color to use for the line.
 */
void Drawing::drawLine(Image& img, Point p1, Point p2, unsigned char color)
{
    // Get the x and y coordinates of the two points
    int x1 = p1.get_x();
    int y1 = p1.get_y();
    int x2 = p2.get_x();
    int y2 = p2.get_y();

    // Calculate the absolute differences in x and y coordinates
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    // Determine the sign of the x and y directions
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    // Calculate the initial error
    int err = dx - dy;

    // Bresenham's line algorithm
    // Loop through each pixel on the line between the two points
    while (true)
    {
        // Set the color of the current pixel to the given color
        img.set_pixel(x1, y1, color);

        // Check if the end point has been reached
        if (x1 == x2 && y1 == y2)
        {
            // Exit the loop
            break;
        }

        // Calculate the double error
        int e2 = 2 * err;

        // Update the error and x coordinate if the error is greater than -dy
        if (e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        // Update the error and y coordinate if the error is less than dx
        if (e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}


/**
 * @brief Draws a rectangle on the given image with the given color.
 *
 * This function draws a rectangle on the given image using the given color. The rectangle is
 * defined by its top-left corner, width, and height.
 *
 * @param img: The image on which to draw the rectangle.
 * @param r: The rectangle to draw.
 * @param color: The color to use for the rectangle.
 */
void Drawing::drawRectangle(Image& img, Rectangle r, unsigned char color)
{
    // Get the coordinates and dimensions of the rectangle
    int x = r.get_x();
    int y = r.get_y();
    int w = r.get_width();
    int h = r.get_height();

    // Draw the top and bottom lines of the rectangle
    drawLine(img, Point(x, y), Point(x + w, y), color);
    drawLine(img, Point(x, y + h), Point(x + w, y + h), color);

    // Draw the left and right lines of the rectangle
    drawLine(img, Point(x, y), Point(x, y + h), color);
    drawLine(img, Point(x + w, y), Point(x + w, y + h), color);
}


/**
 * @brief Draws a rectangle on the given image with the given color.
 *
 * This function draws a rectangle on the given image using the given color. The rectangle is
 * defined by its top-left and bottom-right points.
 *
 * @param img: The image on which to draw the rectangle.
 * @param tl: The top-left point of the rectangle.
 * @param br: The bottom-right point of the rectangle.
 * @param color: The color to use for the rectangle.
 */
void Drawing::drawRectangle(Image& img, Point tl, Point br, unsigned char color)
{
    // Get the x and y coordinates of the top-left and bottom-right points
    int x1 = tl.get_x();
    int y1 = tl.get_y();
    int x2 = br.get_x();
    int y2 = br.get_y();

    // Calculate the width and height of the rectangle
    int w = x2 - x1;
    int h = y2 - y1;

    // Draw the top and bottom lines of the rectangle
    drawLine(img, Point(x1, y1), Point(x2, y1), color);
    drawLine(img, Point(x1, y2), Point(x2, y2), color);

    // Draw the left and right lines of the rectangle
    drawLine(img, Point(x1, y1), Point(x1, y2), color);
    drawLine(img, Point(x2, y1), Point(x2, y2), color);
}