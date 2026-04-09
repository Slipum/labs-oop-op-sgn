#include "matrix/matrix.h"
#include "matrix/iterator.h"
#include <cassert>
#include <iostream>

void Tests()
{
	unsigned int aMat = 5;
	matrix<int> a(aMat, aMat);
	assert(a.get_columns() == aMat);
	assert(a.get_rows() == aMat);
	assert(a.is_square() == true);

	for (int i = 0; i < aMat; i++)
		for (int j = 0; j < aMat; j++)
			assert(a(i, j) == 0);

	a.set_elem(1, 1, 12);
	a.set_elem(4, 2, 13);

	assert(a.get_elem(1, 1) == 12);
	assert(a(1, 1) == 12);
	assert(a.get_elem(4, 2) == 13);

	unsigned int bMat_I = 12, bMat_J = 51;
	matrix<int> b(bMat_I, bMat_J);
	assert(b.is_square() == false);

	for (int i = 0; i < bMat_I; i++)
		for (int j = 0; j < bMat_J; j++)
			assert(b(i, j) == 0);

	matrix<int> c({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
	matrix<int> d({1, 2});
	assert(d.get_rows() == 1);
	assert(d.get_columns() == 2);

	matrix<int> d1({{1, 2}, {3, 4}});
	int i = 1;

	for (auto it = d1.iterator_begin(); it != d1.iterator_end(); ++it)
	{
		assert(it.value() == i);
		i++;
	}

	int j = 1;
	for (auto cu : d1)
	{
		assert(cu == j);
		j++;
	}

	matrix<int> t1({{1, 2, 3}, {4, 5, 6}});
	matrix<int> t2({{7, 8}, {9, 1}, {2, 3}});

	matrix<int> te = t1 * t2;
	int mas[] = {31, 19, 85, 55};
	j = 0;
	for (auto a : te)
	{
		assert(a == mas[j]);
		j++;
	}

	matrix<int> t3({{1, 2, 3}, {4, 5, 6}});
	matrix<int> t4({{7, 8, 9}, {10, 11, 12}});
	matrix<int> te2 = t3+t4;
	int mas2[] = {8, 10, 12, 14, 16, 18};
	j = 0;
	for (auto a : te2)
	{
		assert(a == mas2[j]);
		j++;
	}

	std::cout << "Test methods OK!" << std::endl;
}
