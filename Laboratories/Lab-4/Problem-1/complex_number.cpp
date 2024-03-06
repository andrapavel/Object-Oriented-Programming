#include "complex_number.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cmath>

#define M_PI  3.1415926535f

using namespace std;


DisplayType Complex::getDisplayType()
{
	return DISPLAY_TYPE;
}

void Complex::setDisplayType(DisplayType dt)
{
	DISPLAY_TYPE = dt;
}

Complex::Complex() : real{0}, imag{0}
{

}

Complex::Complex(float r, float i)
{
	real = r;
	imag = i;
}


float Complex::getReal()const
{
	return this->real;
}

float Complex::getImag()const
{
	return this->imag;
}

void Complex::setReal(float r)
{
	real = r;
}

void Complex::setImag(float i)
{
	imag = i;
}

Complex Complex::conjugate() const
{
	Complex conjugate(real, -imag);
	return conjugate;
}

Complex Complex::add(Complex c) const
{
	return Complex(real + c.real, imag + c.imag);
}

Complex Complex::subtract(Complex c) const
{
	return Complex(real - c.real, imag - c.imag);
}

Complex Complex::multiply(Complex c) const
{
	return Complex(real * c.real - imag * c.imag, real * c.imag + imag * c.real);
}

void Complex::multiply(float s)
{
	real *= s;
	imag *= s;
}

bool Complex::equals(Complex other) const
{
	if (real == other.real && imag == other.imag)
		return true;
	return false;
}

float Complex::magnitude() const
{
	float magnitude = sqrt(real * real + imag * imag);
	return magnitude;
}

float Complex::phase() const
{
	float phase = atan2(imag, real);
	return phase;
}

void Complex::toPolar(float* r, float* theta) const
{
	*r = magnitude();
	*theta = phase();
}

std::string Complex::toString() const
{
	ostringstream sstr;
	sstr << std::setprecision(2) << std::fixed;

	DisplayType dt = getDisplayType();

	if (dt == DisplayType::RECTANGULAR_FORM)
	{
		if (real == 0 && imag == 0)
			sstr << "0";
		else
			sstr << real << showpos << imag << "i";
	}
	else
	{
		
		if (dt == DisplayType::POLAR_FORM && (real != 0 || imag != 0))
		{
			float r, theta;
			toPolar(&r, &theta);
			sstr << r << "*(cos(" << theta * 180/M_PI << ") + i*sin(" << theta * 180/M_PI << "))";
		}

		else if (real == 0 && imag == 0)
			sstr << "0";
	}

	return sstr.str();
}

Complex Complex::operator+(const Complex& c) const
{
	Complex result;
	result.real = real + c.real;
	result.imag = imag + c.imag;
	return result;
}

Complex Complex::operator-(const Complex& c) const
{
	Complex result;
	result.real = real - c.real;
	result.imag = imag - c.imag;
	return result;
}

Complex Complex::operator*(const Complex& c) const
{
	Complex result;
	result.real = real * c.real - imag * c.imag;
	result.imag = real * c.imag + imag * c.real;
	return result;
}

bool Complex::operator==(const Complex& c) const
{
	return real == c.real && imag == c.imag;
}

bool Complex::operator!=(const Complex& c) const
{
	return real != c.real || imag != c.imag;
}

ostream& operator<<(ostream& out, const Complex& c)
{	
	out << c.toString();
	return out;

}

istream& operator>>(istream& in, Complex& c)
{
	char sign;
	float real, imag;
	in >> real;

	if (in.peek() == '+')
	{
		in >> sign >> imag;
	}
	else if (in.peek() == '-')
	{
		in >> sign >> sign >> imag;
		imag = -imag;
	}
	else
		imag = 0;

	c.setReal(real);
	c.setImag(imag);

	return in;
}
