#ifndef Huffman_
#define Huffman_

#include <utility>
#include <queue/linkedQueue.h>
#include "Heap.h"
#include "binaryTreeNode.h"

using namespace std;

template<typename T>
class Compare {
	typedef pair<T, int> pti;
public:
	bool operator()(binaryTreeNode<pti>* a, binaryTreeNode<pti>* b) const {
		return a->element.second < b->element.second;
	}
};

template<typename T>
class Huffman {
	typedef pair<T, int> pti;
private:
	Heap<binaryTreeNode<pti>*, Compare<T>> h;
	binaryTreeNode<pti>* root;
public:
	Huffman(int n, pti* a);
	~Huffman();

	binaryTreeNode<pti>* create();

	void preOrder(binaryTreeNode<pti>*);
	void inOrder(binaryTreeNode<pti>*);
	void postOrder(binaryTreeNode<pti> *);
	void levelOrder(binaryTreeNode<pti>*);

	void destroy(binaryTreeNode<pti>*);
};

template <typename T>
Huffman<T>::Huffman(int n, pti* a) {
	while (!h.empty())	h.pop();
	for (auto i = 0; i < n; ++i)	h.push(new binaryTreeNode<pair<T, int>>(a[i]));
	root = nullptr;
}

template <typename T>
Huffman<T>::~Huffman() {
	destroy(root);
}

template <typename T>
binaryTreeNode<pair<T, int> >* Huffman<T>::create() {
	while(h.size() > 1) {
		binaryTreeNode<pair<T, int>>* t1 = h.top(); h.pop();
		binaryTreeNode<pair<T, int>>* t2 = h.top(); h.pop();
		binaryTreeNode<pair<T, int>>* t = new binaryTreeNode<pair<T, int>>(make_pair(0, t1->element.second + t2->element.second));
		t->leftChild = t1;
		t->rightChild = t2;
		h.push(t);
	}
	root = h.top(); h.pop();
	return root;
}

template <typename T>
void Huffman<T>::preOrder(binaryTreeNode<pti>* rt) {
	if (rt == nullptr)	return;
	cout << rt->element.second << ' ';
	preOrder(rt->leftChild);
	preOrder(rt->rightChild);
}

template <typename T>
void Huffman<T>::inOrder(binaryTreeNode<pti>* rt) {
	if (rt == nullptr)	return;
	preOrder(rt->leftChild);
	cout << rt->element.second << ' ';
	preOrder(rt->rightChild);
}

template <typename T>
void Huffman<T>::postOrder(binaryTreeNode<pti>* rt) {
	if (rt == nullptr)	return;
	preOrder(rt->leftChild);
	preOrder(rt->rightChild);
	cout << rt->element.second << ' ';
}

template <typename T>
void Huffman<T>::levelOrder(binaryTreeNode<pti>* rt) {
	linkedQueue<binaryTreeNode<pti>*> q;
	q.push(rt);
	while(!q.empty()) {
		binaryTreeNode<pti>* p = q.front(); q.pop();
		if (p == nullptr)	continue;
		cout << p->element.second << ' ';
		q.push(p->leftChild);
		q.push(p->rightChild);
	}
}

template <typename T>
void Huffman<T>::destroy(binaryTreeNode<pti>* rt) {
	if (rt == nullptr)	return;
	destroy(rt->leftChild);
	destroy(rt->rightChild);
	delete rt;
}

#endif //Huffman_
