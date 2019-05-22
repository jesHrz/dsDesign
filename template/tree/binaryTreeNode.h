#ifndef binaryTreeNode_
#define binaryTreeNode_

template<typename T>
struct binaryTreeNode {
	T element;
	binaryTreeNode<T>* leftChild;//×ó×ÓÊ÷
	binaryTreeNode<T>* rightChild;//ÓÒ×ÓÊ÷
	binaryTreeNode<T>* father;//¸¸Ç×

	binaryTreeNode(){}
	binaryTreeNode(const T& theElement) : element(theElement) {
		leftChild = rightChild = father = nullptr;
	}
	bool operator<(const binaryTreeNode<T>& x) const {
		return element < x.element;
	}
};

#endif //binaryTreeNode_