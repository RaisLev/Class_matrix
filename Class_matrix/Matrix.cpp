#include <iostream>
#include <iomanip>
#include "Matrix.h"

using namespace std;

typedef _Matrix* Matrix;
typedef _LinearMatrixOperation* LinearMatrixOperation;

_Matrix::_Matrix(unsigned int n, unsigned int m)
{
	this->n = n;
	this->m = m;

	c_ret = nullptr;
	c_ret = new  double* [n];
	for (unsigned int i = 0; i < n; i++)
	{
		c_ret[i] = new double[m];

		for (unsigned int j = 0; j < m; j++)
		{
			c_ret[i][j] = 0;
		}
	}
}

unsigned int _Matrix::getN()
{
	return n;
}

unsigned int _Matrix::getM()
{
	return m;
}

void _Matrix::printMatrix(int w)
{
	if (c_ret != nullptr)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			for (unsigned int j = 0; j < m; j++)
			{
				cout.width(w);
				cout << *(*(c_ret + i) + j);
			}
			cout << ' ' << endl;
		}
		cout << endl;
	}
}

void _Matrix::setElements(unsigned int r, unsigned int c, double value)
{
	if (r <= n || c <= m)
	{
		*(*(c_ret + r) + c) = value;
	}
	else return;
}

double _Matrix::getElements(unsigned int r, unsigned int c)
{
	double value = 0;
	if (r <= n || c <= m)
	{
		value = c_ret[r][c];
		return value;
	}
	else return 0;
}

void _Matrix::matrixRandContent(int rBounds)
{
	srand(time(0));
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			*(*(c_ret + i) + j) = rand() % rBounds;
		}
	}
}

long double _Matrix::sumElements()
{
	long double sum = 0;
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			sum += *(*(c_ret + i) + j);
		}
	}
	return sum;
}

long double _Matrix::mullElements()
{
	long double mull = 1;
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			mull *= *(*(c_ret + i) + j);
		}
	}
	return mull;
}

void _Matrix::constMul(double a)
{
	for (unsigned int i = 0; i < n; i++)
	{
		for (unsigned int j = 0; j < m; j++)
		{
			*(*(c_ret + i) + j) *= a;
		}
	}
}

void _Matrix::matrixTranspose()
{
	double** transp = new double* [m];
	for (unsigned int i = 0; i < m; i++)
	{
		transp[i] = new double[n];
		for (unsigned int j = 0; j < n ; j++)
		{
			transp[i][j] = c_ret[j][i];
		}
	}
	localeDelete(c_ret);
	c_ret = nullptr;
	c_ret = transp;
	unsigned int temp = n;
	n = m;
	m = temp;
}

long double _Matrix::determinant()
{
	double** c_retLocale = copyMatrix();
	double localvalue = 0;
	if (n == m)
	{
		if (m == 0)
		{
			localeDelete(c_retLocale);
			return localvalue;
		}
		if (m == 1)
		{
			localvalue = c_retLocale[0][0];
			localeDelete(c_retLocale);
			return localvalue;
		}
		if (m == 2)
		{
			localvalue = (c_retLocale[0][0] * c_retLocale[1][1] - c_retLocale[1][0] * c_retLocale[0][1]);
			localeDelete(c_retLocale);
			return localvalue;
		}
		bool sign = false;
		double det = 1;
		double tmp;
		unsigned int x, y;

		for (unsigned int i = 0; i < n; i++)
		{
			if (c_retLocale[i][i] == 0)
			{
				if (!search(c_retLocale, m, n, 0, false, y, x, i, i))
				{
					localeDelete(c_retLocale);
					return 0;
				}
				if (i != y)
				{
					swaprows(c_retLocale, m, n, i, y);
					sign = !sign;
				}
				if (i != x)
				{
					swapcolumns(c_retLocale, m, n, i, x);
					sign = !sign;
				}
			}
			det *= c_retLocale[i][i];
			tmp = c_retLocale[i][i];
			for (x = i; x < m; x++)
			{
				c_retLocale[i][x] = c_retLocale[i][x] / tmp;
			}
			for (y = i + 1; y < n; y++)
			{
				tmp = c_retLocale[y][i];
				for (x = i; x < m; x++)
					c_retLocale[y][x] -= (c_retLocale[i][x] * tmp);
			}
		}
		if (sign)
		{
			localeDelete(c_retLocale);
			return det * (-1);
		}
		localeDelete(c_retLocale);
		return det;
	}
	else
	{
		localeDelete(c_retLocale);
		return -1;
	}
}

bool _Matrix::matrixDegenerate()
{
	if (determinant() != 0)
	{
		return false;
	}
	else return true;
}

_Matrix::~_Matrix()
{
	if (c_ret != nullptr)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			delete[] c_ret[i];
		}
		delete[] c_ret;
	}
}

int _Matrix::search(double** c_retLocale, int m1, int n1, double what, bool match, unsigned int& uI, unsigned int& uJ, unsigned int starti, unsigned int startj)
{
	if ((!m1) || (!n1)) return 0;
	if ((starti >= n1) || (startj >= m1)) return 0;
	for (unsigned int i = starti; i < n1; i++)
		for (unsigned int j = startj; j < m1; j++)
		{
			if (match == true)
			{
				if (c_retLocale[i][i] == what)
				{
					uI = i; uJ = j;
					return 1;
				}
			}
			else if (c_retLocale[i][j] != what)
			{
				uI = i; uJ = j;
				return 1;
			}
		}
	return 0;
}

