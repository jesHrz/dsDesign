#pragma once
#include <cstring>
#define sz(a) sizeof(a)
class SuffixTreeNode {
public:
	int len, link, firstpos, endpos;
	int* next;
	int alpha_size;
	SuffixTreeNode(const int M = 26) :alpha_size(M) {
		len = link = firstpos = endpos = 0;
	}
	SuffixTreeNode(const SuffixTreeNode& t) {
		len = t.len;
		link = t.link;
		firstpos = t.firstpos;
		endpos = t.endpos;
		alpha_size = t.alpha_size;
		allocatNext();
		memcpy(next, t.next, sz(int) * alpha_size);
	}
	~SuffixTreeNode() { delete[] next; }
	void allocatNext() {
		next = new int[alpha_size];
		memset(next, 0, sz(int) * alpha_size);
	}
};