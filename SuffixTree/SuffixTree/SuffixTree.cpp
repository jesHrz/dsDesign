#include "SuffixTree.h"
#include <cstring>


SuffixTree::SuffixTree(const char str[]) {
	s = str;
	int n = strlen(s);
	MAX_SIZE = n * 2;
	sz = last = 0;
	// �����ʼ��
	next = new int* [MAX_SIZE];
	link = new int[MAX_SIZE];
	len = new int[MAX_SIZE];
	firstpos = new int[MAX_SIZE];
	endpos = new int[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; ++i)	next[i] = new int[26];
	init();
	//���߹����׺��
	for (int i = 0; i < n; ++i) add(s[i] - 'a');
	get_endpos();
}


SuffixTree::SuffixTree(const SuffixTree & t) {
	MAX_SIZE = t.MAX_SIZE;
	last = t.last;
	sz = t.sz;
	s = t.s;
	next = new int* [MAX_SIZE];
	link = new int[MAX_SIZE];
	len = new int[MAX_SIZE];
	firstpos = new int[MAX_SIZE];
	endpos = new int[MAX_SIZE];
	for (int i = 0; i < MAX_SIZE; ++i) {
		next[i] = new int[26];
		memcpy(next[i], t.next[i], sizeof(int) * 26);
	}
	memcpy(link, t.link, sizeof(int) * MAX_SIZE);
	memcpy(len, t.len, sizeof(int) * MAX_SIZE);
	memcpy(firstpos, t.firstpos, sizeof(int) * MAX_SIZE);
	memcpy(endpos, t.endpos, sizeof(int) * MAX_SIZE);
}


SuffixTree::~SuffixTree() {
	for (int i = 0; i < MAX_SIZE; ++i)	delete[] next[i];
	delete[] next;
	delete[] link;
	delete[] len;
	delete[] firstpos;
	delete[] endpos;
}


void SuffixTree::init() {
	memset(link, 0, sizeof(int) * MAX_SIZE);
	memset(len, 0, sizeof(int) * MAX_SIZE);
	memset(firstpos, 0, sizeof(int) * MAX_SIZE);
	memset(endpos, 0, sizeof(int) * MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; ++i)	memset(next[i], 0, sizeof(int) * 26);
	link[0] = -1;
	len[0] = 0;
	last = 0;
	sz = 1;
}


void SuffixTree::add(int c) {
	int cur = sz++;
	len[cur] = len[last] + 1;
	firstpos[cur] = len[cur] - 1;
	memset(next[cur], 0, sizeof next[cur]);
	int p = last;
	//�غ�׺���Ӳ�ѯת���Ƿ����
	while (~p && !next[p][c]) {
		next[p][c] = cur;
		p = link[p];
	}
	//�ҵ���
	if (p == -1) {
		link[cur] = 0;
	}
	else {
		int q = next[p][c];
		//����Ҫ���ƽڵ�
		if (len[p] + 1 == len[q]) {
			link[cur] = q;
		}
		else {
			//���ƽڵ�q
			int clone = sz++;
			memcpy(next[clone], next[q], sizeof(int) * 26);
			len[clone] = len[p] + 1;
			firstpos[clone] = firstpos[q];
			link[clone] = link[q];
			link[cur] = link[q] = clone;
			//���½���ת�ƺͺ�׺����
			while (~p && next[p][c] == q) {
				next[p][c] = clone;
				p = link[p];
			}
		}
	}
	last = cur;
}


void SuffixTree::get_endpos() {
	//Ͱ���� �����ȴӴ�С
	int* tmp = new int[sz + 1];
	int* ind = new int[sz + 1];
	for (int i = 0; i < sz; ++i) ind[i] = tmp[i] = 0;
	for (int i = 1; i < sz; ++i) tmp[len[i]]++;
	for (int i = 1; i < sz; ++i) tmp[i] += tmp[i - 1];
	for (int i = 1; i < sz; ++i) ind[tmp[len[i]]--] = i;
	int cur = 0;
	int n = strlen(s);
	//Ҷ�ӽڵ��ʼ��Ϊ1
	for (int i = 0; i < n; ++i) {
		cur = next[cur][s[i] - 'a'];
		endpos[cur] = 1;
	}
	//����dp
	for (int i = sz - 1; i > 0; --i) {
		int cur = ind[i];
		if (~link[cur]) endpos[link[cur]] += endpos[cur];
	}

	delete[] tmp;
	delete[] ind;
}


int SuffixTree::_find(const char ptr[]) const {
	int n = strlen(ptr);
	int cur = 0;
	//��״̬ת��
	for (int i = 0; i < n; ++i) {
		if (next[cur][ptr[i] - 'a'])	cur = next[cur][ptr[i] - 'a'];
		else return -1;
	}
	return cur;
}


int SuffixTree::find(const char ptr[]) const {
	int cur = _find(ptr);
	if (~cur)	return firstpos[cur] - strlen(ptr) + 1;
	return -1;
}


int SuffixTree::count(const char ptr[]) const {
	int cur = _find(ptr);
	if (cur == -1)	return 0;
	return endpos[cur];
}


int SuffixTree::lcs(const char ptr[], char res[] = nullptr) const {
	int n = strlen(ptr);
	int cur = 0, l = 0, best = 0, bestpos = 0;
	for (int i = 0; i < n; ++i) {
		//��ǰ״̬������ptr[i]��ת��
		while (cur && !next[cur][ptr[i] - 'a']) {
			cur = link[cur];
			l = len[cur];
		}
		if (next[cur][ptr[i] - 'a']) {
			cur = next[cur][ptr[i] - 'a'];
			l++;
		}
		//���´�
		if (best < l) {
			best = l;
			bestpos = i;
		}
	}
	if (res)	memcpy(res, ptr + bestpos - best + 1, best);
	return best;
}


int SuffixTree::LongestRepetitiveSubstring(char res[]) const {
	//Ͱ���� �����ȴӴ�С
	int* tmp = new int[sz + 1];
	int* ind = new int[sz + 1];
	for (int i = 0; i < sz; ++i) ind[i] = tmp[i] = 0;
	for (int i = 1; i < sz; ++i) tmp[len[i]]++;
	for (int i = 1; i < sz; ++i) tmp[i] += tmp[i - 1];
	for (int i = 1; i < sz; ++i) ind[tmp[len[i]]--] = i;
	//�Ӵ�С�����ڵ�
	for (int i = sz - 1; i; --i) {
		int cur = ind[i];
		if (endpos[cur] > 1) {
			memcpy(res, s + firstpos[cur] - len[cur] + 1, len[cur]);
			return len[cur];
		}
	}
	return -1;
}