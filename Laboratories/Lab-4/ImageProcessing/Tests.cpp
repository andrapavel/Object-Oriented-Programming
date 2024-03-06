#include <cassert>
#include <sstream>
#include <iostream>

#include "Image.h"
#include "Size.h"


class ImageTest
{
public:
    static void runTests()
    {
        test_image_default_constructor();
        test_image_constructor();
        test_image_copy_constructor();
        test_image_destructor();
        test_load();
        test_save();
        test_image_operator_assign();
        test_image_addition();
        test_operator_plus_scalar();
        test_image_subtraction_operator();
        test_image_operator_minus_scalar();
        test_image_multiplication();
        test_multiplication_operator_scalar();
        test_get_ROI();
        test_get_ROI2();
        test_isEmpty();
        test_size();
        test_width();
        test_height();
        //test_at();
        //test_at2();
        //test_row();
        //test_operator_output();
        test_zeros();
        test_ones();

        std::cout << "All tests passed!";
    }

private:
    static void test_image_default_constructor()
    {
        Image image;

        assert(image.width() == 0);
        assert(image.height() == 0);
    }

    static void test_image_constructor()
    {
        // Test constructing an Image with valid dimensions
        unsigned int width = 10;
        unsigned int height = 5;
        Image img(width, height);
        assert(img.width() == width && img.height() == height);

        // Test constructing an Image with zero width
        width = 0;
        height = 5;
        assert((Image(width, height), "Image width cannot be zero"));

        // Test constructing an Image with zero height
        width = 10;
        height = 0;
        assert((Image(width, height), "Image height cannot be zero"));
    }

    static void test_image_copy_constructor()
    {
        // Test constructing a copy of an Image with valid dimensions and data
        unsigned int width = 2;
        unsigned int height = 2;
        Image img1(width, height);
        img1.set_pixel(0, 0, 255);
        img1.set_pixel(1, 0, 255);
        img1.set_pixel(0, 1, 255);
        img1.set_pixel(1, 1, 255);

        Image img2(img1);
        assert(img2.width() == img1.width() && img2.height() == img1.height());

        // Test constructing a copy of an Image with zero width
        width = 0;
        height = 5;
        assert((Image(width, height), "Image width cannot be zero"));

        // Test constructing a copy of an Image with zero height
        width = 10;
        height = 0;
        assert((Image(width, height), "Image height cannot be zero"));
    }

    static void test_image_destructor()
    {
        //??
    }

    static void test_load()
    {
        Image img(0, 0);
        bool success = img.load("test_image.pgm");
        assert(success == true);
        assert(img.width() == 512);
        assert(img.height() == 512);
        assert(img.get_pixel(0, 0) == 64);
        assert(img.get_pixel(256, 256) == 128);
        assert(img.get_pixel(511, 511) == 255);
    }

    static void test_save()
    {
        //??
    }

    static void test_image_operator_assign()
    {
        // Create two images
        Image img1(2, 2);
        img1.set_pixel(0, 0, 255);
        img1.set_pixel(0, 1, 255);
        img1.set_pixel(1, 0, 0);
        img1.set_pixel(1, 1, 0);

        Image img2(3, 3);
        img2.set_pixel(0, 0, 255);
        img2.set_pixel(0, 1, 0);
        img2.set_pixel(0, 2, 255);
        img2.set_pixel(1, 0, 0);
        img2.set_pixel(1, 1, 255);
        img2.set_pixel(1, 2, 0);
        img2.set_pixel(2, 0, 255);
        img2.set_pixel(2, 1, 0);
        img2.set_pixel(2, 2, 255);

        // Copy img1 to img2 using assignment operator
        img2 = img1;

        // Check if img1 and img2 are equal
        assert(img1.width() == img2.width());
        assert(img1.height() == img2.height());

        for (unsigned int i = 0; i < img1.height(); i++)
        {
            for (unsigned int j = 0; j < img1.width(); j++)
            {
                assert(img1.get_pixel(i, j) == img2.get_pixel(i, j));
            }
        }
    }

    static void test_image_addition()
    {
        // Create two 2x2 images with known pixel values
        Image img1(2, 2);
        img1.at(0, 0) = 100;
        img1.at(0, 1) = 50;
        img1.at(1, 0) = 25;
        img1.at(1, 1) = 200;

        Image img2(2, 2);
        img2.at(0, 0) = 50;
        img2.at(0, 1) = 100;
        img2.at(1, 0) = 175;
        img2.at(1, 1) = 25;

        // Add the two images together
        Image result = img1 + img2;

        // Check that the resulting image has the correct dimensions
        assert(result.width() == 2);
        assert(result.height() == 2);

        // Check that the pixel values of the resulting image are correct
        assert(result.at(0, 0) == 150);
        assert(result.at(0, 1) == 150);
        assert(result.at(1, 0) == 200);
        assert(result.at(1, 1) == 225);
    }

