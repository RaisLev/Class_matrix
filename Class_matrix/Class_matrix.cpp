
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
	B->setElements(0, 0, 12);
	B->setElements(1, 0, 15);
	B->setElements(2, 0, 14);
	B->setElements(3, 0, 21);
	B->printMatrix(4);

	cout << "det(A) " << A->determinant() << endl;
	cout << endl;

	LinearMatrixOperation equation = solverCreate();
	equation->methodCramer(A, B);
	equation->printSolvs();

	delete A;
	delete B;

	_CrtDumpMemoryLeaks();
	return 0;
}
