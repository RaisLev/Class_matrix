
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
	A->setElements(0, 0, sin(1));
	A->setElements(0, 1, -cos(2));
	A->setElements(0, 2, 7);
	A->setElements(1, 0, 3);
	A->setElements(1, 1, -sqrt(5));
	A->setElements(1, 2, -tan(0.5));
	A->setElements(2, 0, 1);
	A->setElements(2, 1, -cos(3));
	A->setElements(2, 2, sin(2));
	cout << "A:" << endl;
	A->printMatrix(10);

	Matrix B = matrixCreate(3, 1);
	B->setElements(0, 0, sqrt(3));
	B->setElements(1, 0, 7);
	B->setElements(2, 0, tan(0.3));
	cout << "B:" << endl;
	B->printMatrix(10);

	LinearMatrixOperation reshatel = solverCreate();
	reshatel->methodCramer(A, B, "y");

	_CrtDumpMemoryLeaks();
	return 0;
}
