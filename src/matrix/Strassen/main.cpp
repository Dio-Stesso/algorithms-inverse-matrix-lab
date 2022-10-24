#include "../basic_functions.h"
#include "Strassen.h"

using namespace std;

int main() {
	Matrix a = { {1,1,1,1,1,1,1},{2,3,4.5,4.5,1,1,1}, {2,3,1,12.4,1,1,1},{2,2.3,5,3.4,1,1,1} ,{1,1,1,1,1,1,1} };
	Matrix b = { {1,1},{2,4},{2,2},{3.5,3.4},{1,1},{1,1},{1,1} };
	Matrix result;
	result = Strassen_multiplication(a, b);
	print_matrix(result);
}
