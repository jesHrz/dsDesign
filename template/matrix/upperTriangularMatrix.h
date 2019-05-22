#ifndef __upperTriangularMatrix_H_
#define __upperTriangularMatrix_H_
#include <stdexcept>
using namespace std;
template<typename T>
class upperTriangularMatrix
{
public:
	upperTriangularMatrix(int);
	~upperTriangularMatrix() { delete[]element; };
	T operator()(int, int) const;
	void set(int, int, const T&);
protected:
	int n;
	T* element;
};

template<typename T>
upperTriangularMatrix<T>::upperTriangularMatrix(int N) :n(N)
{
	if (N < 1)	throw invalid_argument("row must > 0");
	element = new T[n*(n + 1) / 2];
}

template<typename T>
T upperTriangularMatrix<T>::operator()(int row, int col) const
{
	if (row<1 || row>n || col<1 || col>n)
		throw out_of_range("out of range of matrix");
	if (row <= col)	return element[col*(col - 1) / 2 + row - 1];
	else return 0;
}


template<typename T>
void upperTriangularMatrix<T>::set(int row, int col, const T& theElement)
{
	if (row < 1 || row > n || col < 1 || col>n)
		throw out_of_range("out of range of matrix");
	if (row <= col)	element[col*(col - 1) / 2 + row - 1] = theElement;
	else if (theElement != 0)
		throw logic_error("elements not in upper triangle must be zero");
}

#endif //__upperTriangularMatrix_H_