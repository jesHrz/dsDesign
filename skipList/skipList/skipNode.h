#ifndef skipNode_
#define skipNode_

#include <utility>
#include <string>

template<typename K, typename E>
struct skipNode {
	std::pair<const K, E> element;
	skipNode<K, E> **next;
	int size;
	skipNode(const std::pair<const K, E>& thePair, int size) :element(thePair), size(size) {
		next = new skipNode<K, E>*[size];
	}

	std::string to_str() const {
		return std::string("(") + std::to_string(element.first) + std::string(", ") + std::to_string(element.second) + std::string(")");
	}

};

#endif