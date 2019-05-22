#ifndef _minWinnerTree
#define _minWinnerTree

#include <stdexcept>
#include <iostream>
using namespace std;

template<typename T>
class minWinnerTree {
public:
	minWinnerTree(T* thePlayer, int n) {
		tree = nullptr;
		build(thePlayer, n);
	};
	~minWinnerTree() {
		delete[] tree;
	};

	void build(T*, int);
	void replay(int);
	int winner(int i = 1) const {
		return i < n ? tree[i] : 0;
	};
private:
	int lowExt;
	int offset;
	int *tree;
	int n;
	T *player;
	void play(int, int, int);
};

template<typename T>
void minWinnerTree<T>::build(T* thePlayer, int n) {
	if (n < 2)	throw std::logic_error("must have at least 2 players");
	player = thePlayer;
	this->n = n;
	delete[] tree;

	tree = new int[n];

	int i, s;
	for (s = 1; 2 * s <= n - 1; s += s);
	lowExt = 2 * (n - s);
	offset = 2 * s - 1;
	for (i = 2; i <= lowExt; i += 2) play((offset + i) / 2, i - 1, i);
	if (n & 1) {
		play(n / 2, tree[n - 1], lowExt + 1);
		i = lowExt + 3;
	}
	else i = lowExt + 2;
	for (; i <= n; i += 2)	play((i - lowExt + n - 1) / 2, i - 1, i);
}

template<typename T>
void minWinnerTree<T>::play(int p, int l, int r) {
	tree[p] = player[l] <= player[r] ? l : r;
	while ((p & 1) && p > 1) {
		tree[p >> 1] = player[tree[p - 1]] <= player[tree[p]] ? tree[p - 1] : tree[p];
		p >>= 1;
	}
}

template<typename T>
void minWinnerTree<T>::replay(int k) {
	if (k <= 0 || k > n)	return;
	int cur, l, r;
	if (k <= lowExt) {
		cur = (offset + k) / 2;
		l = 2 * cur - offset;
		r = l + 1;
	}
	else {
		cur = (k - lowExt + n - 1) / 2;
		if (2 * cur == n - 1) {
			l = tree[2 * cur];
			r = k;
		}
		else {
			l = 2 * cur - n + 1 + lowExt;
			r = l + 1;
		}
	}

	tree[cur] = player[l] <= player[r] ? l : r;
	if (cur == n - 1 && (n & 1)) {
		cur >>= 1;
		tree[cur] = player[tree[n - 1]] <= player[lowExt + 1] ? tree[n - 1] : lowExt + 1;
	}
	cur >>= 1;
	for (; cur >= 1; cur >>= 1) tree[cur] = player[tree[cur << 1]] <= player[tree[cur << 1 | 1]] ? tree[cur << 1] : tree[cur << 1 | 1];

}

#endif