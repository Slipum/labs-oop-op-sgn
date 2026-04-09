#ifndef ITERATOR_H
#define ITERATOR_H
#include "matrix.h"
template <typename T>
class matrix;

template <typename T>
class Iterator
{
	T *ptr;
	T *end_prt;

public:
	Iterator(matrix<T> &container_obj);
	Iterator(T *curr);

	Iterator &next();
	T value();
	bool is_end();

	Iterator &operator++();
	T &operator*();

	bool operator==(const Iterator &b) const;
	bool operator!=(const Iterator &b) const;
};

#endif // ITERATOR_H