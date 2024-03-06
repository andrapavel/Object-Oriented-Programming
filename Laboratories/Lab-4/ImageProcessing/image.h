#pragma once

#include <iostream>
#include <vector>

#include "Rectangle.h"
#include "Size.h"
#include "Point.h"

  
class Image
{
public:

    Image();
    Image(unsigned int w, unsigned int h);
    Image(const Image& other);

    ~Image();

    unsigned char get_pixel(unsigned int x, unsigned int y) const;

    void set_pixel(unsigned int x, unsigned int y, unsigned char value);

    bool load(std::string imagePath);
    bool save(std::string imagePath);

    void set_height(unsigned h);
    void set_width(unsigned w);

    Image& operator=(const Image& other);
    Image operator+(const Image& i);
    Image operator+(const int scalar);
    Image operator-(const Image& i);
    Image operator-(const int scalar);
    Image operator*(const Image& i);
    Image operator*(const int scalar);

    bool getROI(Image& roiImg, Rectangle roiRect);
    bool getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    bool isEmpty() const;

    Size size() const;

    unsigned int width() const;
    unsigned int height() const;

    unsigned char& at(unsigned int x, unsigned int y);
    unsigned char& at(Point pt);

    unsigned char* row(int y);

    void release();

    friend std::ostream& operator<<(std::ostream& os, const Image& dt);

    static Image zeros(unsigned int width, unsigned int height);
    static Image ones(unsigned int width, unsigned int height);

    int sum();

private:
    unsigned char** m_data;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int maxVal;
    Size m_size;

    //friend class ImageTests;
};


class ImageProcessing
{
public:
    virtual void process(Image& src, Image& dst) = 0;
};


class BrightnessAndContrast : ImageProcessing
{
public:
    BrightnessAndContrast();

    int get_alpha();
    int get_beta();

    void set_alpha(int a);
    void set_beta(int b);

    void process(Image& src, Image& dst) override;

private:
    int alpha = 1;
    int beta = 0;
    int AlphaBeta[2];
};


class GammaCorrection : ImageProcessing
{
public:
    GammaCorrection();

    float get_gamma();

    void set_gamma(float g);

    void process(Image& src, Image& dst) override;

private:
    float gamma = 1; 

};


class ImageConvolution : ImageProcessing
{
public:
    ImageConvolution();

    Image transformToImage();



    void set_kernel(std::string type);

    void process(Image& src, Image& dst) override;

private:
    int kernel[3][3];
    int value;


};

class Drawing : Image
{
public:
    void drawCircle(Image& img, Point center, int radius, unsigned char color);
    void drawLine(Image& img, Point p1, Point p2, unsigned char color);
    void drawRectangle(Image& img, Rectangle r, unsigned char color);
    void drawRectangle(Image& img, Point tl, Point br, unsigned char color);


};