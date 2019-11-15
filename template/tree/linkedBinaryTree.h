#ifndef linkedBinaryTree_
#define linkedBinaryTree_

#include "binaryTreeNode.h"
#include "binaryTree.h"
#include <queue/linkedQueue.h>
#include <iostream>

template<typename T>
class linkedBinaryTree : public binaryTree<binaryTreeNode<T> > {
public:

	linkedBinaryTree() { root = nullptr; };
	virtual ~linkedBinaryTree() { erase(); };

	bool operator<(const linkedBinaryTree<T>& x) const {
		return root->element < x.root->element;
	}

	bool empty() const { return size(root) == 0; };
	int size() const { return size(root); };

	//������
	binaryTreeNode<T>*& getRoot() {
		return root;
	}
	//ǰ�����
	void preOrder(void(*visit)(binaryTreeNode<T>*) = linkedBinaryTree<T>::output) {
		preOrder(root, visit);
	};
	//�������
	void inOrder(void(*visit)(binaryTreeNode<T>*) = linkedBinaryTree<T>::output) {
		inOrder(root, visit);
	};
	//�������
	void postOrder(void(*visit)(binaryTreeNode<T>*) = linkedBinaryTree<T>::output) {
		postOrder(root, visit);
	};
	//��α���
	void levelOrder(void(*visit)(binaryTreeNode<T>*) = linkedBinaryTree<T>::output) {
		levelOrder(root, visit);
	};
	//�����
	void erase() {
		postOrder(dispose);
		root = nullptr;
	}
	//����
	void makeTree(const T&, linkedBinaryTree<T>&, linkedBinaryTree&);
	//������
	int height() const { return height(root); };


protected:
	binaryTreeNode<T>* root;
	static void preOrder(binaryTreeNode<T>*, void(*)(binaryTreeNode<T>*));
	static void inOrder(binaryTreeNode<T>*, void(*)(binaryTreeNode<T>*));
	static void postOrder(binaryTreeNode<T>*, void(*)(binaryTreeNode<T>*));
	static void levelOrder(binaryTreeNode<T>*, void(*)(binaryTreeNode<T>*));
	static void dispose(binaryTreeNode<T>* t) { delete t; }
	static int size(binaryTreeNode<T>*);
	static int height(binaryTreeNode<T>*);
	static void output(binaryTreeNode<T>* t) { std::cout << t->element << ' '; }
};


template<typename T>
void linkedBinaryTree<T>::preOrder(binaryTreeNode<T>* t, void(*visit)(binaryTreeNode<T>*)) {
	if (t == nullptr)	return;
	visit(t);
	preOrder(t->leftChild, visit);
	preOrder(t->rightChild, visit);
}

template<typename T>
void linkedBinaryTree<T>::inOrder(binaryTreeNode<T>* t, void(*visit)(binaryTreeNode<T>*)) {
	if (t == nullptr)	return;
	inOrder(t->leftChild, visit);
	visit(t);
	inOrder(t->rightChild, visit);
}

template<typename T>
void linkedBinaryTree<T>::postOrder(binaryTreeNode<T>* t, void(*visit)(binaryTreeNode<T>*)) {
	if (t == nullptr)	return;
	postOrder(t->leftChild, visit);
	postOrder(t->rightChild, visit);
	visit(t);
}

template<typename T>
void linkedBinaryTree<T>::levelOrder(binaryTreeNode<T>* t, void(*visit)(binaryTreeNode<T>*)) {
	linkedQueue<binaryTreeNode<T>* >q;
	q.push(t);
	while (!q.empty()) {
		binaryTreeNode<T>* p = q.front(); q.pop();
		if (p == nullptr)	continue;
		visit(p);
		q.push(p->leftChild);
		q.push(p->rightChild);
	}
}

template<typename T>
void linkedBinaryTree<T>::makeTree(const T& theElement, linkedBinaryTree<T>& left, linkedBinaryTree<T>& right) {
	root = new binaryTreeNode<T>(theElement);
	root->leftChild = left.root;
	root->rightChild = right.root;

	if (root->leftChild != nullptr)	root->leftChild->father = root;
	if (root->rightChild != nullptr) root->rightChild->father = root;

	left.root = right.root = nullptr;
}

template<typename T>
int linkedBinaryTree<T>::height(binaryTreeNode<T>* t) {
	if (t == nullptr)	return 0;
	int hl = height(t->leftChild);
	int hr = height(t->rightChild);
	//���ߵ����������������߶ȼ�һ
	return (hl > hr ? hl : hr) + 1;
}

template<typename T>
int linkedBinaryTree<T>::size(binaryTreeNode<T>* t) {
	if (t == nullptr)	return 0;
	//�ڵ�����������������ڵ����֮���ټ�һ
	return size(t->leftChild) + size(t->rightChild) + 1;
}

#endif linkedBinaryTree_