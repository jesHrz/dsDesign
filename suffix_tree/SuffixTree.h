#pragma once
#include <sstream>
#include "SuffixTreeNode.h"
class SuffixTree
{
protected:
	SuffixTreeNode* st;
	int last, sz;//当前状态、状态数
	int MAX_SIZE;//最大状态数
	const char* s;


	void add(int); //末尾追加字符
	void init(); //后缀树初始化
	void get_endpos(); //统计endpos集合
	int _find(const char[]) const;

	// 存放树形图
	struct edge { int to, next; } *e;
	int cnt, * head, *deg;
	void add_edge(int, int);
	void build(int, int);//打印树

public:
	std::stringstream ssm;
	SuffixTree(const char[], const int = 26);
	SuffixTree(const SuffixTree&);
	~SuffixTree();
	int find(const char[]) const; //模式串匹配
	int count(const char[]) const;//模式串统计
	int lcs(const char[], char[]) const;//最长公共子串
	int LongestRepetitiveSubstring(char[]) const;//最长重复子串
	int getSZ() const { return sz;  }
};

