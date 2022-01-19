
#include <iostream>
#include <iomanip>
#include "Matrix.h"

using namespace std;

#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW


int main()
{
	setlocale(LC_ALL, "");
	
	Matrix A = matrixCreate(4, 4);
	A->matrixRandContent(15);
	cout << "A: " << endl;
	A->printMatrix(4);
	
	A->sortColums();
	cout << "sortedColums: " << endl;
	A->printMatrix(4);
	
	A->matrixTranspose();
	cout << "transpose: " << endl;
	A->printMatrix(4);

	Matrix B = matrixCreate(4, 1);
	B->matrixRandContent(4);
	cout << "B: " << endl;
	B->printMatrix(4);

	LinearMatrixOperation reshatel = solverCreate();
	reshatel->methodCramer(A, B);

	delete A;
	delete B;
	delete reshatel;

	_CrtDumpMemoryLeaks();
	return 0;
}
