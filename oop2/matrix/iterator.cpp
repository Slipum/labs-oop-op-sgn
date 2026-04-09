#include "iterator.h"

template <typename T>
Iterator<T>::Iterator(matrix<T> &container_obj) : ptr(&container_obj.get_elem(0, 0)), end_prt(container_obj.arr + container_obj.rows * container_obj.cols) {} // конструктор, принимающий объект контейнерного класса, который необходимо обойти с помощью данного итератора

template <typename T>
Iterator<T>::Iterator(T *curr) : ptr(curr) {}

template <typename T>
Iterator<T> &Iterator<T>::next()
{ // перейти к следующему объекту в контейнере
	ptr++;
	return *this;
}

template <typename T>
T Iterator<T>::value()
{ // получить значение текущего объекта в контейнере
	return *ptr;
}

template <typename T>
bool Iterator<T>::is_end()
{ // указывает ли итератор на конечный фиктивный элемент контейнера, следующий за последним реальным. Нужен для определения конца итерирования
	return ptr == end_prt;
}

template <typename T>
Iterator<T> &Iterator<T>::operator++()
{ // префиксный инкремент, эквивалентен next()
	return this->next();
}

template <typename T>
T &Iterator<T>::operator*()
{ // оператор разыменования, эквивалентен value()
	return *ptr;
}

template <typename T>
bool Iterator<T>::operator==(const Iterator &b) const
{ // оператор сравнения
	return ptr == b.ptr;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator &b) const
{ // оператор сравнения
	return ptr != b.ptr;
}

template class Iterator<int>;
template class Iterator<float>;
template class Iterator<double>;