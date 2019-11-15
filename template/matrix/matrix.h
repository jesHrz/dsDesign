#ifndef __MATRIX_H_
#define __MATRIX_H_
#include <stdexcept>
#include <iostream>
using namespace std;

template <typename T>
class matrix
{
public:
	matrix(int, int);
	matrix(const matrix<T>&);
	~matrix() { delete[]element; };

	int rows() const { return row; }
	int columns() const { return col; }

	T& operator()(int, int);
	const T& operator()(int, int) const;
	matrix<T>& operator=(const matrix<T>&);
	matrix<T> operator+() const { return *this; };
	matrix<T> operator+(const matrix<T>&) const;
	matrix<T> operator-() const;
	matrix<T> operator-(const matrix<T>&) const;
	matrix<T> operator*(const matrix<T>&) const;
	matrix<T> operator*(const T&) const;
	matrix<T>& operator+=(const matrix<T>&);
	matrix<T>& operator-=(const matrix<T>&);

	friend matrix<T> operator* (const T& coeffcient, const matrix<T>& m) { return m * coeffcient; };
	friend ostream& operator<< <T>(ostream&, const matrix<T>&);
	friend istream& operator>> <T>(istream&, matrix<T>&);

	//matrix<T> transport() const;
	//matrix<T> inverse() const;
protected:
	T* element;
	int row, col;
};

template<typename T>
matrix<T>::matrix(int rows, int columns) :row(rows), col(columns)
{
	if (rows < 1 || columns < 1)	throw invalid_argument("row and column must > 0");
	element = new T[rows*columns];
}

template<typename T>
matrix<T>::matrix(const matrix<T>& m) : row(m.row), col(m.col)
{
	element = new T[row*col];
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= col; ++j)
			operator()(i, j) = m(i, j);
}

template<typename T>
T& matrix<T>::operator()(int rows, int columns)
{
	if (rows < 1 || rows > row || columns < 1 || columns > col)
		throw out_of_range("out of range of matrix");
	return element[(rows - 1)*col + (columns - 1)];
}

template<typename T>
const T& matrix<T>::operator()(int rows, int columns) const
{
	if (rows < 1 || rows > row || columns < 1 || columns > col)
		throw out_of_range("out of range of matrix");
	return element[(rows - 1)*col + (columns - 1)];
}

template<typename T>
matrix<T>& matrix<T>::operator=(const matrix<T>& m)
{
	if (this == &m)	return *this;
	row = m.row;
	col = m.col;
	delete[]element;
	element = new T[row*col];
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= col; ++j)
			operator()(i, j) = m(i, j);
	return *this;
}

template<typename T>
matrix<T> matrix<T>::operator+(const matrix<T>& m) const
{
	if (row != m.row || col != m.col)
		throw logic_error("No match of row or column");
	matrix<T> res(row, col);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= col; ++j)
			res(i, j) = operator()(i, j) + m(i, j);
	return res;
}

template<typename T>
matrix<T> matrix<T>::operator-() const
{
	matrix<T> res(row, col);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= col; ++j)
			res(i, j) = -operator()(i, j);
	return res;
}

template<typename T>
matrix<T> matrix<T>::operator-(const matrix<T>& m) const
{
	if (row != m.row || col != m.col)
		throw logic_error("No match of row or column while performing addition operator");
	matrix<T> res(row, col);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= col; ++j)
			res(i, j) = operator()(i, j) - m(i, j);
	return res;
}

template<typename T>
matrix<T> matrix<T>::operator*(const matrix<T>& m) const
{
	if (col != m.row)
		throw logic_error("No match of row and column while performing multiply operation");
	matrix<T> res(row, m.col);

}

template<typename T>
matrix<T> matrix<T>::operator*(const T& coefficient) const
{
	matrix<T> res(row, col);
	for (int i = 1; i <= row; ++i)
		for (int j = 1; j <= col; ++j)
			res(i, j) = coefficient*operator()(i, j);
	return res;
}

template<typename T>
matrix<T>& matrix<T>::operator+=(const matrix<T>& m)
{
	*this = *this + m;
	return *this;
}

template<typename T>
matrix<T>& matrix<T>::operator-=(const matrix<T>& m)
{
	*this = *this - m;
	return *this;
}

template<typename T>
ostream& operator<<(ostream& out, const matrix<T>& m)
{
	for (int i = 1; i <= m.row; ++i)
	{
		for (int j = 1; j <= m.col; ++j)
			out << m(i, j) << ' ';
		out << endl;
	}
	return out;
}

template<typename T>
istream& operator>>(istream& in, matrix<T>& m)
{
	for (int i = 1; i <= m.row; ++i)
		for (int j = 1; j <= m.col; ++j)
			in >> m(i, j);
	return in;
}

#endif //__MATRIX_H_