
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
	A->matrixRandContent(50);
	A->printMatrix(4);

	Matrix B = matrixCreate(4, 1);
	B->matrixRandContent(100);
	B->printMatrix(4);

	LinearMatrixOperation solv = solverCreate();
	(solv->matrixMultiply(A, B))->printMatrix(4);

	delete A;
	delete B;
	delete solv;

	_CrtDumpMemoryLeaks();
	return 0;
}
