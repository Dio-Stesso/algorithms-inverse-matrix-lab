#pragma once

#include <vector>
#include <iostream>

using namespace std;
class Real_valued {
public:

	vector<vector<double>>  Matrix;
	int rows; //= matrix.size()
	int columns;// matrix[0].size()

	bool compare (Real_valued matrix) {
		if ((this->Matrix.size() != matrix.Matrix.size()) || (this->Matrix[0].size() != matrix.Matrix[0].size())) {
			return false;
		}
		for (int i = 0; i < this->Matrix.size(); i += 1) {
			for (int j = 0; j < this->Matrix[0].size(); j += 1) {
				if ( int(this->Matrix[i][j] - matrix.Matrix[i][j])!=0) {
					return false;
				}
			}
		}
		return true;
	}

	void print_matrix() {
		for (int i = 0; i < this->Matrix.size(); i++)
		{
			for (int j = 0; j < this->Matrix[0].size(); j++) {
				cout << this->Matrix[i][j] << " ";

			}
			cout << endl;
		}
	}

	bool  correct_size_for_multiplication(const Real_valued matrix)
	{
		if (this->columns != matrix.rows) {
			cout << this->columns << " " << matrix.rows << endl;
			return false;
		}
		return true;
	}

	bool correct_sizes(const Real_valued matrix)
	{
		if (this->rows != matrix.rows || this->columns != matrix.columns) {
			false;
		}
		return true;
	}

	Real_valued multiplication(const Real_valued matrix) {
		this->rows = this->Matrix.size();
		this->columns = this->Matrix[0].size();
		if (!this->correct_size_for_multiplication(matrix)) {
			throw runtime_error("");
		}
		Real_valued  result(this->rows);
		for (size_t i = 0; i < this->rows; ++i) {
			result.Matrix[i].resize(matrix.columns);
			for (size_t j = 0; j < matrix.columns; ++j) {
				for (size_t k = 0; k < this->columns; ++k) {
					result.Matrix[i][j] += this->Matrix[i][k] * matrix.Matrix[k][j];
				}
			}
		}
		return result;
	}

	Real_valued addition(Real_valued matrix)
	{
		if (!this->correct_sizes(matrix)) {
			throw runtime_error("");
		}
		for (size_t i = 0; i < matrix.rows; ++i) {
			for (size_t j = 0; j < matrix.columns; ++j) {
				matrix.Matrix[i][j] += this->Matrix[i][j];
			}
		}
		return matrix;
	}

	Real_valued subtraction (Real_valued matrix)
	{
		if (!correct_sizes(matrix)) {
			throw runtime_error("");
		}
		for (size_t i = 0; i < matrix.rows; ++i) {
			for (size_t j = 0; j < matrix.columns; ++j) {
				matrix.Matrix[i][j] -= this->Matrix[i][j];
			}
		}
		return matrix;
	} 

	void expand(const size_t& size)
	{
		this->Matrix.resize(size);
		for (auto& row : this->Matrix) {
			row.resize(size, 0);
		}
	}
	
	//Constructors
	Real_valued(const int& n) {
		vector<vector<double>> matrix;
		matrix.resize(n);
		for (int i = 0; i < n; i++) {
			matrix[i].resize(n);
		}
		Matrix = matrix;
		rows = matrix.size();
		columns = matrix[0].size();
	}

	Real_valued(vector<vector<double>> matrix ) {
		Matrix = matrix;
		rows = matrix.size();
		columns = matrix[0].size();
	}

	Real_valued(const int& N, const int& M) {
		vector<vector<double>> matrix;
		rows = N;
		columns = M;
		for (int i = 0; i < this->rows; ++i) {
			vector<double> line;
			for (int j = 0; j < this->columns; ++j) {
				double number=rand()%1000;
				line.push_back(number);
			}
			matrix.push_back(line);
		}
		Matrix = matrix;	
	}
	
	// for Strassen multiplication 
	void split(Real_valued &a1, Real_valued& a2, Real_valued& a3, Real_valued& a4);
	void collect(Real_valued& c11, Real_valued & c12, Real_valued& c21, Real_valued& c22);
	Real_valued Strassens_algorithm(Real_valued matrix, size_t n);
	Real_valued Strassen_multiplication(Real_valued matrix);
	auto test_time(const Real_valued& matrix);
	auto test_time_Strassen(const Real_valued& matrix);
	void test(const Real_valued& matrix);
};
