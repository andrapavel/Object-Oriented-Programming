#include <assert.h>
#include <iostream>
using namespace std;

// -------------------------------------------------------------------------------------------
// Dynamic Array
// -------------------------------------------------------------------------------------------
template <class T>
class Array
{
private:
    int m_length;
    T *m_data;

public:
    Array()
    {
        m_length = 0;
        m_data = nullptr;
    }

    Array(int length)
    {
        m_data = new T[length];
        m_length = length;
    }

    Array(const Array& a) = delete;

    ~Array()
    {
        delete[] m_data;
    }

    void Erase()
    {
        delete[] m_data;
        // always set to nullptr after memory free!!!
        m_data = nullptr;
        m_length = 0;
    }


    T& operator[](int index)
    {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }

    int getLength(); // templated getLength() function defined below
};

// notice: Array<T>:: instead of Array:: as we normaly write
template <typename T>
int Array<T>::getLength() { return m_length; } // member functions defined outside the class need their own template declaration


void testDynamicArray() {
    Array<int> intArray(12);
    Array<double> doubleArray(12);
    //std::vector<int> v;

    for (int idx = 0; idx < intArray.getLength(); ++idx)
    {
        intArray[idx] = idx;
        doubleArray[idx] = idx * 2 + idx / 10.0;
    }

    for (int count = intArray.getLength() - 1; count >= 0; --count)
        std::cout << intArray[count] << "\t" << doubleArray[count] << '\n';
}

// -------------------------------------------------------------------------------------------
// end Dynamic Array
// -------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------
// Static Array
// -------------------------------------------------------------------------------------------

template <class T, int size> // size is the non-type parameter
class StaticArray // std::array
{
private:
    // The non-type parameter controls the size of the array
    T m_array[size]; // 
   // T m_array[10]; // T m_array[109];  T m_array[1000];\

public:
    T* getArray(){return m_array;}


    T& operator[](int index)
    {
        return m_array[index];
    }
};

void testStaticArray() {
    const int sz = 10;
    // declare an integer array with room for sz integer
    StaticArray<int, 10> intArrayS;

    for (int idx = 0; idx < sz; ++idx)
        intArrayS[idx] = idx;

    for (int idx = sz - 1; idx >= 0; --idx)
        std::cout << intArrayS[idx] << " ";
    std::cout << '\n';

    // declare a double buffer with room for 4 doubles
    StaticArray<double, 4> doubleArrayS;

    for (int idx = 0; idx < 4; ++idx)
        doubleArrayS[idx] = idx + 0.5;

    for (int idx = 0; idx < 4; ++idx)
        std::cout << doubleArrayS[idx] << ' ';
    std::cout << '\n';
}

// -------------------------------------------------------------------------------------------
// end Static Array
// -------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------
// Template specialization
// -------------------------------------------------------------------------------------------

// class template: "base" template
template <class T>
class DummyContainer {
    T m_element;
public:
    DummyContainer (T arg) {m_element=arg;}
    T increase () {return ++m_element;}

    T element() const {return m_element;}
};

// class template specialization:
template <>
class DummyContainer <char> {
    char m_element;
public:
    DummyContainer (char arg) {m_element=arg;}
    char increase ()
    {
        if ((m_element >='a')&&(m_element<='z'))
            m_element+='A'-'a';
        return m_element;
    }
    char element() const {return m_element;}
};

void testTemplateSpecialization() {
    DummyContainer<int> intV (7);
    DummyContainer<char> charV ('a');
    cout <<intV.element();
    cout<<"->increased int="<<intV.increase() << endl;
    cout << charV.element();
    cout<< "->increased char="<<charV.increase() << endl;
}

// -------------------------------------------------------------------------------------------
// end Template specialization
// -------------------------------------------------------------------------------------------
int main(){

  //  testDynamicArray();
   // getchar();

   // testStaticArray();
    //getchar();

    testTemplateSpecialization();
        
  

    return 0;
}
