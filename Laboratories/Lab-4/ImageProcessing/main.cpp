#include <iostream>
#include <cassert>

#include "image.h"
#include "Size.h"
#include "Rectangle.h"
#include "Point.h"
#include "Tests.cpp"


int main(int argc, char** argv) 
{

	//ImageTest::runTests();
	Image Img;
	Img.load("Image.ppm");
	Img.save("NewImage.ppm");

    std::cout << Img;

    /*Image NewImg(Img.width(), Img.height());
    GammaCorrection g;
    g.set_gamma(2);
    g.process(Img, NewImg);
    std::cout << NewImg;*/

    BrightnessAndContrast AlphaBeta;
    Image NewImg(Img.width(), Img.height());

    AlphaBeta.set_alpha(2);
    AlphaBeta.set_beta(1);

    AlphaBeta.process(Img, NewImg);

    std::cout << NewImg;

    /*Image NewImg;
    ImageConvolution k;
    k.set_kernel("IK");
    k.process(Img, NewImg);
    std::cout << NewImg;*/

    /*ImageConvolution k;
    k.set_kernel("IK");

    Image y = k.transformToImage();
    std::cout << "AICI"<<std::endl;

    std::cout << y;*/

    /*Rectangle A(2,2,2,2), B(2, 3, 1, 1);
    std::cout << (A | B);*/

    /*Rectangle A(2, 2, 2, 2);

    Drawing a;
    Point p1(0, 0), p2(0, 4), c(10, 4);
    a.drawLine(Img, p1, p2, 0);
    Img.save("NewImage.ppm");*/

    //a.drawRectangle(Img, A, 0);
    //a.drawCircle(Img, c, 2, 0);
    //a.drawRectangle(Img, p1, c, 0);
    //Img.save("NewImage.ppm");

    return 0;
}




