
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
	
	Matrix A = matrixCreate(3, 3);
	A->setElements(0, 0, 4);
	A->setElements(0, 1, 5);
	A->setElements(0, 2, 1);
	A->setElements(1, 0, 7);
	A->setElements(1, 1, 11);
	A->setElements(1, 2, 8);
	A->setElements(2, 0, 6);
	A->setElements(2, 1, 9);
	A->setElements(2, 2, 3);

	A->printMatrix(4);

	Matrix C = matrixCreate(3, 3);
	C->setElements(0, 0, 4);
	C->setElements(0, 1, 7);
	C->setElements(0, 2, 1);
	C->setElements(1, 0, 6);
	C->setElements(1, 1, 11);
	C->setElements(1, 2, 8);
	C->setElements(2, 0, 12);
	C->setElements(2, 1, 15);
	C->setElements(2, 2, 8);

	C->printMatrix(4);


	LinearMatrixOperation lsolv = solverCreate();

	Matrix B = matrixCreate(3, 1);
	B->setElements(0, 0, 15);
	B->setElements(1, 0, 25);
	B->setElements(2, 0, 11);
	B->printMatrix(4);

	lsolv->methodCramer(A, B);

	Matrix RES = matrixCreate(3, 3);
	RES = lsolv->matrixMultiply(A, C);

	RES->printMatrix(4);
	
	delete A;
	delete B;
	delete C;
	delete RES;
    delete lsolv;

	_CrtDumpMemoryLeaks();
	return 0;
}
