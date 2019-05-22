#pragma once
class SuffixTree
{
protected:
	int** next, * link, * len, * endpos, * firstpos;
	int last, sz;//��ǰ״̬��״̬��
	int MAX_SIZE;//���״̬��
	const char* s;

	void add(int); //ĩβ׷���ַ�
	void init(); //��׺����ʼ��
	void get_endpos(); //ͳ��endpos����
	int _find(const char[]) const;
public:
	SuffixTree(const char[]);
	SuffixTree(const SuffixTree&);
	~SuffixTree();
	int find(const char[]) const; //ģʽ��ƥ��
	int count(const char[]) const;//ģʽ��ͳ��
	int lcs(const char[], char[]) const;//������Ӵ�
	int LongestRepetitiveSubstring(char[]) const;//��ظ��Ӵ�
};

