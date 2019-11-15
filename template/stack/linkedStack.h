#ifndef __linkedStack_H_
#define __linkedStack_H_

#include "stack.h"
#include <linearList/chain.h>
#include <stdexcept>
using namespace std;

template<typename T>
class linkedStack : public stack<T>
{
public:
	linkedStack() :stackTop(nullptr), stackSize(0) {};
	linkedStack(const linkedStack<T>&);
	~linkedStack();

	bool empty() const { return stackSize == 0; }
	int size() const { return stackSize; }

	T top() const;

	void pop();
	void push(const T&);
	void clear();

	linkedStack<T>& operator=(const linkedStack<T>&);
protected:
	chainNode<T>* stackTop;
	int stackSize;
};


template<typename T>
linkedStack<T>::linkedStack(const linkedStack<T>& s)
{
	if (s.stackSize == 0)
	{
		stackTop = nullptr;
		stackSize = 0;
	}
	else
	{
		stackTop = new chainNode<T>(s.stackTop->element);
		chainNode<T>* sourceNode = s.stackTop->next;
		chainNode<T>* currentNode = stackTop;
		while (sourceNode != nullptr)
		{
			currentNode->next = new chainNode<T>(sourceNode->element);
			currentNode = currentNode->next;
			sourceNode = sourceNode->next;
		}
		stackSize = s.stackSize;
	}
}

template<typename T>
linkedStack<T>::~linkedStack()
{
	while (stackTop != nullptr)
	{
		chainNode<T>* nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
	}
}

template<typename T>
T linkedStack<T>::top() const
{
	if (stackSize == 0)	throw out_of_range("stack is empty");
	return stackTop->element;
}

template<typename T>
void linkedStack<T>::pop()
{
	if (stackSize == 0)	throw out_of_range("stack is empty");
	chainNode<T>* nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}

template<typename T>
void linkedStack<T>::push(const T& theElement)
{
	stackTop = new chainNode<T>(theElement, stackTop);
	stackSize++;
}

template<typename T>
void linkedStack<T>::clear()
{
	while (stackTop != nullptr)
	{
		chainNode<T>* nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
	}
	stackSize = 0;
}

template<typename T>
linkedStack<T>& linkedStack<T>::operator=(const linkedStack<T>& s)
{
	if (this == &s)	return *this;
	if (s.stackSize == 0)
	{
		stackTop = nullptr;
		stackSize = 0;
	}
	else
	{
		stackTop = new chainNode<T>(s.stackTop->element);
		chainNode<T>* sourceNode = s.stackTop->next;
		chainNode<T>* currentNode = stackTop;
		while (sourceNode != nullptr)
		{
			currentNode->next = new chainNode<T>(sourceNode->element);
			currentNode = currentNode->next;
			sourceNode = sourceNode->next;
		}
		stackSize = s.stackSize;
	}
	return *this;
}

#endif //__linkedStack_H_
