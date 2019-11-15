#pragma once
#include <sstream>
#include "SuffixTreeNode.h"
class SuffixTree
{
protected:
	SuffixTreeNode* st;
	int last, sz;//��ǰ״̬��״̬��
	int MAX_SIZE;//���״̬��
	const char* s;


	void add(int); //ĩβ׷���ַ�
	void init(); //��׺����ʼ��
	void get_endpos(); //ͳ��endpos����
	int _find(const char[]) const;

	// �������ͼ
	struct edge { int to, next; } *e;
	int cnt, * head, *deg;
	void add_edge(int, int);
	void build(int, int);//��ӡ��

public:
	std::stringstream ssm;
	SuffixTree(const char[], const int = 26);
	SuffixTree(const SuffixTree&);
	~SuffixTree();
	int find(const char[]) const; //ģʽ��ƥ��
	int count(const char[]) const;//ģʽ��ͳ��
	int lcs(const char[], char[]) const;//������Ӵ�
	int LongestRepetitiveSubstring(char[]) const;//��ظ��Ӵ�
	int getSZ() const { return sz;  }
};

