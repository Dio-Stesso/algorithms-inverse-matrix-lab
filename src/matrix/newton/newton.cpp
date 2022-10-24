#pragma once

#include <iostream>
#include <cfloat>
#include "newton.hpp"
#include "../Strassen/Strassen.h"

using namespace std;

Matrix inverse(const Matrix A, double epsilon) {
    if (!isValid(A)) {
        return {};
    }
    double t = 1.0 / (getMaxRowSum(A) * getMaxColumnSum(A));
    Matrix B = multiplyMatrixByNumber(A, t);
    Matrix I = getUnitMatrix(A.size());
    Matrix E;
    do {
        E = I - Strassen_multiplication(B, A);
        B = Strassen_multiplication(I + E, B);
    } while (getAverageSum(E) > epsilon);
    return B;
}

bool isSquare(const Matrix &matrix) {
    int n = matrix.size();
    for (size_t i = 0; i < n; i++) {
        if (matrix[i].size() != n) return false;
    }
    return true;
}

bool isValid(const Matrix &A) {
    if (A.empty()) {
        cout << "Matrix A has no elements.\n";
        return false;
    } else if (!isSquare(A)) {
        cout << "Matrix A is not a square matrix.\n";
        return false;
    }
    return true;
}

Matrix multiplyMatrixByNumber(const Matrix &A, double val) {
    Matrix result = Matrix(A);
    for (size_t i = 0; i < A.size(); i++)
        for (size_t j = 0; j < A.at(0).size(); j++) {
            result[i][j] = A[i][j] * val;
        }
    return result;
}

double getAverageSum(const Matrix &E) {
    int numberOfElements = E.size() * E[0].size();
    double number = 0;
    for (int i = 0; i < E.size(); ++i) {
        for (int j = 0; j < E[0].size(); ++j) {
            number += E.at(i).at(j);
        }
    }
    return number / numberOfElements;
}

Matrix getUnitMatrix(int n) {
    Matrix I = Matrix(n, vector<float>(n, double()));
    for (size_t i = 0; i < n; i++) {
        I[i][i] = 1;
    }
    return I;
}

double getMaxRowSum(const Matrix &A) {
    auto max = DBL_MIN;
    for (const auto &i: A) {
        double sum = 0;
        for (size_t j = 0; j < i.size(); j++) {
            sum += i[j];
        }
        if (max < sum) {
            max = sum;
        }
    }
    return max;
}

double getMaxColumnSum(const Matrix &A) {
    auto max = DBL_MIN;
    for (size_t j = 0; j < A.at(0).size(); j++) {
        double sum = 0;
        for (const auto &i: A) {
            sum += i[j];
        }
        if (max < sum) {
            max = sum;
        }
    }
    return max;
}
