#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include "linkedBinaryTree.h""
#include "binaryTreeNode.h"
#include <iostream>

template<typename T>
class binary_seach_tree : linkedBinaryTree<pair<int, T>> {
public:
	typedef binaryTreeNode<pair<int, T>> node;

	binary_seach_tree() { this->root = nullptr; }
	~binary_seach_tree() {}

	bool empty() const override { return linkedBinaryTree<pair<int, T>>::empty(); }
	int size() const override { return linkedBinaryTree<pair<int, T>>::size(); }
	int height() const { return linkedBinaryTree<pair<int, T>>::height(); }

	pair<int, T>* find(const T&);
	pair<int, T>* find_by_rank(int);

	void insert(const T& element) { insert(this->root, element); };

	void erase(const T&);
	void erase_by_rank(int);

	void ascend() { this->inOrder(output); std::cout << std::endl; }
protected:
	static int insert(node*&, const T&);
	static node* erase(node*, const T&);
	static node* erase_by_rank(node*, int);
	static void output(node* t) { std::cout << t->element.second << ' '; }
};



template<typename T>
pair<int, T>* binary_seach_tree<T>::find(const T& element) {
	node* rt = this->root;
	while (rt != nullptr) {
		cout << rt->element.second << ' ';
		if (rt->element.second < element)rt = rt->rightChild;
		else if (rt->element.second > element) rt = rt->leftChild;
		else return &rt->element;
	}
	return nullptr;
}

template <typename T>
pair<int, T>* binary_seach_tree<T>::find_by_rank(int rank) {
	node* rt = this->root;
	while (rt != nullptr) {
		cout << rt->element.second << ' ';
		if (rt->element.first + 1 < rank) {
			//find in rightChild with rank - leftSize - 1
			rank -= rt->element.first + 1;
			rt = rt->rightChild;
		}
		//find in leftChild with rank
		else if (rt->element.first + 1 > rank) rt = rt->leftChild;
		else return &rt->element;
	}
	return nullptr;
}

//if insert an element successfully, return 1, else 0
template<typename T>
int binary_seach_tree<T>::insert(node*& rt, const T& element) {
	if (rt == nullptr) {
		rt = new node(make_pair(0, element));
		return 1;
	}
	if (rt->element.second < element) {
		if (rt->rightChild == nullptr) {
			node* new_node = new node(make_pair(0, element));
			new_node->father = rt;
			rt->rightChild = new_node;
			return 1;
		}
		return insert(rt->rightChild, element);
	}
	else if (rt->element.second > element) {
		if (rt->leftChild == nullptr) {
			node* new_node = new node(make_pair(0, element));
			new_node->father = rt;
			rt->leftChild = new_node;
			++rt->element.first;
			return 1;
		}
		int add = insert(rt->leftChild, element);
		//if success, leftSize increase
		rt->element.first += add;
		return add;
	}
	return 0;
}

template<typename T>
void binary_seach_tree<T>::erase(const T& element) {
	node* p = erase(this->root, element);//find the element
	node* pp = nullptr;
	if (p != nullptr) {
		if (p->rightChild != nullptr && p->leftChild != nullptr) {//both have leftChild and rightChild
			pp = p->rightChild;
			while (pp->leftChild != nullptr) {//find the minium one
				--pp->element.first;//lose one of their leftChild
				pp = pp->leftChild;
			}

			if (pp->father == p) {//if p is pp's father
				pp->father->rightChild = pp->rightChild;
				if (pp->rightChild != nullptr)	pp->rightChild->father = pp->father;
			}
			else {//let pp's rightChild be its father's leftChild 
				pp->father->leftChild = pp->rightChild;
				if (pp->rightChild != nullptr)	pp->rightChild->father = pp->father;
			}
			//implement all element in node p
			pp->element.first = p->element.first;

			pp->leftChild = p->leftChild;
			if (pp->leftChild != nullptr)	pp->leftChild->father = pp;

			pp->rightChild = p->rightChild;
			if (pp->rightChild != nullptr) pp->rightChild->father = pp;

			pp->father = p->father;
		}
		//only have one child
		else if (p->leftChild != nullptr) {
			if (p != this->root) {
				if (p->father->leftChild == p)	p->father->leftChild = p->leftChild;
				else p->father->rightChild = p->leftChild;
				if (p->leftChild != nullptr)	p->leftChild->father = p->father;
			}
			else {
				this->root = p->leftChild;
			}
			delete p;
			return;
		}
		else if (p->rightChild != nullptr) {
			if (p != this->root) {
				if (p->father->leftChild == p)	p->father->leftChild = p->rightChild;
				else p->father->rightChild = p->rightChild;
				if (p->rightChild != nullptr)p->rightChild->father = p->father;
			}
			else {
				this->root = p->rightChild;
			}
			delete p;
			return;
		}
		//check whether p is the root
		if (p == this->root) {
			this->root = pp;
		}
		else {
			if (p->father->leftChild == p)	p->father->leftChild = pp;
			else p->father->rightChild = pp;
		}
		delete p;
	}
}

