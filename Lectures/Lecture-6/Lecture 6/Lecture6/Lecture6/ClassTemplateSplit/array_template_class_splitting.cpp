#include "array_template_class_splitting.h"
#include <assert.h>

template<class T>
void Array<T>::Erase()
{
    delete[] m_data;
    // always set to nullptr after memory free!!!
    m_data = nullptr;
    m_length = 0;
}

template <class T>
T &Array<T>::operator[](int index)
{
    assert(index >= 0 && index < m_length);
    return m_data[index];
}

template<class T>
int Array<T>::getLength() { return m_length; }



