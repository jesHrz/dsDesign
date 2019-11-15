#pragma once
#include <cstring>
#define sz(a) sizeof(a)
class SuffixTreeNode {
public:
	//长度 后缀链接 第一次出现的位置 结尾集合
	int len, link, firstpos, endpos;
	int* next;
	//字符集大小
	int alpha_size;

	SuffixTreeNode(const int M = 26) : alpha_size(M) {
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