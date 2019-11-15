#ifndef __lowerTriangularMatrix_H_
#define __lowerTriangularMatrix_H_
#include <stdexcept>
using namespace std;
template<typename T>
class lowerTriangularMatrix
{
public:
	lowerTriangularMatrix(int);
	~lowerTriangularMatrix() { delete[]element; };
	T operator()(int, int) const;
	void set(int, int, const T&);
protected:
	int n;
	T* element;
};

template<typename T>
lowerTriangularMatrix<T>::lowerTriangularMatrix(int N) :n(N)
{
	if (N < 1)	throw invalid_argument("row must > 0");
	element = new T[n*(n + 1) / 2];
}

template<typename T>
T lowerTriangularMatrix<T>::operator()(int row, int col) const
{
	if (row < 1 || row > n || col < 1 || col > n)
		throw out_of_range("out of range of matrix");
	if (row >= col)	return element[row*(row - 1) / 2 + col - 1];
	else return 0;
}

template<typename T>
void lowerTriangularMatrix<T>::set(int row, int col, const T& theElement)
{
	if(row < 1 || row > n || col < 1 || col > n)
		throw out_of_range("out of range of matrix");
	if (row >= col)	element[row*(row - 1) / 2 + col - 1] = theElement;
	else if (theElement != 0)
		throw logic_error("elements not in lower triangle must be zero");
}

#endif //__lowerTriangularMatrix_H_