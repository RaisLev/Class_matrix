#pragma once

#include <iostream>
#include <iomanip>

class _Matrix
{
private:

	unsigned int n;
	unsigned int m;
	double** c_ret;

public:

	_Matrix(unsigned int n, unsigned int m);
	unsigned int getN();
	unsigned int getM();
	void printMatrix(int w);
	void setElements(unsigned int r, unsigned int c, double value);
	double getElements(unsigned int r, unsigned int c);
	void matrixRandContent(int rBounds);
	long double sumElements();
	long double mullElements();
	void constMul(double a);
	void matrixTranspose();
	void sortLines();
	void sortColums();
	long double determinant();
	bool matrixDegenerate();
	~_Matrix();

private:

	int search(double** c_retLocale, int m1, int n1, double what, bool match, unsigned int& uI, unsigned int& uJ, unsigned int starti, unsigned int startj);
	void swapcolumns(double** c_retLocale, int n2, int m2, unsigned int x1, unsigned int x2);
	void swaprows(double** c_retLocale, int n3, int m3, unsigned int x1, unsigned int x2);
	void sort(bool rowCol);
	double** copyMatrix();
	void localeDelete(double** c_retCopy);
};

typedef _Matrix* Matrix;

class _LinearMatrixOperation
{
private:

	Matrix R;

public:

	_LinearMatrixOperation();
	Matrix matrixMultiply(Matrix A, Matrix B);
	void methodCramer(Matrix A, Matrix B);
	~_LinearMatrixOperation();

private:

	void printSolvs(double* cramer);
	Matrix copyMatrix(Matrix A);
	void resultAlloc(unsigned int An, unsigned int bm);
};

typedef _LinearMatrixOperation* LinearMatrixOperation;

Matrix matrixCreate(unsigned int r, unsigned int c);
LinearMatrixOperation solverCreate();