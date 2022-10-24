#pragma once

#include <vector>
#include <iostream>
#include "Basic_functions.h"
using namespace std;

void split(Matrix& a, Matrix& a1, Matrix& a2, Matrix& a3, Matrix& a4)
{
	size_t n = a.size() / 2;
	for (size_t i = 0; i < n; ++i) {
		a1[i].resize(n);
		a2[i].resize(n);
		a3[i].resize(n);
		a4[i].resize(n);

		copy(begin(a[i]), begin(a[i]) + n, begin(a1[i]));
		copy(begin(a[i]) + n, end(a[i]), begin(a2[i]));
		copy(begin(a[i + n]), begin(a[i + n]) + n, begin(a3[i]));
		copy(begin(a[i + n]) + n, end(a[i + n]), begin(a4[i]));

	}
}

Matrix collect(Matrix& c11, Matrix& c12, Matrix& c21, Matrix& c22)
{
	for (int i = 0; i < c11.size(); i++)
	{
		c11[i].insert(c11[i].end(), c12[i].begin(), c12[i].end());
		c21[i].insert(c21[i].end(), c22[i].begin(), c22[i].end());
	}
	c11.insert(c11.end(), c21.begin(), c21.end());
	return c11;
}


size_t degrees_two(const size_t& number) {
	size_t d_two = 2;
	while (number > d_two) { d_two = d_two << 1; }
	return d_two;
}

Matrix Strassens_algorithm(Matrix first, Matrix second, size_t n)
{
	if (n == 2) {
		return (first * second);
	}
	n = n / 2;
	Matrix a11(n), a12(n), a21(n), a22(n);
	Matrix b11(n), b12(n), b21(n), b22(n);
	split(first, a11, a12, a21, a22);
	split(second, b11, b12, b21, b22);

	Matrix p1 = Strassens_algorithm((a11 + a22), (b11 + b22), n);
	Matrix p2 = Strassens_algorithm((a21 + a22), b11, n);
	Matrix p3 = Strassens_algorithm(a11, (b12 - b22), n);
	Matrix p4 = Strassens_algorithm(a22, (b21 - b11), n);
	Matrix p5 = Strassens_algorithm((a11 + a12), b22, n);
	Matrix p6 = Strassens_algorithm((a21 - a11), (b11 + b12), n);
	Matrix p7 = Strassens_algorithm((a12 - a22), (b21 + b22), n);

	Matrix c11 = ((p1 + p4) + (p7 - p5));
	Matrix c12 = (p3 + p5);
	Matrix c21 = (p2 + p4);
	Matrix c22 = ((p1 - p2) + (p3 + p6));

	Matrix result(2 * n);
	result = collect(c11, c12, c21, c22);

	return result;
}

Matrix Strassen_multiplication(Matrix first, Matrix second) {
	if (!correct_size_for_multiplication(first, second)) {
		throw std::runtime_error("");
	}

	size_t first_rows = first.size(), first_columns = first[0].size(), second_rows = second.size(), second_columns = second[0].size();
	size_t new_size = max(max(first_rows, first_columns), second_columns); // first_columns=second_rows
	new_size = degrees_two(new_size);

	
	if (first.size() != new_size || first[0].size() != new_size) {
		expand(first, new_size);
		expand(second, new_size);
	}

	Matrix result = Strassens_algorithm(first, second, new_size);

	if (first_rows != new_size) {
		result.resize(first_rows);
	}
	if (second_columns != new_size) {
		for (auto& r : result) { r.resize(second_columns); }
	}

	return result;
}



