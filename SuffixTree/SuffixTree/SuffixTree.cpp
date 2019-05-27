#include "SuffixTree.h"
#include <cstring>


SuffixTree::SuffixTree(const char str[], const int M) {
	s = str;
	int n = strlen(s);
	MAX_SIZE = n * 2;
	sz = last = 0;
	// 数组初始化
	st = new SuffixTreeNode[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; ++i)	st[i].allocatNext();
	init();
	//在线构造后缀树
	for (int i = 0; i < n; ++i) add(s[i] - 'a');
	get_endpos();
}


SuffixTree::SuffixTree(const SuffixTree & t) {
	MAX_SIZE = t.MAX_SIZE;
	last = t.last;
	sz = t.sz;
	s = t.s;
	st = new SuffixTreeNode[MAX_SIZE];
	for (int i = 0; i < sz; ++i)	st[i] = SuffixTreeNode(t.st[i]);
}


SuffixTree::~SuffixTree() {
	delete[] st;
	delete[] e;
	delete[] deg;
	delete[] head;
}


void SuffixTree::init() {
	st[0].link = -1;
	st[0].len = 0;
	memset(st[0].next, 0, sizeof(int) * st[0].alpha_size);
	last = 0;
	sz = 1;
}


void SuffixTree::add(int c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	st[cur].firstpos = st[cur].len - 1;
	int p = last;
	while (p != -1 && !st[p].next[c]) {
		st[p].next[c] = cur;
		p = st[p].link;
	}
	if (p == -1) {
		st[cur].link = 0;
	}
	else {
		int q = st[p].next[c];
		if (st[p].len + 1 == st[q].len) {
			st[cur].link = q;
		}
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			memcpy(st[clone].next, st[q].next, sizeof(int) * st[clone].alpha_size);
			st[clone].link = st[q].link;
			st[clone].firstpos = st[q].firstpos;
			while (p != -1 && st[p].next[c] == q) {
				st[p].next[c] = clone;
				p = st[p].link;
			}
			st[q].link = st[cur].link = clone;
		}
	}
	last = cur;
}


void SuffixTree::get_endpos() {
	//桶排序 按长度从大到小
	int* tmp = new int[sz + 1];
	int* ind = new int[sz + 1];
	deg = new int[sz + 1];
	head = new int[sz + 1];
	e = new edge[MAX_SIZE];
	cnt = 0;

	for (int i = 0; i < sz; ++i) head[i] = deg[i] = ind[i] = tmp[i] = 0;
	for (int i = 1; i < sz; ++i) tmp[st[i].len]++;
	for (int i = 1; i < sz; ++i) tmp[i] += tmp[i - 1];
	for (int i = 1; i < sz; ++i) ind[tmp[st[i].len]--] = i;
	int cur = 0;
	int n = strlen(s);
	//叶子节点初始化为1
	for (int i = 0; i < n; ++i) {
		cur = st[cur].next[s[i] - 'a'];
		st[cur].endpos = 1;
	}
	//树上dp 建立树形图
	for (int i = sz - 1; i > 0; --i) {
		int cur = ind[i];
		if (~st[cur].link) {
			st[st[cur].link].endpos += st[cur].endpos;
			add_edge(st[i].link, i);
			deg[st[i].link]++;
		}
	}
	ssm << ".\n";
	build(0, 0);
	delete[] tmp;
	delete[] ind;
}

void SuffixTree::add_edge(int u, int v) {
	e[++cnt] = { v, head[u] };
	head[u] = cnt;
}

//打印后缀树
void SuffixTree::build(int u, int dep) {
	if (st[u].len) {
		for (int i = 0; i < dep - 1; ++i) ssm << "|   ";
		if (--deg[st[u].link])
			ssm << "+---";
		else
			ssm << "+---";
		for (int i = 0; i < st[u].len; ++i) ssm << *(s + st[u].firstpos - st[u].len + 1 + i);
		ssm << '\n';
	}

	for (int i = head[u]; i; i = e[i].next) {
		int v = e[i].to;
		build(v, dep + 1);
	}
}


int SuffixTree::_find(const char ptr[]) const {
	int n = strlen(ptr);
	int cur = 0;
	//沿状态转移
	for (int i = 0; i < n; ++i) {
		if (st[cur].next[ptr[i] - 'a'])	cur = st[cur].next[ptr[i] - 'a'];
		else return -1;
	}
	return cur;
}


int SuffixTree::find(const char ptr[]) const {
	int cur = _find(ptr);
	if (~cur)	return st[cur].firstpos - strlen(ptr) + 1;
	return -1;
}


int SuffixTree::count(const char ptr[]) const {
	int cur = _find(ptr);
	if (cur == -1)	return 0;
	return st[cur].endpos;
}


int SuffixTree::lcs(const char ptr[], char res[] = nullptr) const {
	int n = strlen(ptr);
	int cur = 0, l = 0, best = 0, bestpos = 0;
	for (int i = 0; i < n; ++i) {
		//当前状态不存在ptr[i]的转移
		while (cur && !st[cur].next[ptr[i] - 'a']) {
			cur = st[cur].link;
			l = st[cur].len;
		}
		if (st[cur].next[ptr[i] - 'a']) {
			cur = st[cur].next[ptr[i] - 'a'];
			l++;
		}
		//更新答案
		if (best < l) {
			best = l;
			bestpos = i;
		}
	}
	if (res)	memcpy(res, ptr + bestpos - best + 1, best);
	return best;
}


int SuffixTree::LongestRepetitiveSubstring(char res[]) const {
	//桶排序 按长度从大到小
	int* tmp = new int[sz + 1];
	int* ind = new int[sz + 1];
	for (int i = 0; i < sz; ++i) ind[i] = tmp[i] = 0;
	for (int i = 1; i < sz; ++i) tmp[st[i].len]++;
	for (int i = 1; i < sz; ++i) tmp[i] += tmp[i - 1];
	for (int i = 1; i < sz; ++i) ind[tmp[st[i].len]--] = i;
	//从大到小遍历节点
	for (int i = sz - 1; i; --i) {
		int cur = ind[i];
		if (st[cur].endpos > 1) {
			memcpy(res, s + st[cur].firstpos - st[cur].len + 1, st[cur].len);
			return st[cur].len;
		}
	}
	return -1;
}