#ifndef __CHAIN_H_
#define __CHAIN_H_

#include "linearList.h"
#include <stdexcept>
using namespace std;

template<typename T>
struct chainNode
{
	T element;
	chainNode<T>* next;
	chainNode(const T& _element, chainNode<T>* _next = nullptr) : element(_element), next(_next) {}
	chainNode(const chainNode<T>*& c) : element(c->element), next(c->element) {}
};

template<typename T>
class chain
	:virtual public linearList<T>
{
public:
	chain(int = 10);
	chain(const chain<T>&);
	~chain();


	bool empty() const;
	int size() const;
	int find(const T&) const;
	void erase(int);
	void insert(int, const T&);

	void clear();
	void push_back(const T&);

	chain<T>& operator=(const chain<T>&);
	T& operator[](int);
	const T& operator[](int) const;

	class iterator;
	class const_iterator;

	iterator begin() { return iterator(pHead->next); }
	iterator end() { return iterator(nullptr); }

	const_iterator begin() const { return const_iterator(pHead->next); }
	const_iterator end() const { return const_iterator(nullptr); }

	class iterator
	{
	public:
		typedef forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		iterator(chainNode<T>* theNode = nullptr) :node(theNode) {};

		T& operator*() { return node->element; }
		T* operator->() { return &node->element; }

		iterator& operator++()
		{
			node = node->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			node = node->next;
			return old;
		}

		bool operator==(const iterator right) const { return node == right.node; }
		bool operator!=(const iterator right) const { return node != right.node; }

	protected:
		chainNode<T>* node;
	};

	class const_iterator
	{
	public:
		typedef forward_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;

		const_iterator(chainNode<T>* theNode) :node(theNode) {};

		const T& operator*() { return node->element; }
		const T* operator->() { return &node->element; }

		const_iterator& operator++()
		{
			node = node->next;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			node = node->next;
			return old;
		}

		bool operator==(const const_iterator right) const { return node == right.node; }
		bool operator!=(const const_iterator right) const { return node != right.node; }

	protected:
		chainNode<T>* node;
	};

protected:
	chainNode<T>* pHead;
	chainNode<T>* pTail;
	int listSize;
	void checkIndex(int) const;
};



template<typename T>
chain<T>::chain(int initialCapacity)
{
	if (initialCapacity < 1)	throw out_of_range("the initial Capacity of arrayList must > 0");
	listSize = 0;
	pHead = new chainNode<T>(T());
	pTail = pHead;
}

template<typename T>
chain<T>::chain(const chain<T>& c)
{
	pHead = new chainNode<T>(c.pHead->element);
	pTail = pHead;
	chainNode<T>* sourceNode = c.pHead->next;
	chainNode<T>* currentNode = pHead;
	while (sourceNode != nullptr)
	{
		pTail = currentNode->next = new chainNode<T>(sourceNode->element);
		currentNode = currentNode->next;
		sourceNode = sourceNode->next;
	}
	listSize = c.listSize;
}

template<typename T>
chain<T>::~chain()
{
	chainNode<T>* currentNode = pHead->next;
	chainNode<T>* deleteNode;
	while (currentNode != nullptr)
	{
		deleteNode = currentNode;
		currentNode = currentNode->next;
		delete deleteNode;
	}
	delete pHead;
}


template<typename T>
bool chain<T>::empty() const { return listSize == 0; }

template<typename T>
int chain<T>::size() const { return listSize; }

template<typename T>
int chain<T>::find(const T& theElement) const
{
	int index = 0;
	chainNode<T>* currentNode = pHead->next;
	while (currentNode != nullptr)
	{
		if (currentNode->element == theElement)	return index;
		currentNode = currentNode->next;
		++index;
	}
	return -1;
}

template<typename T>
void chain<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	chainNode<T>* deleteNode;
	chainNode<T>* pre = pHead;
	for (int i = 0; i < theIndex; ++i)	pre = pre->next;
	if (theIndex == listSize - 1)	pTail = pre;
	deleteNode = pre->next;
	pre->next = pre->next->next;
	--listSize;
	delete deleteNode;
}

template<typename T>
void chain<T>::insert(int theIndex, const T& theElement)
{
	if (theIndex < 0 || theIndex>listSize)	throw out_of_range("illegalIndex");
	chainNode<T>* pre = pHead;
	for (int i = 0; i < theIndex; ++i)	pre = pre->next;
	pre->next = new chainNode<T>(theElement, pre->next);
	if (theIndex == listSize)	pTail = pre->next;
	++listSize;
}


template<typename T>
void chain<T>::clear()
{
	chainNode<T>* currentNode = pHead->next;
	chainNode<T>* deleteNode;
	while (currentNode != nullptr)
	{
		deleteNode = currentNode;
		currentNode = currentNode->next;
		delete deleteNode;
	}
	listSize = 0;
	pHead->next = nullptr;
	pTail = pHead;
}

template<typename T>
void chain<T>::push_back(const T& theElement)
{
	pTail->next = new chainNode<T>(theElement, pTail->next);
	pTail = pTail->next;
	listSize++;
}

template<typename T>
chain<T>& chain<T>::operator=(const chain<T>& c)
{
	if (this == &c)	return *this;
	clear();
	chainNode<T>* currentNode = pHead;
	chainNode<T>* sourceNode = c.pHead->next;
	while (sourceNode != nullptr)
	{
		pTail = currentNode->next = new chainNode<T>(sourceNode->element);
		currentNode = currentNode->next;
		sourceNode = sourceNode->next;
	}
	listSize = c.listSize;
	return *this;
}

template<typename T>
T& chain<T>::operator[](int index)
{
	checkIndex(index);
	chainNode<T>* currentNode = pHead->next;
	for (int i = 0; i < index; ++i)	currentNode = currentNode->next;
	return currentNode->element;
}

template<typename T>
const T& chain<T>::operator[](int index) const
{
	checkIndex(index);
	chainNode<T>* currentNode = pHead->next;
	for (int i = 0; i < index; ++i)	currentNode = currentNode->next;
	return currentNode->element;
}

template<typename T>
void chain<T>::checkIndex(int theIndex) const
{
	if (theIndex < 0 || theIndex >= listSize)
		throw out_of_range("the index is out of range");
}

#endif //__CHAIN_H_