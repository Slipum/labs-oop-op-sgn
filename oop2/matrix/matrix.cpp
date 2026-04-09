#include "matrix.h"
#include "iterator.h"
#include <stdexcept>

template <typename T>
matrix<T>::matrix(unsigned int n, unsigned int m) : rows(n), cols(m) { arr = new T[n * m]{}; };

template <typename T>
matrix<T>::matrix(const matrix<T> &matr)
{ // конструктор копирования
	rows = matr.rows;
	cols = matr.cols;
	arr = new T[rows * cols];
	for (unsigned int i = 0; i < rows * cols; ++i)
		arr[i] = matr.arr[i];
}

template <typename T>
matrix<T>::matrix(matrix<T> &&matr)
{ // конструктор перемещения
	rows = matr.rows;
	cols = matr.cols;
	arr = matr.arr;
	matr.arr = nullptr;
}
template <typename T>
matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> lst)
{ // конструктор со списком инициализации
	rows = lst.size();
	cols = lst.begin()->size();
	for (auto it : lst)
	{
		if (it.size() != cols)
			throw std::invalid_argument("matrix incorrect row size");
	}
	arr = new T[rows * cols];
	int i = 0;
	for (auto it : lst)
		for (auto jt : it)
		{
			arr[i++] = jt;
		}
}

template <typename T>
matrix<T>::~matrix() { delete[] arr; }

template <typename T>
matrix<T> &matrix<T>::operator=(const matrix<T> &matr)
{ // перегрузка оператора присваивания для двух матриц типа T
	if (this == &matr)
		return *this;

	delete[] arr;

	rows = matr.rows;
	cols = matr.cols;
	arr = new T[rows * cols]{};

	for (unsigned int i = 0; i < rows * cols; ++i)
		arr[i] = matr.arr[i];

	return *this;
}

template <typename T>
matrix<T> &matrix<T>::operator+=(const matrix<T> &matr)
{ // перегрузка оператора += для двух матриц типа T
	if (matr.cols != this->cols || matr.rows != this->rows)
		throw std::invalid_argument("matrix incorrect size");

	for (size_t i = 0; i < (matr.rows * matr.cols); i++)
		this->arr[i] += matr.arr[i];
	return *this;
}

template <typename T>
matrix<T> &matrix<T>::operator-=(const matrix<T> &matr)
{ // перегрузка оператора -= для двух матриц типа T
	if (matr.cols != this->cols || matr.rows != this->rows)
		throw std::invalid_argument("matrix incorrect size");

	for (size_t i = 0; i < (matr.rows * matr.cols); i++)
		this->arr[i] -= matr.arr[i];
	return *this;
}

template <typename _T>
matrix<_T> operator+(const matrix<_T> &m1, const matrix<_T> &m2)
{ // перегрузка оператора + для двух матриц
	if (m1.cols != m2.cols || m1.rows != m2.rows)
		throw std::invalid_argument("matrix incorrect size");

	for (size_t i = 0; i < (m1.rows * m1.cols); i++)
		m1.arr[i] += m2.arr[i];
	return m1;
}

template <typename _T>
matrix<_T> operator-(const matrix<_T> &m1, const matrix<_T> &m2)
{ // перегрузка оператора - для двух матриц
	if (m1.cols != m2.cols || m1.rows != m2.rows)
		throw std::invalid_argument("matrix incorrect size");

	for (size_t i = 0; i < (m1.rows * m1.cols); i++)
		m1.arr[i] -= m2.arr[i];
	return m1;
}

template <typename _T>
matrix<_T> operator*(const matrix<_T> &m1, const matrix<_T> &m2)
{ // перегрузка оператора * для двух матриц
	if (m1.cols != m2.rows)
		throw std::invalid_argument("matrix incorrect size");

	int rows = m1.rows;
	int cols = m2.cols;

	matrix<_T> result(rows, cols);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			for (int t = 0; t < m1.cols; t++)
				result.arr[i * cols + j] += m1.arr[i * m1.cols + t] * m2.arr[t * m2.cols + j];
	return result;
}

template <typename _T>
matrix<_T> operator+(const matrix<_T> &m1, _T num)
{ // перегрузка оператора + для сложения матрицы с числом
	for (size_t i = 0; i < m1.cols; i++)
		for (size_t j = 0; j < m1.rows; j++)
			if (i == j)
				m1.arr[i * m1.cols + j] += num;
	return m1;
}

template <typename _T>
matrix<_T> operator-(const matrix<_T> &m1, _T num)
{ // перегрузка оператора – для вычисления разности матрицы с числом
	for (size_t i = 0; i < m1.cols; i++)
		for (size_t j = 0; j < m1.rows; j++)
			if (i == j)
				m1.arr[i * m1.cols + j] -= num;
	return m1;
}

