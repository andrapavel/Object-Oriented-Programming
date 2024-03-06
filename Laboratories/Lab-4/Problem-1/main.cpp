#define _CRT_SECURE_DEBUG_NO_WARNINGS
#include <iostream>

using namespace std;

#include "complex_number.h"
#include "complex_test.h"

void display_mandelbrot(int width, int height, int max_its)
{

    const float x_start = -3.0f;
    const float x_fin = 1.0f;
    const float y_start = -1.0f;
    const float y_fin = 1.0f;

    double dx = (x_fin - x_start) / (width - 1);
    double dy = (y_fin - y_start) / (height - 1);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Complex z(0, 0);

            Complex c(x_start + x * dx, y_start + y * dy);
            
            int iteration = 0;

            while (z.magnitude() < 2 && ++iteration < max_its)
                z = Complex((z * z) + c);

            if (iteration == max_its)
            {
                cout << "*";
            }
            else
            {
                cout << "-";
            }

        }
        cout << endl;
    }
}

int main(int argc, char** argv) 
{
#if ENABLE_TESTS > 0
	run_complex_tests(false);
#endif

    display_mandelbrot(100, 25, 100);

	// on the stack
	Complex c1{ 35, 9 };
	Complex c2{ 10, 20 };
	//cout << c2.getReal() << '\n';

	// on the heap
	Complex* h1 = new Complex{};
	Complex* h2 = new Complex{ 4, 2.45 };
	//cout << h2->getReal() << '\n';

	//cout << c1 + c2 << '\n';
	return 0;
}