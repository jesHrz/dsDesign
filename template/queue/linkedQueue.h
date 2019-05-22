#ifndef __linkedQueue_H_
#define __linkedQueue_H_

#include "queue.h"
#include <linearlist/chain.h>
#include <stdexcept>
using namespace std;

template<typename T>
class linkedQueue:public queue<T>
{
public:
	linkedQueue() :queueFront(nullptr), queueBack(nullptr), queueSize(0) {};
	linkedQueue(const linkedQueue<T>&);
	~linkedQueue();

	bool empty() const { return queueSize == 0; }
	int size() const { return queueSize; }
	T front() const;
	T back() const;
	void pop();
	void push(const T&);
	void clear();

	linkedQueue<T>& operator=(const linkedQueue<T>&);
protected:
	chainNode<T>* queueFront;
	chainNode<T>* queueBack;
	int queueSize;
};

template<typename T>
linkedQueue<T>::linkedQueue(const linkedQueue<T>& q)
{
	if (q.empty())
	{
		queueFront = queueBack = nullptr;
		queueSize = 0;
	}
	else
	{
		queueFront = queueBack = new chainNode<T>(q.queueFront->element);
		chainNode<T>* sourceNode = q.queueFront->next;
		while (sourceNode != nullptr)
		{
			queueBack->next = new chainNode<T>(sourceNode->element);
			queueBack = queueBack->next;
			sourceNode = sourceNode->next;
		}
		queueSize = q.queueSize;
	}
}

template<typename T>
linkedQueue<T>::~linkedQueue()
{
	while (queueFront != nullptr)
	{
		chainNode<T>* nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
	queueBack = nullptr;
}

template<typename T>
T linkedQueue<T>::front() const
{
	if (queueSize < 1)	throw out_of_range("the queue is empty");
	return queueFront->element;
}

template<typename T>
T linkedQueue<T>::back() const
{
	if (queueSize < 1)	throw out_of_range("the queue is empty");
	return queueBack->element;
}

template<typename T>
void linkedQueue<T>::pop()
{
	if (queueSize < 1)	throw out_of_range("the queue is empty");
	chainNode<T>* nextNode = queueFront->next;
	delete queueFront;
	queueFront = nextNode;
	queueSize--;
}

template<typename T>
void linkedQueue<T>::push(const T& theElement)
{
	chainNode<T>* newNode = new chainNode<T>(theElement);
	if (queueSize == 0)	queueFront = newNode;
	else queueBack->next = newNode;
	queueBack = newNode;
	queueSize++;
}

template<typename T>
void linkedQueue<T>::clear()
{
	while (queueFront != nullptr)
	{
		chainNode<T>* nextNode = queueFront->next;
		delete queueFront;
		queueFront = nextNode;
	}
	queueBack = nullptr;
	queueSize = 0;
}

template<typename T>
linkedQueue<T>& linkedQueue<T>::operator=(const linkedQueue<T>& q)
{
	if (this == &q)	return *this;
	clear();
	if (q.empty())
	{
		queueFront = queueBack = nullptr;
		queueSize = 0;
	}
	else
	{
		queueFront = queueBack = new chainNode<T>(q.queueFront->element);
		chainNode<T>* sourceNode = q.queueFront->next;
		while (sourceNode != nullptr)
		{
			queueBack->next = new chainNode<T>(sourceNode->element);
			queueBack = queueBack->next;
			sourceNode = sourceNode->next;
		}
		queueSize = q.queueSize;
	}
	return *this;
}

#endif //__linkedQueue_H_