template <typename _T>
matrix<_T> operator/(const matrix<_T> &m1, _T num)
{ // перегрузка оператора / для вычисления частного матрицы с числом
	for (size_t i = 0; i < (m1.rows * m1.cols); i++)
		m1.arr[i] /= num;
	return m1;
}

template <typename _T>
matrix<_T> operator*(const matrix<_T> &m1, _T num)
{ // перегрузка оператора * для умножения матрицы с числом
	for (size_t i = 0; i < (m1.rows * m1.cols); i++)
		m1.arr[i] *= num;
	return m1;
}

template <typename _T>
std::ostream &operator<<(std::ostream &os, const matrix<_T> &matr)
{ // перегрузка оператора << для вывода класса в поток (cout к примеру)
	// for (size_t i = 0; i < matr.rows; i++)
	// {
	// 	for (size_t j = 0; j < matr.cols; j++)
	// 		os << matr.arr[i * matr.cols + j] << " ";
	// 	if (i + 1 < matr.rows)
	// 		os << "\n";
	// }
	os << matr.arr;
	return os;
}

template <typename T>
void matrix<T>::set_elem(unsigned int i, unsigned int j, const T &elem)
{ // метод изменения элемента матрицы по индексу
	if (i >= rows || j >= cols)
		throw std::out_of_range("Matrix index out of range");
	unsigned int curr = i * cols + j;
	for (unsigned int k = 0; k < rows * cols; k++)
		if (curr == k)
		{
			arr[k] = elem;
			return;
		}
	throw std::invalid_argument("Undefined element in matrix");
}

template <typename T>
T &matrix<T>::get_elem(unsigned int i, unsigned int j) const
{ // метод получения элемента матрицы по индексу
	if (i >= rows || j >= cols)
		throw std::out_of_range("Matrix index out of range");
	return arr[i * cols + j];
}

template <typename T>
T &matrix<T>::operator()(unsigned int i, unsigned int j) const { return get_elem(i, j); } // метод получения элемента по индексу через синтаксис круглых скобок matrix(i, j)

template <typename T>
bool matrix<T>::is_square() const { return rows == cols; } // метод проверки матрицы на квадратную || я добавил const, т к метод не изменяет параметров

template <typename T>
unsigned int matrix<T>::get_rows() const { return this->rows; } // метод получения числа строк матрицы

template <typename T>
unsigned int matrix<T>::get_columns() const { return this->cols; } // метод получения числа столбцов матрицы

template <typename T>
Iterator<T> matrix<T>::iterator_begin() { return Iterator<T>(*this); } // метод получения итератора на начало матрицы (первый элемент)

template <typename T>
Iterator<T> matrix<T>::iterator_end() { return Iterator<T>(arr + (rows * cols)); } // метод получения итератора на конец матрицы (конец - это фиктивный элемент, следующий за последним в матрицы)

template <typename T>
Iterator<T> matrix<T>::begin() { return this->iterator_begin(); }

template <typename T>
Iterator<T> matrix<T>::end() { return this->iterator_end(); }

template class matrix<int>;
template matrix<int> operator* <int>(const matrix<int> &, const matrix<int> &);
template matrix<int> operator+ <int>(const matrix<int> &, const matrix<int> &);
template matrix<int> operator- <int>(const matrix<int> &, const matrix<int> &);
template matrix<int> operator* <int>(const matrix<int> &, int);
template matrix<int> operator+ <int>(const matrix<int> &, int);
template matrix<int> operator- <int>(const matrix<int> &, int);
template matrix<int> operator/ <int>(const matrix<int> &, int);

template class matrix<float>;
template matrix<float> operator* <float>(const matrix<float> &, const matrix<float> &);
template matrix<float> operator+ <float>(const matrix<float> &, const matrix<float> &);
template matrix<float> operator- <float>(const matrix<float> &, const matrix<float> &);
template matrix<float> operator* <float>(const matrix<float> &, float);
template matrix<float> operator+ <float>(const matrix<float> &, float);
template matrix<float> operator- <float>(const matrix<float> &, float);
template matrix<float> operator/ <float>(const matrix<float> &, float);

template class matrix<double>;
template matrix<double> operator* <double>(const matrix<double> &, const matrix<double> &);
template matrix<double> operator+ <double>(const matrix<double> &, const matrix<double> &);
template matrix<double> operator- <double>(const matrix<double> &, const matrix<double> &);
template matrix<double> operator* <double>(const matrix<double> &, double);
template matrix<double> operator+ <double>(const matrix<double> &, double);
template matrix<double> operator- <double>(const matrix<double> &, double);
template matrix<double> operator/ <double>(const matrix<double> &, double);