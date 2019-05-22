#ifndef __derivedArrayStack_H_
#define __derivedArrayStack_H_

#include "stack.h"
#include <linearList/arrayList.h>
#include <stdexcept>
using namespace std;

template<typename T>
class derivedArrayStack : private arrayList<T>, public stack<T>
{
public:
	derivedArrayStack(int initialCapacity = 10) :arrayList<T>(initialCapacity) {};
	
	bool empty() const { return arrayList<T>::empty(); }
	int size() const { return arrayList<T>::size(); }
	T top() const
	{
		if (empty())	throw out_of_range("stack is empty");
		return arrayList<T>::operator[](arrayList<T>::size() - 1);
	}
	void pop()
	{
		if (empty())	throw out_of_range("stack is empty");
		arrayList<T>::erase(arrayList<T>::size() - 1);
	}
	void push(const T& theElement)
	{
		arrayList<T>::insert(arrayList<T>::size(), theElement);
	}
	void clear() { arrayList<T>::clear(); }
};

#endif //__derivedArrayStack_H_