    static void test_operator_plus_scalar()
    {
        // Create an image with some initial values
        Image img(2, 2);
        img.set_pixel(0, 0, 100);
        img.set_pixel(0, 1, 150);
        img.set_pixel(1, 0, 200);
        img.set_pixel(1, 1, 250);

        // Add a scalar value to the image
        Image result = img + 50;

        // Verify that the result image has the correct values
        assert(result.get_pixel(0, 0) == 150);
        assert(result.get_pixel(0, 1) == 200);
        assert(result.get_pixel(1, 0) == 250);
        assert(result.get_pixel(1, 1) == 255);

        // Add a negative scalar value to the image
        result = img + (-50);

        // Verify that the result image has the correct values
        assert(result.get_pixel(0, 0) == 50);
        assert(result.get_pixel(0, 1) == 100);
        assert(result.get_pixel(1, 0) == 150);
        assert(result.get_pixel(1, 1) == 200);

        // Add a scalar value that would cause overflow
        result = img + 300;

        // Verify that the result image has the correct values
        assert(result.get_pixel(0, 0) == 255);
        assert(result.get_pixel(0, 1) == 255);
        assert(result.get_pixel(1, 0) == 255);
        assert(result.get_pixel(1, 1) == 255);
    }

    static void test_image_subtraction_operator()
    {
        // Create two images with the same dimensions
        Image img1(2, 2);
        img1.set_pixel(0, 0, 100);
        img1.set_pixel(0, 1, 150);
        img1.set_pixel(1, 0, 200);
        img1.set_pixel(1, 1, 250);

        Image img2(2, 2);
        img2.set_pixel(0, 0, 50);
        img2.set_pixel(0, 1, 100);
        img2.set_pixel(1, 0, 150);
        img2.set_pixel(1, 1, 200);

        // Subtract img2 from img1
        Image result = img1 - img2;

        // Verify that the result image has the correct values
        assert(result.get_pixel(0, 0) == 50);
        assert(result.get_pixel(0, 1) == 50);
        assert(result.get_pixel(1, 0) == 50);
        assert(result.get_pixel(1, 1) == 50);

        // Subtract img1 from img2 (this should return an empty image)
        result = img2 - img1;

        // Verify that the result image is empty
        assert(result.width() == 0);
        assert(result.height() == 0);
    }

    static void test_image_operator_minus_scalar()
    {
        // Create an image
        Image img(2, 2);
        img.set_pixel(0, 0, 100);
        img.set_pixel(0, 1, 150);
        img.set_pixel(1, 0, 200);
        img.set_pixel(1, 1, 250);

        // Subtract a scalar from the image
        Image result = img - 50;

        // Verify that the result image has the correct values
        assert(result.get_pixel(0, 0) == 50);
        assert(result.get_pixel(0, 1) == 100);
        assert(result.get_pixel(1, 0) == 150);
        assert(result.get_pixel(1, 1) == 200);

        // Subtract a larger scalar from the image
        result = img - 300;

        // Verify that the result image has the correct values
        assert(result.get_pixel(0, 0) == 0);
        assert(result.get_pixel(0, 1) == 0);
        assert(result.get_pixel(1, 0) == 0);
        assert(result.get_pixel(1, 1) == 0);

        // Subtract a negative scalar from the image
        result = img - (-50);

        // Verify that the result image has the correct values
        assert(result.get_pixel(0, 0) == 150);
        assert(result.get_pixel(0, 1) == 200);
        assert(result.get_pixel(1, 0) == 250);
        assert(result.get_pixel(1, 1) == 255);
    }

    static void test_image_multiplication()
    {
        Image img1(3, 3);
        img1.at(0, 0) = 1;
        img1.at(0, 1) = 2;
        img1.at(0, 2) = 3;
        img1.at(1, 0) = 4;
        img1.at(1, 1) = 5;
        img1.at(1, 2) = 6;
        img1.at(2, 0) = 7;
        img1.at(2, 1) = 8;
        img1.at(2, 2) = 9;

        Image img2(3, 3);
        img2.at(0, 0) = 9;
        img2.at(0, 1) = 8;
        img2.at(0, 2) = 7;
        img2.at(1, 0) = 6;
        img2.at(1, 1) = 5;
        img2.at(1, 2) = 4;
        img2.at(2, 0) = 3;
        img2.at(2, 1) = 2;
        img2.at(2, 2) = 1;

        Image result = img1 * img2;

        assert(result.at(0, 0) == 9);
        assert(result.at(0, 1) == 16);
        assert(result.at(0, 2) == 21);
        assert(result.at(1, 0) == 24);
        assert(result.at(1, 1) == 25);
        assert(result.at(1, 2) == 24);
        assert(result.at(2, 0) == 21);
        assert(result.at(2, 1) == 16);
        assert(result.at(2, 2) == 9);
    }

