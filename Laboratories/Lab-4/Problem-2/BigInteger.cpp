#include "BigInteger.h"

#include <cctype> // for isdigit
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

BigInteger::BigInteger()
{
	this->digits = nullptr;
	this->num_digits = 0;
	this->sign = 0;
}

BigInteger::BigInteger(std::string s)
{
	this->num_digits = s.size();

	switch (s[0])
	{
	case '0':
		this->digits = new int[num_digits]();
		this->sign = 0;
		break;
	case '-':
		this->digits = new int[num_digits - 1]();
		s.erase(0, 1);
		this->num_digits--;
		this->sign = -1;
		break;
	case'+':
		this->digits = new int[num_digits - 1]();
		s.erase(0, 1);
		this->num_digits--;
		this->sign = 1;
		break;
	default:
		this->digits = new int[num_digits]();
		this->sign = 1;
		break;
	}

	int t = 0;

	for (int i = 0; i < this->num_digits; i++)
	{
		if (!isdigit(s[i])) throw("error");
		*(this->digits + t) = (int)(s[i] - '0');
		t++;
	}
}

BigInteger::BigInteger(const BigInteger& N)
{
	this->digits = new int[N.num_digits] { 0 };
	this->num_digits = N.num_digits;
	this->sign = N.sign;

	for (int i = 0; i < N.num_digits; i++)
		this->digits[i] = N.digits[i];
}

BigInteger::~BigInteger()
{
	delete[] digits;
}

void BigInteger::display()
{
	for (int i = 0; i < this->num_digits; i++)
		std::cout << this->digits[i] << " ";
}

BigInteger& BigInteger::operator=(const BigInteger& N)
{
	if (this == &N)
		return *this;

	delete[] this->digits;

	this->digits = new int[N.num_digits] { 0 };
	this->num_digits = N.num_digits;
	this->sign = N.sign;

	for (int i = 0; i < N.num_digits; i++)
		this->digits[i] = N.digits[i];

	return *this;
}

int BigInteger::sgn() const
{
	return this->sign;
}

void BigInteger::negate()
{
	this->sign *= -1;
}

BigInteger& BigInteger::operator++()	//pre-increment
{
	BigInteger a = BigInteger("1");
	if (this->sign > -1)
		*this = this->add(a);

	else
		*this = this->sub(a);
	return *this;
}

BigInteger BigInteger::operator++(int t)	//post-increment
{
	BigInteger a = BigInteger("1");
	BigInteger copy = *this;
	*this = this->add(a);
	return copy;
}

BigInteger BigInteger::add(const BigInteger& N) const
{
	BigInteger result;

	int t1 = this->num_digits - 1;
	int t2 = N.num_digits - 1;
	result.digits = new int[std::max(t1 + 1, t2 + 1)] { 0 };
	result.num_digits = std::max(t1 + 1, t2 + 1);
	int r = result.num_digits - 1;

	while (t1 >= 0 && t2 >= 0)
	{
		result.digits[r] = this->digits[t1] + N.digits[t2];
		r--;
		t1--;
		t2--;
	}
	while (t1 >= 0)
	{
		result.digits[r] = this->digits[t1];
		r--;
		t1--;
	}
	while (t2 >= 0)
	{
		result.digits[r] = N.digits[t2];
		r--;
		t2--;
	}

	return result;
}

BigInteger BigInteger::sub(const BigInteger& N) const
{
	BigInteger result;

	int t1 = this->num_digits - 1;
	int t2 = N.num_digits - 1;
	result.digits = new int[std::max(t1 + 1, t2 + 1)] { 0 };
	result.num_digits = std::max(t1 + 1, t2 + 1);
	int r = result.num_digits - 1;

	while (t1 >= 0 && t2 >= 0)
	{
		result.digits[r] = this->digits[t1] + N.digits[t2];
		r--;
		t1--;
		t2--;
	}
	while (t1 >= 0)
	{
		result.digits[r] = this->digits[t1];
		r--;
		t1--;
	}
	while (t2 >= 0)
	{
		result.digits[r] = N.digits[t2];
		r--;
		t2--;
	}

	return result;
}

int BigInteger::compare(const BigInteger& N) const
{
	if (this->sign < N.sign)
		return -1;

	else if (this->sign > N.sign)
		return 1;
	if (this->num_digits < N.num_digits)
		return -1;
	else if (this->num_digits > N.num_digits)
		return 1;
	else
	{
		for (int i = 0; i < this->num_digits; i++)
		{
			if (this->digits[i] < N.digits[i])
				return -1;
			else if (this->digits[i] > N.digits[i])
				return 1;
		}
		return 0;
	}
}

bool operator==(const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == 0)
		return true;
	return false;
}

bool operator<(const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == -1)
		return true;
	return false;
}

bool operator<=(const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == 0 || A.compare(B) == -1)
		return true;
	return false;
}

bool operator>(const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == 1)
		return true;
	return false;
}

bool operator>=(const BigInteger& A, const BigInteger& B)
{
	if (A.compare(B) == 0 || A.compare(B) == 1)
		return true;
	return false;
}

BigInteger operator+(const BigInteger& A, const BigInteger& B)
{
	return A.add(B);
}

BigInteger operator-(const BigInteger& A, const BigInteger& B)
{
	return A.sub(B);
}

std::ostream& operator<<(std::ostream& out, BigInteger N)
{
	out << N.to_string();
	return out;
}

BigInteger& BigInteger::operator+=(const BigInteger& N)
{
	*this = this->add(N);
	return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& N)
{
	*this = this->sub(N);
	return *this;
}

std::string BigInteger::to_string()
{
	std::string result;
	if (this->sign == -1)
		result += "-";
	for (int i = 0; i < num_digits; i++)
		result += std::to_string(this->digits[i]);
	return result;
}
