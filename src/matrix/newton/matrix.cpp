#include <stdexcept>
#include <vector>
#include <cmath>
#include "newton.hpp"

using namespace std;

bool isCorrectMultiplySizes(const Matrix &left, const Matrix &right) {
    if (left[0].size() != right.size()) {
        return false;
    }
    return true;
}

bool isCorrectFullSizes(Matrix left, const Matrix &right) {
    if (left.size() != right.size() || left[0].size() != right[0].size()) {
        return false;
    }
    return true;
}

Matrix transpose(const Matrix &m) {
    int n = m.size();
    Matrix r(n, vector<double>(n));
    for (int i = 0; i < n; i += 1) {
        for (int k = 0; k < n; k += 1) {
            r[i][k] = m[k][i];
        }
    }
    return r;
}

Matrix multiplyMatrix(const Matrix &left, const Matrix &right) {
    if (!isCorrectMultiplySizes(left, right)) {
        throw runtime_error("Matrix sizes do not match.");
    }
    Matrix result(left.size());
    for (size_t i = 0; i < left.size(); ++i) {
        result[i].resize(right[0].size());
        for (size_t j = 0; j < right[0].size(); ++j) {
            for (size_t k = 0; k < left[0].size(); ++k) {
                result[i][j] += left[i][k] * right[k][j];
            }
        }
    }
    return result;
}

Matrix addMatrix(Matrix left, const Matrix &right) {
    if (!isCorrectFullSizes(left, right)) {
        throw runtime_error("Matrix sizes do not match.");
    }
    for (size_t i = 0; i < left.size(); ++i) {
        for (size_t j = 0; j < left[0].size(); ++j) {
            left[i][j] += right[i][j];
        }
    }
    return left;
}

Matrix subtractMatrices(Matrix left, const Matrix &right) {
    if (!isCorrectFullSizes(left, right)) {
        throw runtime_error("Matrix sizes do not match.");
    }
    for (size_t i = 0; i < left.size(); ++i) {
        for (size_t j = 0; j < left[0].size(); ++j) {
            left[i][j] -= right[i][j];
        }
    }
    return left;
}
