#pragma once

#include <vector>
#include <iostream>
#include <cassert>
#include "../basic_functions.h"
#include "Strassen.h"
#include <chrono>

using namespace std::chrono;
using namespace std;

auto Real_valued::test_time(const Real_valued& matrix)
{
	auto start = high_resolution_clock::now();
	Real_valued result = this->multiplication(matrix);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	long int result_time = duration.count();
	return result_time;
}

auto Real_valued::test_time_Strassen(const Real_valued& matrix) {
	auto start = high_resolution_clock::now();
	Real_valued result = this->Strassen_multiplication(matrix);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	long int result_time = duration.count();
	return result_time;
}

void  Real_valued::test(const Real_valued& matrix) {

	Real_valued result1 = this->multiplication(matrix);
	long int result_time = this->test_time(matrix);
	cout << "Execution time of the usual algorithm: ";
	cout << result_time / 1000000 << " seconds, "
		<< (result_time % 1000000) / 1000 << " milliseconds, "
		<< result_time % 1000 << " microseconds";
	cout << endl;

	Real_valued result2 = this->Strassen_multiplication(matrix);
	long int result_time_str = this->test_time_Strassen(matrix);
	cout << "Execution time of the Strassen algorithm: ";
	cout << result_time_str / 1000000 << " seconds, "
		<< (result_time_str % 1000000) / 1000 << " milliseconds, "
		<< result_time_str % 1000 << " microseconds";
	cout << endl;
	cout << endl;
	assert(result1.compare(result2));
	/*result1.print_matrix();
	cout << endl;
	result2.print_matrix();*/
}

void examples_tests() {
	Real_valued a1(15, 44);
	Real_valued b1(44, 15);
	a1.test(b1);

	Real_valued a2({ { 2, 1, 1, 1, 1, 1, 1 },
				{2,3,4.5,4.5,1,1,1},
				{2,3,1,12.4,1,1,1},
				{2,2.3,5,3.4,1,1,1},
				{1,1,1,1,1,1,1} });
	Real_valued b2({ {1, 1},
				{2,4},
				{2,2},
				{3.5,3.4},
				{1,1},
				{1,1},
				{1,1} });
	a2.test(b2);

	Real_valued a3(1, 1);
	Real_valued b3(1, 1);
	a3.test(b3);

	Real_valued a4({ {0,43434,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{2323,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
					{2323,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
					{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} ,
					{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} });
	Real_valued b4({ {0,43434,0,0,0,0},
					{0,0,0,0,0,0},
					{0,0,0,0,0,0} ,
					{0,2,0,0,0,0,0} ,
					{0,0,0,0,0,0} ,
					{0,0,0,0,3,0},
					{0,0,0,0,0,0},
					{0,0,5,0,0,0},
					{0,0,0,0,0,0},
					{0,0,0,0,0,0},
					{0,0,0,0,0,0},
					{0,0,0,0,0,0},
					{0,0,0,0,0,0},
					{0,0,0,0,0,0},
					{0,0,0,0,0,2},
					{0,0,0,0,0,0},
					{0,0,0,0,0,0} });
	a4.test(b4);
}
