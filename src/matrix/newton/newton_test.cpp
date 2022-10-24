#pragma once

#include <iostream>
#include <chrono>
#include "newton.cpp"

using namespace std;
using namespace chrono;

void displayMatrix(const Matrix &matrix) {
    cout << "\n";
    for (size_t i = 0; i < matrix.size(); i++) {
        for (size_t j = 0; j < matrix.at(i).size(); j++) {
            cout << " " << left << matrix[i][j];
        }
        cout << "\n\n";
    }
}

int main() {
    double epsilon = 4;

    cout << " *** Matrix tests ***\n\n";
    cout << " Test #1\n Epsilon = " << epsilon << "\n\n";
    vector<vector<float>> A{
            vector<float>{1, 4, 0},
            vector<float>{7, 1, 7},
            vector<float>{4, 1, 1}
    };
    cout << " Matrix A:\n";
    displayMatrix(A);
    auto start = high_resolution_clock::now();
    auto matrix = inverse(A, epsilon);
    auto stop = high_resolution_clock::now();
    cout << " Inversed A:\n";
    displayMatrix(matrix);
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    A = vector<vector<float>>{
            vector<float>{1, 5, 0},
            vector<float>{3, 1, 2},
            vector<float>{4, 1, 0}
    };
    cout << " Matrix A:\n";
    displayMatrix(A);
    start = high_resolution_clock::now();
    matrix = inverse(A, epsilon);
    stop = high_resolution_clock::now();
    cout << " Inversed A:\n";
    displayMatrix(matrix);
    duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    A = vector<vector<float>>{
            vector<float>{2, 0},
            vector<float>{14, 2.8}
    };
    cout << "\n Test #3\n Epsilon = " << epsilon << "\n\n";
    cout << " Matrix A:\n";
    displayMatrix(A);print_matrix(A);
    start = high_resolution_clock::now();
    matrix = inverse(A, epsilon);
    stop = high_resolution_clock::now();
    cout << " Inversed A:\n";
    displayMatrix(matrix);
    duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";

    A = vector<vector<float>>{
            vector<float>{18, 0.3, 1, -9.3},
            vector<float>{-7.3, 189, 0, 0.1},
            vector<float>{-91, 0, 0.34, 1},
            vector<float>{71, 56, 0.56, 3}
    };
    cout << "\n Test #4\n Epsilon = " << epsilon << "\n\n";
    cout << " Matrix A:\n";
    displayMatrix(A);
    start = high_resolution_clock::now();
    matrix = inverse(A, epsilon);
    stop = high_resolution_clock::now();
    cout << " Inversed A:\n";
    displayMatrix(matrix);
    duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n";
}
