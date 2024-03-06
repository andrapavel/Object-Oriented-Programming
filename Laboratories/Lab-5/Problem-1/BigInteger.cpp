#include "BigInteger.h"

#include <cctype> // for isdigit
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

BigInteger::BigInteger()
{
	//this->digits = nullptr;
	this->num_digits = 1;
	this->digits = new int[num_digits]{0};
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

	if (this->sign)
		//*this = this->add(a);
		*this = *this + a;

	return *this;
}

BigInteger BigInteger::operator++(int t)	//post-increment
{
	BigInteger a = BigInteger("1");
	BigInteger copy = *this;

	//*this = this->add(a);
	*this = *this + a;

	return copy;
}

BigInteger BigInteger::add(const BigInteger& N) const
{
	BigInteger result;

	int t1 = this->num_digits - 1;
	int t2 = N.num_digits - 1;
	result.digits = new int[std::max(t1 + 1, t2 + 1) + 1] { 0 };  // Add one extra digit for carry-over
	result.num_digits = std::max(t1 + 1, t2 + 1) + 1;  // Add one extra digit for carry-over
	int r = result.num_digits - 1;

	int carry = 0;
	
	while (t1 >= 0 && t2 >= 0)
	{
		int sum = this->digits[t1] + N.digits[t2] + carry;
		carry = sum / 10;
		result.digits[r] = sum % 10;
		r--;
		t1--;
		t2--;
	}
	while (t1 >= 0)
	{
		int sum = this->digits[t1] + carry;
		carry = sum / 10;
		result.digits[r] = sum % 10;
		r--;
		t1--;
	}
	while (t2 >= 0)
	{
		int sum = N.digits[t2] + carry;
		carry = sum / 10;
		result.digits[r] = sum % 10;
		r--;
		t2--;
	}


	if (carry != 0)  // If there is a carry-over digit
	{
		result.digits[r] = carry;
	}
	else  // If there is no carry-over digit
	{
		// Shifts the result digits by one to the right, and removes the extra digit
		for (int i = 0; i < result.num_digits - 1; i++)
			result.digits[i] = result.digits[i + 1];

		result.num_digits--;
	}

	if (sign == N.sign)
	{
		result.sign = sign;
	}
	else if (abs() > N.abs())
	{
		if (sign == 1 && N.sign == -1)
			result.sign = sign;
		else if (sign == -1 && N.sign == 1)
			result.sign = sign;
	}
	else if (abs() < N.abs())
	{
		if (sign == 1 && N.sign == -1)
			result.sign = N.sign;
	}

	result.normalize(); // This line removes any leading zeros

	return result;
}


void BigInteger::normalize() 
{
	// Removes any leading zeros
	while (num_digits > 1 && digits[num_digits - 1] == 0) 
		num_digits--;
	
	bool negative = true;
	// If all digits are zero, it sets the number to zero
	if (num_digits == 1 && digits[0] == 0)
		negative = false;
}

BigInteger BigInteger::abs() const
{
	BigInteger result = *this;
	result.sign = 1;  // Set the sign of the result to positive
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

	int borrow = 0;

	while (t1 >= 0 && t2 >= 0)
	{
		int diff = this->digits[t1] - N.digits[t2] + borrow;
		if (diff < 0) 
		{
			diff += 10;
			borrow = -1;
		}
		else 
		{
			borrow = 0;
		}
		result.digits[r] = diff;
		r--;
		t1--;
		t2--;
	}
	while (t1 >= 0)
	{
		int diff = this->digits[t1] + borrow;
		if (diff < 0) 
		{
			diff += 10;
			borrow = -1;
		}
		else 
		{
			borrow = 0;
		}
		result.digits[r] = diff;
		r--;
		t1--;
	}
	while (t2 >= 0)
	{
		int diff = N.digits[t2] + borrow;
		if (diff < 0) 
		{
			diff += 10;
			borrow = -1;
		}
		else 
		{
			borrow = 0;
		}
		result.digits[r] = diff;
		r--;
		t2--;
	}

	result.normalize(); // This line removes any leading zeros

	
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
	else if (this->sign == N.sign)
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
	return A.compare(B) == 0;
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
	BigInteger result;
	
	
	if (A.sgn() == B.sgn())
	{
		if (A.abs() > B.abs())
		{
			result = A.add(B);
			result.sign = A.sign;
		}
		else if (A.abs() == B.abs())
		{
			for (int i = 0; i < result.num_digits; i++)
			{
				result.digits[i] = '0';
				result.sign = A.sign;
			}
		}
	}
	else if (A.sgn() != B.sgn())
	{
		if (A.abs() > B.abs())
		{
			result = A.sub(B);
			result.sign = A.sign;
		}
		else if (A.abs() < B.abs())
		{
			result = B.sub(A);
			result.sign = B.sign;
		}
	}

	return result;
	
}

BigInteger operator-(BigInteger& A, BigInteger& B)
{
	BigInteger result;


	if (A.sgn() == B.sgn())
	{
		if (A.abs() > B.abs())
		{
			result = A.sub(B);
			result.sign = A.sign;
		}
		else if (A.abs() == B.abs())
		{
			for (int i = 0; i < result.num_digits; i++)
			{
				result.digits[i] = '0';
			}
		}
		else if (A.abs() < B.abs())
		{
			result = A.sub(B);
			result.sign = -1 * A.sign;
			
		}

	}
	else if (A.sgn() == 1 && B.sgn() == -1)
	{
		if (A.abs() > B.abs())
		{
			if (A.sgn() == 1 && B.sgn() == -1)
			{
				result = A.sub(B);
				result.sign = A.sign;
			}
			else if (A.sgn() == 1 && B.sgn() == -1)
			{
				result = A.sub(B);
				result.sign = A.sign;
			}
		}
	}

	

	return result;
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
