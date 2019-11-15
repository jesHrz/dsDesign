#ifndef skipList_
#define skipList_

#include <utility>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include "skipNode.h"

template<typename K, typename E>
class skipList {
public:
	skipList(const K, const K, int = 100000, float = 0.5);
	~skipList();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	std::pair<const K, E>* find(const K&) const;
	void insert(const K&, const E&);
	void erase(const K&);
	void eraseMinKey();
	void eraseMaxKey();


	void output(std::ostream& = std::cout);

protected:
	float prob; // 级分配的可能
	int dSize; // 节点个数
	int maxLevel; // 最大层数
	int level; // 当前层数
	K tailKey; // 最大键值
	K headKey; // 最小键值

	skipNode<K, E>* headNode; // 头节点
	skipNode<K, E>* tailNode; // 尾节点 不需要指针域
	skipNode<K, E>** last; // 记录查询到的最后一个指针
};

template<typename K, typename E>
skipList<K, E>::skipList(const K headKey, const K tailKey, int maxPaires, float prob) {
	this->prob = prob * RAND_MAX;
	this->maxLevel = ceil(log(maxPaires) / log(1 / prob));
	this->dSize = this->level = 0;
	this->tailKey = tailKey;
	this->headKey = headKey;

	std::pair<K, E> tailPair;
	tailPair.first = headKey;
	headNode = new skipNode<K, E>(tailPair, maxLevel);
	tailPair.first = tailKey;
	tailNode = new skipNode<K, E>(tailPair, 0);
	last = new skipNode<K, E>*[maxLevel];

	for (int i = 0; i < maxLevel; ++i)	headNode->next[i] = tailNode;
}

template<typename K, typename E>
skipList<K, E>::~skipList() {
	while (headNode != tailNode) {
		skipNode<K, E>* nextNode = headNode->next[0];
		delete headNode;
		headNode = nextNode;
	}
	delete tailNode;
	delete[] last;
}

template<typename K, typename E>
std::pair<const K, E>* skipList<K, E>::find(const K& theKey) const {
	if (theKey >= tailKey || theKey <= headKey)	return nullptr;
	int cnt = 1;
	skipNode<K, E>* nextNode = headNode;
	for (int i = level; i >= 0; --i) {
		while (nextNode->next[i]->element.first < theKey) {
			nextNode = nextNode->next[i];
			cnt++;
		}
	}
	std::cout << "find: " << cnt << std::endl;
	if (nextNode->next[0]->element.first == theKey)	return &nextNode->next[0]->element;
	return nullptr;
}

template<typename K, typename E>
void skipList<K, E>::insert(const K& theKey, const E& theElement) {
	if (theKey >= tailKey || theKey <= headKey) {
		return;
	}
	int cnt = 0;
	skipNode<K, E>* nextNode = headNode;
	for (int i = level; i >= 0; --i) {
		while (nextNode->next[i]->element.first < theKey) {
			nextNode = nextNode->next[i];
			cnt++;
		}
		last[i] = nextNode;
	}
	nextNode = nextNode->next[0];

	if (nextNode->element.first == theKey) {
		nextNode->element.second = theElement;
		std::cout << "insert: " << cnt << std::endl;
		return;
	}

	int lev = 0;
	while (rand() <= prob)	lev++;
	if (lev >= maxLevel)	lev = maxLevel - 1;
	if (lev > level) {
		lev = ++level;
		last[lev] = headNode;
	}

	skipNode<K, E>* newNode = new skipNode<K, E>(std::make_pair(theKey, theElement), lev + 1);
	for (int i = 0; i <= lev; ++i) {
		newNode->next[i] = last[i]->next[i];
		last[i]->next[i] = newNode;
		cnt += 2;
	}
	std::cout << "insert: " << cnt << std::endl;
	dSize++;
}

template<typename K, typename E>
void skipList<K, E>::erase(const K& theKey) {
	if (theKey >= tailKey || theKey <= headKey) {
		return;
	}

	int cnt = 0;
	skipNode<K, E>* nextNode = headNode;

	for (int i = level; i >= 0; --i) {
		while (nextNode->next[i]->element.first < theKey) {
			nextNode = nextNode->next[i];
			cnt++;
		}
		last[i] = nextNode;
	}
	nextNode = nextNode->next[0];

	if (nextNode->element.first != theKey)	return;

	for (int i = 0; i <= level; ++i) {
		if (last[i]->next[i] != nextNode)	break;
		last[i]->next[i] = nextNode->next[i];
		cnt++;
	}
	std::cout << "erase: " << cnt << std::endl;
	while (level > 0 && headNode->next[level] == tailNode)	level--;

	delete nextNode;
	dSize--;
}

template<typename K, typename E>
void skipList<K, E>::eraseMinKey() {
	skipNode<K, E>* theNode = headNode->next[0];
	if (theNode == tailNode)	return;
	erase(theNode->element.first);
}

template<typename K, typename E>
void skipList<K, E>::eraseMaxKey() {
	skipNode<K, E>* nextNode = headNode->next[0];
	int maxKey = headKey;
	while (nextNode != tailNode) {
		maxKey = nextNode->element.first;
		nextNode = nextNode->next[0];
	}
	if (maxKey == headKey)	return;
	this->erase(maxKey);
}

template<typename K, typename E>
void skipList<K, E>::output(std::ostream& out) {
	skipNode<K, E> *theNode;
	for (int i = level; i >= 0; --i) {
		out << headNode->to_str() << ' ';
		theNode = headNode->next[0];
		while (theNode != tailNode) {
			if (theNode->size < i) for (int i = 0; i < theNode->to_str().length() + 4; ++i)	out << '-';
			else out << "-> " << theNode->to_str() << ' ';
			theNode = theNode->next[0];
		}
		out << "-> " << tailNode->to_str() << std::endl;
	}
	out << std::endl;
}

#endif 