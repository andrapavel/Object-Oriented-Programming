#include <iostream>
#include <string>
using std::cout;


class Coin {
public:
	Coin(int v = 0, std::string mat = "", float w = 0) :m_value{ v }, m_material{ mat }, m_weight{ w }{}

	bool operator<(const Coin& other) {
		return m_value < other.m_value;
	}
	friend bool operator>(const Coin& c1, const Coin& c2);
	friend std::ostream& operator<<(std::ostream& os, const Coin& c2);

	void print() { std::cout << "coin of value " << m_value << " made of " << m_material << " with weight " << m_weight << std::endl; }
private:
	int m_value;
	std::string m_material;
	float m_weight;
};
std::ostream& operator<<(std::ostream& os, const Coin& c2){
	os << "Coin with val" << c2.m_value << std::endl;
	return os;

}

bool operator>(const Coin& c1, const Coin& c2) {
	return c1.m_value > c2.m_value;
}

//class Stundet;
//int min(int m1, int m2);
//double min(double m1, double m2);
//Stundet min(Stundet s1, Stundet s2);
//Coin min(Coin s1, Coin s2);

template<typename T>
T minval(T v1, T v2) {
	if (v1 < v2)
		return v1;
	return v2;
}

template<typename T>
T maxval(T v1, T v2) {
	if (v1 > v2)
		return v1;
	return v2;
}

template<typename T>
void printmaxval(T v1, T v2) {
	cout << "max is:" << std::endl;
	if (v1 > v2)
		cout << v1;
	else
		cout << v2;
	cout << std::endl;
}

template<>
void printmaxval<char>(char v1, char v2) {
	cout << "max is:" << std::endl;
	if (v1 > v2)
		cout << v1 <<" ascii: "<<(int)v1;
	else
		cout << v2 << " ascii: " << (int)v2;
	cout << std::endl;
}

template <class T>
T averaget(T* array, int length)
{
	T sum(0); 
	for (int count{ 0 }; count < length; ++count)
		sum += array[count];

	sum /= length;
	return sum;
}

template <class T, typename V>
V average(T* array, int length)
{
	V sum{ 0 };
	for (int count{ 0 }; count < length; ++count)
		sum += array[count];

	sum /= length;
	return sum;
}

int main() {
	float f1 = 10, f2 = 0.5;
	int i1 = 3, i2 = 4;
	char a1 = 'A', a2 = 'a';
	Coin c1{ 10, "steel-nickel", 30 };
	Coin c2{ 50, "copper-nickel", 60 };
	printmaxval(f1, f2);
	printmaxval(i1, i2);
	printmaxval(c1, c2);
	printmaxval(a1, a2);
	/*getchar();
	float maxf1f2 = maxval<float>(f1, f2);
	float minf1f2 = minval<float>(f1, f2);


	int maxi1i2 = maxval<int>(i1, i2);
	int mini1i2 = minval<int>(i1, i2);


	Coin maxc1c2 = maxval(c1, c2);
	Coin minc1c2 = minval(c1, c2);

	cout << "i1 = " << i1 << "; i2 = " << i2 << std::endl;
	cout << "\t" << "maximum value is " << maxi1i2 << std::endl;
	cout << "\t" << "minimum value is " << mini1i2 << std::endl;


	cout << "f1 = " << f1 << "; f2 = " << f2 << std::endl;
	cout << "\t" << "maximum value is " << maxf1f2 << std::endl;
	cout << "\t" << "minimum value is " << minf1f2 << std::endl;


	c1.print();
	c2.print();
	cout << "\t" << "maximum value is ";
	maxc1c2.print();
	cout << "\t" << "minimum value is ";
	minc1c2.print();

	getchar();*/
	int array1[]{ 4, 3, 2, 1, 4 };
	std::cout << "array 1: averaget " << averaget(array1, 5) << '\n';

	//getchar();

	double array2[]{ 3.12, 3.45, 9.23, 6.34 };
	std::cout << "array 1: average " << average<int, double>(array1, 5) << '\n';
	std::cout << "array 1: average int" << average<int, int>(array1, 5) << '\n';
	std::cout << "array 2: average: " << average<double, double>(array2, 4) << '\n';


	return 0;
}
