#pragma once

#include<string>
#include<iostream>


//class DynamicArray
//{
//public:
//	DynamicArray();
//	DynamicArray(const DynamicArray& other);
//
//	~DynamicArray();
//
//	DynamicArray& operator=(const DynamicArray& other);
//
//private:
//	int* arr;
//	int capacity;
//	int dimension;
//};

class BigInteger 
{

public:
	BigInteger();
	BigInteger(std::string s);

	BigInteger(const BigInteger& N);
	~BigInteger();

	void display();

	BigInteger& operator=(const BigInteger& N);

	int sgn()const;
	void negate();

	void normalize();
	BigInteger abs() const;

	BigInteger& operator++();
	BigInteger operator++(int t);

	friend bool operator==(const BigInteger& A, const BigInteger& B);
	friend bool operator<(const BigInteger& A, const BigInteger& B);
	friend bool operator<=(const BigInteger& A, const BigInteger& B);
	friend bool operator>(const BigInteger& A, const BigInteger& B);
	friend bool operator>=(const BigInteger& A, const BigInteger& B);

	friend BigInteger operator+(const BigInteger& A, const BigInteger& B);
	BigInteger& operator+=(const BigInteger& N);

	friend BigInteger operator-(BigInteger& A, BigInteger& B);
	BigInteger& operator-=(const BigInteger& N);

	std::string to_string();
	friend std::ostream& operator<<(std::ostream& out, BigInteger N);

private:
	int* digits;
	int num_digits;
	int sign;

	BigInteger add(const BigInteger& N)const;
	BigInteger sub(const BigInteger& N)const;

	int compare(const BigInteger& N)const;

};
