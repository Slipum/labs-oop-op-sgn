#ifndef MATRIX_H
#define MATRIX_H

#include <filesystem>
#include <initializer_list>
#include <iosfwd>
template <typename T>
class Iterator;

template <typename T>
class matrix
{
	unsigned int rows; // строк n
	unsigned int cols; // столбцов m
	T *arr;

public:
	friend class Iterator<T>;

	matrix(unsigned int n, unsigned int m);

	matrix(const matrix<T> &matr);

	matrix(matrix<T> &&matr);

	explicit matrix(std::initializer_list<std::initializer_list<T>> lst);

	~matrix();

	matrix<T> &operator=(const matrix<T> &matr);
	matrix<T> &operator+=(const matrix<T> &matr);
	matrix<T> &operator-=(const matrix<T> &matr);

	template <typename _T>
	friend matrix<_T> operator+(const matrix<_T> &m1, const matrix<_T> &m2);
	template <typename _T>
	friend matrix<_T> operator-(const matrix<_T> &m1, const matrix<_T> &m2);
	template <typename _T>
	friend matrix<_T> operator*(const matrix<_T> &m1, const matrix<_T> &m2);

	template <typename _T>
	friend matrix<_T> operator+(const matrix<_T> &m1, _T num);
	template <typename _T>
	friend matrix<_T> operator-(const matrix<_T> &m1, _T num);
	template <typename _T>
	friend matrix<_T> operator/(const matrix<_T> &m1, _T num);
	template <typename _T>
	friend matrix<_T> operator*(const matrix<_T> &m1, _T num);

	template <typename _T>
	friend std::ostream &operator<<(std::ostream &os, const matrix<_T> &matr);

	void set_elem(unsigned int i, unsigned int j, const T &elem);
	T &get_elem(unsigned int i, unsigned int j) const;
	T &operator()(unsigned int i, unsigned int j) const;

	bool is_square() const;

	unsigned int get_rows() const;
	unsigned int get_columns() const;

	Iterator<T> iterator_begin();
	Iterator<T> iterator_end();

	// для работы auto : matrix
	Iterator<T> begin();
	Iterator<T> end();
};

#endif // MATRIX_H
