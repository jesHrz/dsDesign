#include <iostream>
#include <algorithm>
#include "linearList/arrayList.h"
#include "queue/linkedQueue.h"

template<typename T = int>
class Arranger {
public:
	Arranger(int, const T*, const arrayList<int>*);
	~Arranger();

	bool solve(arrayList<int>&, T*, T*) const;
private:
	int n;
	T* t;
	arrayList<int>* e;
	void dfs(int);
};

template<typename T>
Arranger<T>::Arranger(int n, const T* p, const arrayList<int>* mp) : n(n) {
	t = new T[n + 2];
	for (int i = 1; i <= n; ++i)	t[i] = p[i];
	e = new arrayList<int>[n + 2];
	for (int i = 1; i <= n; ++i)	e[i] = mp[i];
}

template<typename T>
Arranger<T>::~Arranger() {
	delete[] t;
	delete[] e;
}


template<typename T>
bool Arranger<T>::solve(arrayList<int> & keyAction, T * start, T * end) const {
	int* in = new int[n + 2];
	t[0] = t[n + 1] = 0;
	for (int i = 0; i <= n + 1; ++i)	in[i] = start[i] = 0;
	for (int i = 1; i <= n; ++i)
		for (int j = 0; j < e[i].size(); ++j)
			in[e[i][j]]++;
	linkedQueue<int> q;
	for (int i = 1; i <= n; ++i) {
		if (!in[i]) {
			e[0].push_back(i);
			in[i]++;
		}
		if (e[i].size() == 0) {
			e[i].push_back(n + 1);
			in[n + 1]++;
		}
	}

	q.push(0);
	int cnt = 0;
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		cnt++;
		if (u == n + 1)	break;
		for (int i = 0; i < e[u].size(); ++i) {
			int v = e[u][i];
			start[v] = max(start[v], start[u] + t[u]);
			if (--in[v] == 0)	q.push(v);
		}
	}
	//cout << cnt << endl;
	if (cnt != n + 2)	return false;

	arrayList<int> * ee = new arrayList<int>[n + 2];

	for (int i = 0; i <= n + 1; ++i) 
		for (int j = 0; j < e[i].size(); ++j)
			ee[e[i][j]].push_back(i);
	
	for (int i = 0; i <= n + 1; ++i)	in[i] = 0;
	for (int i = 0; i <= n + 1; ++i)	end[i] = 0x3f3f3f3f;
	for (int i = 0; i <= n + 1; ++i) {
		for (int j = 0; j < ee[i].size(); ++j)
			in[ee[i][j]]++;
	}

	cnt = 0;
	q.push(n + 1);
	end[n + 1] = start[n + 1];
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		cnt++;
		if (u == 0)	break;
		for (int i = 0; i < ee[u].size(); ++i) {
			int v = ee[u][i];
			end[v] = min(end[v], end[u] - t[v]);
			if (--in[v] == 0)	q.push(v);
		}
	}

	for (int i = 1; i <= n; ++i)	if (start[i] == end[i])	keyAction.push_back(i);

	delete[] in;
	delete[] ee;
	return true;
}

int main() {
	int n, m;
	cin >> n >> m;
	int* t = new int[n + 2];
	int* start = new int[n + 2];
	int* end = new int[n + 2];
	arrayList<int> key;
	arrayList<int>* e = new arrayList<int>[n + 2];
	for (int i = 1; i <= n; ++i)	cin >> t[i];
	for (int i = 1; i <= m; ++i) {
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
	}
	Arranger<int> it(n, t, e);
	if (!it.solve(key, start, end)) {
		cout << "illegal arragement" << endl;
	}
	else {
		cout << "key action: " << endl;
		for (int i : key) {
			cout << i << ' ';
		}
		cout << endl << "earliest and latest: " << endl;
		for (int i = 1; i <= n; ++i) {
			cout << start[i] << ' ' << end[i] << endl;
		}
	}
	delete[] t;
	delete[] start;
	delete[] end;
	delete[] e;
	return 0;
}
/*
6 7
1 2 3 4 5 6
4 3
4 6
3 6
3 2
6 1
6 5
1 2

7 8
4 5 3 6 3 2 7
1 2
1 3
2 4
3 4
4 5
4 6
5 7
6 7

9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
5 7 9
5 8 7
8 9 4
7 9 2
4 6 2
6 8 4

*/