    static void test_multiplication_operator_scalar()
    {
        // Create a test image
        Image image(3, 3);

        // Multiply the image by a scalar
        Image result = image * 2;

        // Check that the result has the correct dimensions
        assert(result.width() == 3);
        assert(result.height() == 3);

        // Check that each pixel value in the result is correct
        assert(result.at(0, 0) == 200);
        assert(result.at(0, 1) == 100);
        assert(result.at(0, 2) == 255);
        assert(result.at(1, 0) == 150);
        assert(result.at(1, 1) == 250);
        assert(result.at(1, 2) == 255);
        assert(result.at(2, 0) == 255);
        assert(result.at(2, 1) == 200);
        assert(result.at(2, 2) == 100);
    }

    static void test_get_ROI()
    {
        // Create an image with dimensions 4x4 and fill it with zeros
        Image img(4, 4);
        for (unsigned int i = 0; i < 4; i++)
            for (unsigned int j = 0; j < 4; j++)
                img.at(i, j) = 0;

        // Set the pixels in the top-left 2x2 region to 1
        for (unsigned int i = 0; i < 2; i++)
            for (unsigned int j = 0; j < 2; j++)
                img.at(i, j) = 1;

        // Define a ROI rectangle that covers the top-left 2x2 region
        Rectangle roiRect(0, 0, 2, 2);

        // Extract the ROI and store it in a new image
        Image roiImg;
        bool success = img.getROI(roiImg, roiRect);

        // Assert that the ROI extraction was successful
        assert(success == true);

        // Assert that the dimensions of the ROI image are correct
        assert(roiImg.width() == 2 && roiImg.height() == 2);

        // Assert that the pixels in the ROI image are correct
        assert(roiImg.at(0, 0) == 1 && roiImg.at(0, 1) == 1 &&
            roiImg.at(1, 0) == 1 && roiImg.at(1, 1) == 1);
    }

    static void test_get_ROI2()
    {
        // Create an image with dimensions 4x4 and fill it with zeros
        Image img(4, 4);
        for (unsigned int i = 0; i < 4; i++)
            for (unsigned int j = 0; j < 4; j++)
                img.at(i, j) = 0;

        // Set the pixels in the top-left 2x2 region to 1
        for (unsigned int i = 0; i < 2; i++)
            for (unsigned int j = 0; j < 2; j++)
                img.at(i, j) = 1;

        // Define the coordinates and dimensions of the ROI rectangle
        unsigned int x = 0, y = 0, width = 2, height = 2;

        // Extract the ROI and store it in a new image
        Image roiImg;
        bool success = img.getROI(roiImg, x, y, width, height);

        // Assert that the ROI extraction was successful
        assert(success == true);

        // Assert that the dimensions of the ROI image are correct
        assert(roiImg.width() == 2 && roiImg.height() == 2);

        // Assert that the pixels in the ROI image are correct
        assert(roiImg.at(0, 0) == 1 && roiImg.at(0, 1) == 1 &&
            roiImg.at(1, 0) == 1 && roiImg.at(1, 1) == 1);
    }

    static void test_isEmpty()
    {
        // Create an empty image
        Image emptyImage(0, 0);

        // Check that isEmpty() returns true for an empty image
        assert(emptyImage.isEmpty() == true);

        // Create an image with non-zero dimensions
        Image nonEmptyImage(100, 200);

        // Check that isEmpty() returns false for a non-empty image
        assert(nonEmptyImage.isEmpty() == false);
    }

    static void test_size()
    {
        // Create an Image object with width=100 and height=50
        Image img(100, 50);

        // Call the size() method and store the returned Size object
        Size size = img.size();

        // Verify that the returned Size object has the expected width and height
        assert(size.width() == 100);
        assert(size.height() == 50);
    }
    
    static void test_width()
    {
        Image img(100, 50);

        // Call the width() method and store the returned value
        unsigned int width = img.width();

        // Verify that the returned width is equal to the expected value
        assert(width == 100);
    }

    static void test_height()
    {
        // Create an Image object with width=100 and height=50
        Image img(100, 50);

        // Call the height() method and store the returned value
        unsigned int height = img.height();

        // Verify that the returned height is equal to the expected value
        assert(height == 50);
    }

    static void test_at()
    {
        //??
    }

    static void test_at2()
    {
        //??
    }

    static void test_row()
    {
        //??
    }

    static void test_operator_output()
    {
        //??
    }

    static void test_zeros()
    {
        // Create a new image with width=100 and height=50
        Image img = Image::zeros(100, 50);

        // Verify that all pixels in the image are set to zero
        for (unsigned int y = 0; y < img.height(); y++)
        {
            const unsigned char* row = img.row(y);

            for (unsigned int x = 0; x < img.width(); x++)
                assert(row[x] == '0');
        }
    }

    static void test_ones()
    {
        // Create a new image with width=100 and height=50
        Image img = Image::ones(100, 50);

        // Verify that all pixels in the image are set to one
        for (unsigned int y = 0; y < img.height(); y++)
        {
            const unsigned char* row = img.row(y);

            for (unsigned int x = 0; x < img.width(); x++)
                assert(row[x] == '1');
        }
    }
};