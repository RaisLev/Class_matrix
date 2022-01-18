
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
	A->setElements(0, 0, 2);
	A->setElements(0, 1, -5);
	A->setElements(0, 2, 3);
	A->setElements(1, 0, 4);
	A->setElements(1, 1, 1);
	A->setElements(1, 2, 4);
	A->setElements(2, 0, 1);
	A->setElements(2, 1, 2);
	A->setElements(2, 2, -8);
	cout << "A: " << endl;
	A->printMatrix(4);

	Matrix B = matrixCreate(1, 3);
	B->setElements(0, 0, 7);
	B->setElements(0, 1, 21);
	B->setElements(0, 2, -11);
	cout << "B: " << endl;
	B->printMatrix(4);

	B->matrixTranspose();
	cout << "transp(B): " << endl;
	B->printMatrix(4);

	LinearMatrixOperation reshatel = solverCreate();
	reshatel->methodCramer(A, B);

	delete A;
	delete B;
	delete reshatel;

	_CrtDumpMemoryLeaks();
	return 0;
}