void _Matrix::swapcolumns(double** c_retLocale, int n2, int m2, unsigned int x1, unsigned int x2)
{
	if ((!n2) || (!m2)) return;
	if ((x1 >= m2) || (x2 >= m2) || (x1 == x2)) return;
	double tmp;
	for (unsigned int x = 0; x < n; x++)
	{
		tmp = c_retLocale[x][x1];
		c_retLocale[x][x1] = c_retLocale[x][x2];
		c_retLocale[x][x2] = tmp;
	}
	return;
}

void _Matrix::swaprows(double** c_retLocale, int n3, int m3, unsigned int x1, unsigned int x2)
{
	if ((!n3) || (!m3)) return;
	if ((x1 >= n3) || (x2 >= n3) || (x1 == x2)) return;
	double tmp;
	for (unsigned int x = 0; x < m3; x++)
	{
		tmp = c_retLocale[x1][x];
		c_retLocale[x1][x] = c_retLocale[x2][x];
		c_retLocale[x2][x] = tmp;
	}
	return;
}

double** _Matrix::copyMatrix()
{
	double** c_retCopy = nullptr;
	c_retCopy = new  double* [n];
	for (unsigned int i = 0; i < n; i++)
	{
		c_retCopy[i] = new double[m];
		for (unsigned int j = 0; j < m; j++)
		{
			c_retCopy[i][j] = c_ret[i][j];
		}
	}
	return c_retCopy;
}

void _Matrix::localeDelete(double** c_retCopy)
{
	if (c_retCopy != nullptr)
	{
		for (unsigned int i = 0; i < n; i++)
		{
			delete[] c_retCopy[i];
		}
		delete[] c_retCopy;
	}
}



_LinearMatrixOperation::_LinearMatrixOperation()
{
	this->R = nullptr;
};

Matrix _LinearMatrixOperation::matrixMultiply(Matrix A, Matrix B)
{
	unsigned int An = A->getN();
	unsigned int Am = A->getM();
	unsigned int bn = B->getN();
	unsigned int bm = B->getM();
	
	resultAlloc(An, bm);

	if (Am == bn)
	{
		for (unsigned int i = 0; i < An; i++)
		{
			for (unsigned int j = 0; j < bm; j++)
			{
				R->setElements(i, j, 0);
				for (unsigned int k = 0; k < Am; k++)
				{
					R->setElements(i, j, (R->getElements(i, j) + (A->getElements(i, k)) * (B->getElements(k, j))));
				}
			}
		}
		return R;
	}
	else return R;
}

void _LinearMatrixOperation::methodCramer(Matrix A, Matrix B)
{
	unsigned int An = A->getN();
	unsigned int Am = A->getM();
	unsigned int bn = B->getN();
	unsigned int bm = B->getM();

	double det_alpha = A->determinant();
	unsigned int count = 0;

	if ((An == Am) && (bn == An) && (bm == 1) && (A->matrixDegenerate() == false))
	{
		Matrix CopA = copyMatrix(A);
		double* cramer = new double[An + 1];
		*(unsigned int*)cramer = An;
		cramer++;
		for (unsigned int k = 0; k < Am; k++)
		{
			for (unsigned int j = 0; j < An; j++)
			{
				A->setElements(j, k, B->getElements(j, 0));
			}
			cramer[count] = (A->determinant()) / det_alpha;
			for (unsigned int i = 0; i < An; i++)
			{
				for (unsigned int j = 0; j < Am; j++)
				{
					A->setElements(i, j, CopA->getElements(i, j));
				}
			}
			count++;
		}
		delete CopA;
		printSolvs(cramer);
		cramer--;
		delete[] cramer;
	}
}

void _LinearMatrixOperation::printSolvs(double* cramer)
{
	if (cramer == nullptr) return;

	unsigned int length = *(unsigned int*)(cramer - 1);
	for (unsigned int i = 0; i < length; i++)
	{
		cout << "x" << (i + 1) << ": " << cramer[i] << endl;
	}
	cout << endl;
}

_LinearMatrixOperation::~_LinearMatrixOperation()
{
	//delete R;
}

Matrix _LinearMatrixOperation::copyMatrix(Matrix A)
{
	unsigned int An = A->getN();
	unsigned int Am = A->getM();

	Matrix Copy = matrixCreate(An, Am);

	for (unsigned int i = 0; i < An; i++)
	{
		for (unsigned int j = 0; j < Am; j++)
		{
			Copy->setElements(i, j, A->getElements(i, j));
		}
	}
	return Copy;
}


void _LinearMatrixOperation::resultAlloc(unsigned int An, unsigned int bm)
{
	R = matrixCreate(An, bm);
	for (unsigned int i = 0; i < An; i++)
	{
		for (unsigned int j = 0; j < bm; j++)
		{
			R->setElements(i, j, 0);
		}
	}
}


Matrix matrixCreate(unsigned int r, unsigned int c)
{
	Matrix M = new _Matrix(r, c);
	return M;
}

LinearMatrixOperation solverCreate()
{
	LinearMatrixOperation LinearSystem = new _LinearMatrixOperation();
	return LinearSystem;
}