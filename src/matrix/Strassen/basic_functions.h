
#pragma once

#include <vector>
#include <iostream>

using namespace std;

vector<vector<float>> typedef Matrix;


void print_matrix(Matrix matrix) {
	int m = (matrix).size();
	int n = (matrix)[0].size();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++) {
			cout << matrix[i][j] << " ";

		}
		cout << endl;
	}
}

bool  correct_size_for_multiplication(const Matrix& first, const Matrix& second)
{
	if (first[0].size() != second.size()) {
		return false;
	}
	return true;
}

bool correct_sizes(const Matrix& first, const Matrix& second)
{
	if (first.size() != second.size() || first[0].size() != second[0].size()) {
		false;
	}
	return true;
}

Matrix operator * (const Matrix& first, const Matrix& second)
{
	if (!correct_size_for_multiplication(first, second)) {
		throw std::runtime_error("");
	}
	Matrix result(first.size());
	for (size_t i = 0; i < first.size(); ++i) {
		result[i].resize(second[0].size());
		for (size_t j = 0; j < second[0].size(); ++j) {
			for (size_t k = 0; k < first[0].size(); ++k) {
				result[i][j] += first[i][k] * second[k][j];
			}
		}
	}
	return result;
}

Matrix operator +(Matrix first, const Matrix& second)
{
	if (!correct_sizes(first, second)) {
		throw std::runtime_error("");
	}
	for (size_t i = 0; i < first.size(); ++i) {
		for (size_t j = 0; j < first[0].size(); ++j) {
			first[i][j] += second[i][j];
		}
	}
	return first;
}

Matrix operator -(Matrix first, const Matrix& second)
{
	if (!correct_sizes(first, second)) {
		throw std::runtime_error("");
	}
	for (size_t i = 0; i < first.size(); ++i) {
		for (size_t j = 0; j < first[0].size(); ++j) {
			first[i][j] -= second[i][j];
		}
	}
	return first;
}

void expand(Matrix& matrix, const size_t& size)
{
	matrix.resize(size);
	for (auto& row : matrix) {
		row.resize(size, 0);
	}
}


