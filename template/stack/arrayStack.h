#ifndef __arrayStack_H_
#define __arrayStack_H_

#include "stack.h"
#include <stdexcept>
using namespace std;

template<typename T>
class arrayStack :public stack<T>
{
public:
	arrayStack(int = 10);
	arrayStack(const arrayStack<T>&);
	~arrayStack() { delete[] stack; }

	bool empty() const { return stackTop == 0; }
	int size() const { return stackTop; }

	T top() const;

	void pop();
	void push(const T&);
	void clear();

	arrayStack<T>& operator=(const arrayStack<T>&);
protected:
	T* stack;
	int stackTop;
	int stackSize;
};

template<typename T>
arrayStack<T>::arrayStack(int initialCapacity)
{
	if(initialCapacity < 1)	throw out_of_range("the initial Capacity of arrayStack mut > 0");
	stackSize = initialCapacity;
	stack = new T[stackSize];
	stackTop = 0;
}

template<typename T>
arrayStack<T>::arrayStack(const arrayStack<T>& s)
{
	stackSize = s.stackSize;
	stackTop = 0;
	stack = new T[stackSize];
	while (stackTop < s.stackTop)
	{
		stack[stackTop] = s.stack[stackTop];
		stackTop++;
	}
}

template<typename T>
T arrayStack<T>::top() const
{
	if (stackTop <= 0)	throw out_of_range("stack is empty");
	return stack[stackTop - 1];
}

template<typename T>
void arrayStack<T>::pop()
{
	if (stackTop <= 0)	throw out_of_range("stack is empty");
	stack[--stackTop].~T();
}

template<typename T>
void arrayStack<T>::push(const T& theElement)
{
	if (stackTop == stackSize)
	{
		
		T* newStack = new T[stackSize * 2];
		copy(stack, stack + stackTop, newStack);
		delete stack;
		stack = newStack;
		stackSize *= 2;
	}
	stack[stackTop++] = theElement;
}

template<typename T>
void arrayStack<T>::clear()
{
	while (stackTop > 0)	stack[--stackTop].~T();
}

template<typename T>
arrayStack<T>& arrayStack<T>::operator=(const arrayStack<T>& s)
{
	if (this == &s)	return *this;
	stackSize = s.stackSize;
	stackTop = 0;
	stack = new T[stackSize];
	while (stackTop < s.stackTop)
	{
		stack[stackTop] = s.stack[stackTop];
		stackTop++;
	}
	return *this;
}

#endif //__arrayStack_H_
