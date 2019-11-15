#ifndef binaryTreeNode_
#define binaryTreeNode_

template<typename T>
struct binaryTreeNode {
	T element;
	binaryTreeNode<T>* leftChild;//������
	binaryTreeNode<T>* rightChild;//������
	binaryTreeNode<T>* father;//����

	binaryTreeNode(){}
	binaryTreeNode(const T& theElement) : element(theElement) {
		leftChild = rightChild = father = nullptr;
	}
	bool operator<(const binaryTreeNode<T>& x) const {
		return element < x.element;
	}
};

#endif //binaryTreeNode_