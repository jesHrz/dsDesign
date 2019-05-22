#ifndef adjacencyGraph_
#define adjacencyGraph_

#include <cstring>
#include <queue/linkedQueue.h>
#include <iostream>
#include "ufset.h"
using namespace std;

template<typename T>
class adjacencyGraph {
public:
	explicit adjacencyGraph(const int n, T MAX = 0x3fffffff) :n(n), MAX(MAX) {
		e = new T*[n + 1];
		for (auto i = 0; i <= n; ++i)	e[i] = new T[n + 1];
		for (auto i = 0; i <= n; ++i)
			for (auto j = 0; j <= n; ++j) {
				if (i == j)	e[i][j] = 0;
				else e[i][j] = MAX;
			}
		g = new T*[n + 1];
		for (auto i = 0; i <= n; ++i)	g[i] = new T[n + 1];
		vis = new bool[n + 1];
		for (auto i = 0; i <= n; ++i)	vis[i] = false;
		changed = true;
		m = 0;
	}
	~adjacencyGraph() {
		for (auto i = 0; i <= n; ++i)	delete[] e[i];
		for (auto i = 0; i <= n; ++i)	delete[] g[i];
		delete[] e;
		delete[] g;
		delete[] vis;
	};
	void add(int u, int v, const T w) {
		changed = true;
		e[u][v] = w;
		++m;
	}
	void erase(int u, int v) {
		changed = true;
		e[u][v] = MAX;
		--m;
	}
	void bfs(int s) {
		linkedQueue<int> q;
		vis[s] = true;
		q.push(s);
		while (!q.empty()) {
			auto u = q.front(); q.pop();
			cout << u << ' ';
			for (auto i = 1; i <= n; ++i)
				if (!vis[i] && e[u][i] < MAX) {
					q.push(i);
					vis[i] = true;
				}
		}
		cout << endl;
	}
	void dfs(int u) {
		cout << u << ' ';
		vis[u] = true;
		for (auto i = 1; i <= n; ++i)
			if (!vis[i] && e[u][i] < MAX)
				dfs(i);
	}
	int connectedComponent(bool method = false) {
		for (auto i = 1; i <= n; ++i)	vis[i] = false;
		auto tot = 0;
		for (auto i = 1; i <= n; ++i) {
			if (vis[i])	continue;
			++tot;
			if (method) {
				this->dfs(i);
				cout << endl;
			}
			else this->bfs(i);
		}
		return tot;
	}
	int dis(int u, int v) {
		if (changed)	floyd();
		return g[u][v] >= MAX ? -1 : g[u][v];
	}
	int kru() const {
		struct edge {
			int u, v;
			T w;
			bool operator<(const edge& x) const { return w < x.w; }
		}*ee;
		int cnt = 0;
		ee = new edge[m];
		for (int i = 1; i <= n; ++i)
			for (int j = 1; j <= n; ++j)
				if (i != j && e[i][j] < MAX)
					ee[cnt++] = { i, j, e[i][j] };
		std::sort(ee, ee + cnt);
		ufset f(n);
		int tot = 0;
		int sum = 0;
		for (int i = 0; i < cnt; ++i) {
			int u = ee[i].u;
			int v = ee[i].v;
			if (f.unite(u, v)) {
				sum += ee[i].w;
				cout << u << "<->" << v << " " << ee[i].w << endl;
				if (++tot >= n)	break;
			}
		}
		delete[] ee;
		return sum;
	}
	int prim(int s) const {
		T* dis = new T[n + 1];
		int* path = new int[n + 1];
		for (auto i = 1; i <= n; ++i)	dis[i] = (T)0x6f6f6f6f;
		for (auto i = 1; i <= n; ++i)	vis[i] = false;
		for (auto i = 1; i <= n; ++i) {
			if (e[s][i] < MAX && i != s) {
				dis[i] = e[s][i];
				path[i] = s;
			}
		}
		vis[s] = true;
		int sum = 0;
		for (int i = 1; i < n; ++i) {
			int MIN = MAX;
			int u = -1;
			for (int j = 1; j <= n; ++j) {
				if (!vis[j] && dis[j] < MIN) {
					MIN = dis[j];
					u = j;
				}
			}
			if (u == -1)	return -1;
			vis[u] = true;
			cout << path[u] << "<->" << u << " " << dis[u] << endl;
			sum += dis[u];
			for (auto v = 1; v <= n; ++v) {
				if (!vis[v] && dis[v] > e[u][v]) {
					dis[v] = e[u][v];
					path[v] = u;
				}
			}
		}
		delete[] dis;
		delete[] path;
		return sum;
	}
protected:
	T** e;
	T** g;
	bool* vis;
	bool changed;
	int n;
	int m;
	T MAX;
	void floyd() {
		for (auto i = 1; i <= n; ++i)
			for (auto j = 1; j <= n; ++j)
				g[i][j] = e[i][j];
		for (auto k = 1; k <= n; ++k)
			for (auto i = 1; i <= n; ++i)
				for (auto j = 1; j <= n; ++j)
					g[i][j] = (g[i][j] < g[i][k] + g[k][j] ? g[i][j] : g[i][k] + g[k][j]);
		changed = false;
	}
};

#endif //adjacencyGrap_