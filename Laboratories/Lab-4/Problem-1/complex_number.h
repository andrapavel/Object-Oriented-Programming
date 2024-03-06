#pragma once
#include <string>
#include <fstream>

enum class DisplayType
{
	RECTANGULAR_FORM,
	POLAR_FORM,
};

static DisplayType DISPLAY_TYPE;

class Complex 
{

public:

	Complex();
	Complex(float r, float i);

	static void setDisplayType(DisplayType dt);
	static DisplayType getDisplayType();

	//GETTERS
	float getReal()const;
	float getImag()const;


	//SETTERS
	void setReal(float r);
	void setImag(float i);


	Complex conjugate() const;
	Complex add(Complex a) const;
	Complex subtract(Complex c) const;
	Complex multiply(Complex c) const;

	void multiply(float);

	bool equals(Complex other) const;

	float magnitude() const;
	float phase() const;
	void toPolar(float* r, float* theta) const;

	std::string toString() const;

	Complex operator+(const Complex& c)const;
	Complex operator-(const Complex& c)const;
	Complex operator*(const Complex& c)const;

	bool operator==(const Complex& c)const;
	bool operator!=(const Complex& c)const;

	friend std::ostream& operator<<(std::ostream& out, const Complex &c);
	friend std::istream& operator>>(std::istream& in, Complex& c);

private:
	float real, imag;
};
