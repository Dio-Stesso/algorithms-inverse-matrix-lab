#pragma once

#include <vector>
#include <iostream>
#include "../basic_functions.h"
using namespace std;

void Real_valued:: split(Real_valued& a1, Real_valued &a2, Real_valued& a3, Real_valued &a4)
{   
	size_t n = this->Matrix.size() /2;
	for (size_t i = 0; i < n; ++i) {		
		a1.Matrix[i].resize(n);
		a2.Matrix[i].resize(n);
		a3.Matrix[i].resize(n);
		a4.Matrix[i].resize(n);

		copy(begin(this->Matrix[i]), begin(this->Matrix[i]) + n, begin(a1.Matrix[i]));
		copy(begin(this->Matrix[i]) + n, end(this->Matrix[i]), begin(a2.Matrix[i]));
		copy(begin(this->Matrix[i + n]), begin(this->Matrix[i + n]) + n, begin(a3.Matrix[i]));
		copy(begin(this->Matrix[i + n]) + n, end(this->Matrix[i + n]), begin(a4.Matrix[i]));
	}
}

void Real_valued:: collect(Real_valued& c11, Real_valued& c12, Real_valued& c21, Real_valued& c22)
{
	size_t n = this->Matrix.size() / 2;
	for (size_t i = 0; i < n; ++i) {
		copy(begin(c11.Matrix[i]), end(c11.Matrix[i]), begin(this->Matrix[i]));
		copy(begin(c12.Matrix[i]), end(c12.Matrix[i]), begin(this->Matrix[i]) + n);
		copy(begin(c21.Matrix[i]), end(c21.Matrix[i]), begin(this->Matrix[i + n]));
		copy(begin(c22.Matrix[i]), end(c22.Matrix[i]), begin(this->Matrix[i + n]) + n);
	}	
}

size_t degrees_two(const size_t& number) {
	size_t d_two = 2;
	while (number > d_two) { d_two = d_two << 1; }
	return d_two;
}

Real_valued Real_valued:: Strassens_algorithm (Real_valued matrix, size_t n)
{
	if (n <= 64) {
		return (this->multiplication(matrix));
	}
	n = n / 2;
	Real_valued a11(n), a12(n), a21(n), a22(n);
	Real_valued b11(n), b12(n), b21(n), b22(n);
	this->split(a11, a12, a21, a22);
	matrix.split( b11, b12, b21, b22);
	Real_valued p1 = (a11.addition(a22)).Strassens_algorithm(b11.addition(b22), n);
	Real_valued p2 = (a21.addition(a22)).Strassens_algorithm( b11, n);
	Real_valued p3 = a11.Strassens_algorithm( b22.subtraction(b12), n);
	Real_valued p4 = a22.Strassens_algorithm( (b11.subtraction (b21)), n);
	Real_valued p5 = (a11.addition(a12)).Strassens_algorithm( b22, n);
	Real_valued p6 = (a11.subtraction(a21)).Strassens_algorithm( b11.addition( b12), n);
	Real_valued p7 = (a22.subtraction(a12)).Strassens_algorithm(b21.addition( b22), n);

	Real_valued c11 = (p1.addition( p4)).addition(p5.subtraction( p7));
	Real_valued c12 = p3.addition( p5);
	Real_valued c21 = p2.addition( p4);
	Real_valued c22 = (p2.subtraction(p1)).addition(p3.addition( p6));
	Real_valued result(2*n);
	result.collect(c11, c12, c21, c22);
	return result;
}

Real_valued Real_valued:: Strassen_multiplication(Real_valued matrix) {
	if (!(this->correct_size_for_multiplication(matrix))) {
		throw runtime_error("");
	}
	if (this->rows <=64) {
		return (this->multiplication(matrix));
	}
	size_t first_rows = this->rows, first_columns = this->columns, second_rows = matrix.rows, second_columns = matrix.columns;
	size_t new_size = max(max(first_rows, first_columns), second_columns); // first_columns=second_rows
	new_size = degrees_two(new_size);

	if (this->rows != new_size || this->columns != new_size) {
		this->expand(new_size);
		matrix.expand( new_size);
	}
	Real_valued result = this->Strassens_algorithm(matrix, new_size);
	if (first_rows != new_size) {
		result.Matrix.resize(first_rows);
	}
	if (second_columns != new_size) {
		for (auto& r : result.Matrix) { r.resize(second_columns); }
	}
	return result;
}