template<typename T>
binaryTreeNode<pair<int, T>>* binary_seach_tree<T>::erase(node* rt, const T& element) {
	if (rt == nullptr) return nullptr;
	if (rt->element.second < element) return erase(rt->rightChild, element);
	else if (rt->element.second > element) {
		//they will lose thier leftChild, so the leftSize will decrease
		node* tmp = erase(rt->leftChild, element);
		if (tmp != nullptr)	--rt->element.first;
		return tmp;
	}
	else return rt;
}

template<typename T>
void binary_seach_tree<T>::erase_by_rank(int rank) {
	node* p = erase_by_rank(this->root, rank);//find the element
	node* pp = nullptr;
	if (p != nullptr) {
		if (p->rightChild != nullptr && p->leftChild != nullptr) {//both have leftChild and rightChild
			pp = p->rightChild;
			while (pp->leftChild != nullptr) {//find the minium one
				--pp->element.first;//lose one of their leftChild
				pp = pp->leftChild;
			}

			if (pp->father == p) {//if p is pp's father
				pp->father->rightChild = pp->rightChild;
				if (pp->rightChild != nullptr)	pp->rightChild->father = pp->father;
			}
			else {//let pp's rightChild be its father's leftChild 
				pp->father->leftChild = pp->rightChild;
				if (pp->rightChild != nullptr)	pp->rightChild->father = pp->father;
			}
			//implement all element in node p
			pp->element.first = p->element.first;

			pp->leftChild = p->leftChild;
			if (pp->leftChild != nullptr)	pp->leftChild->father = pp;

			pp->rightChild = p->rightChild;
			if (pp->rightChild != nullptr) pp->rightChild->father = pp;

			pp->father = p->father;
		}
		//only have one child
		else if (p->leftChild != nullptr) {
			if (p != this->root) {
				if (p->father->leftChild == p)	p->father->leftChild = p->leftChild;
				else p->father->rightChild = p->leftChild;
				if (p->leftChild != nullptr)	p->leftChild->father = p->father;
			}
			else {
				this->root = p->leftChild;
			}
			delete p;
			return;
		}
		else if (p->rightChild != nullptr) {
			if (p != this->root) {
				if (p->father->leftChild == p)	p->father->leftChild = p->rightChild;
				else p->father->rightChild = p->rightChild;
				if (p->rightChild != nullptr)p->rightChild->father = p->father;
			}
			else {
				this->root = p->rightChild;
			}
			delete p;
			return;
		}
		//check whether p is the root
		if (p == this->root) {
			this->root = pp;
		}
		else {
			if (p->father->leftChild == p)	p->father->leftChild = pp;
			else p->father->rightChild = pp;
		}
		delete p;
	}
}

template<typename T>
binaryTreeNode<pair<int, T>>* binary_seach_tree<T>::erase_by_rank(node* rt, int rank) {
	if (rt == nullptr) return nullptr;
	if (rt->element.first + 1 < rank) return erase_by_rank(rt->rightChild, rank - 1 - rt->element.first);
	else if (rt->element.first + 1 > rank) {
		// they will lose their leftChild, so the leftSize will decrease
		node* tmp = erase_by_rank(rt->leftChild, rank);
		if (tmp != nullptr)	--rt->element.first;
		return tmp;
	}
	else return rt;
}

#endif //BINARY_SEARCH_TREE
