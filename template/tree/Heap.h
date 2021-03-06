#ifndef Heap_
#define Heap_

#include <stdexcept>
#include <cstring>
#include <iostream>

template<typename T, typename Pr = std::greater<T> >
class Heap {
public:
	Heap(int = 10);
	Heap(const Heap<T, Pr>&);
	~Heap() {
		delete[] heap;
	}

	bool empty() const { return heapSize == 0; }
	int size() const { return heapSize; }

	const T& top() {
		if (heapSize < 1)	throw std::out_of_range("heap is empty");
		return heap[1];
	}
	void pop();
	void push(const T&);
	void init(T*, T*);
	void erase(const T&);

	void output(std::ostream&, char = '\n');

protected:
	int heapSize;
	int arrayLength;
	T* heap;
	Pr cmp;
};

template<typename T, typename cmp>
Heap<T, cmp>::Heap(int initialCapacity) : cmp() {
	if (initialCapacity < 1)	throw std::out_of_range("the initial Capacity of heap mut > 0");
	arrayLength = initialCapacity + 1;
	heap = new T[arrayLength];
	heapSize = 0;
}

template<typename T, typename Pr>
Heap<T, Pr>::Heap(const Heap<T, Pr>& theHeap) {
	arrayLength = theHeap.arrayLength;
	heapSize = theHeap.heapSize;
	heap = new T[arrayLength];
	copy(theHeap.heap, theHeap.head + heapSize + 1, heap);
}

template<typename T, typename Pr>
void Heap<T, Pr>::pop() {
	heap[1] = heap[heapSize--];
	int k = 1, c = 2;
	while (c <= heapSize) {
		if (c < heapSize && !cmp(heap[c], heap[c | 1]))	c |= 1;
		if (cmp(heap[k], heap[c]))	break;
		std::swap(heap[k], heap[c]);
		k = c;
		c <<= 1;
	}
}

template<typename T, typename Pr>
void Heap<T, Pr>::push(const T& element) {
	if (heapSize >= arrayLength - 1) {
		T* temp = new T[arrayLength * 2];
		for (int i = 1; i <= heapSize; ++i)	temp[i] = heap[i];
		delete[] heap;
		heap = temp;
		arrayLength *= 2;
	}
	heap[++heapSize] = element;
	int k = heapSize;
	while (k != 1) {
		if (cmp(heap[k], heap[k >> 1]))	std::swap(heap[k], heap[k >> 1]);
		k >>= 1;
	}
}

template<typename T, typename Pr>
void Heap<T, Pr>::init(T* begin, T* end) {
	delete[] heap;
	heapSize = end - begin;
	arrayLength = heapSize;
	heap = new T[arrayLength + 1];
	for (int i = 1; i <= heapSize; ++i)	heap[i] = *(begin + i - 1);
	for (int rt = heapSize / 2; rt; --rt) {
		int k = rt;
		int c = k << 1;
		while (c <= heapSize) {
			if (c < heapSize && !cmp(heap[c], heap[c | 1]))	c |= 1;
			if (cmp(heap[k], heap[c]))	break;
			std::swap(heap[k], heap[c]);
			k = c;
			c <<= 1;
		}
	}
}

template<typename T, typename Pr>
void Heap<T, Pr>::erase(const T& element) {
	int k = heapSize;
	for (int i = 1; i <= heapSize; ++i) {
		if (heap[i] == element) {
			heap[i] = heap[heapSize];
			heap[heapSize--].~T();
			k = i;
			break;
		}
	}
	int c = k << 1;
	while (c <= heapSize) {
		if (c < heapSize && !cmp(heap[c], heap[c << 1]))	c |= 1;
		if (cmp(heap[k], heap[c]))	break;
		std::swap(heap[k], heap[c]);
		k = c;
		c <<= 1;
	}
}

template<typename T, typename Pr>
void Heap<T, Pr>::output(std::ostream& out, char ends) {
	for (int i = 1; i <= heapSize; ++i)	out << heap[i] << ' ';
	out << ends;
}



#endif //Heap_