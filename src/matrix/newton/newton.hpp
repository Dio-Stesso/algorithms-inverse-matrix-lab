#include <vector>

using Matrix = std::vector<std::vector<double>>;

Matrix inverse(Matrix A, double epsilon);

bool isValid(const Matrix &A);

Matrix multiplyMatrixByNumber(const Matrix &A, double val);

double getAverageSum(const Matrix &E);

Matrix getUnitMatrix(int n);

double getMaxRowSum(const Matrix &A);

double getMaxColumnSum(const Matrix &A);
