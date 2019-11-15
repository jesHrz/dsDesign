#ifndef linkedGraph_
#define linkedGraph_

#include <linearList/chain.h>
#include <queue/linkedQueue.h>
#include <tree/Heap.h>
#include <algorithm>
#include <iostream>
#include "ufset.h"
using namespace std;

template<typename T>
class linkedGraph {
	typedef pair<int, T> p;
protected:
	chain<p>* e;
	bool* vis;
	int n;
	int m;
public:
	explicit linkedGraph(const int n) :n(n) {
		e = new chain<p>[n + 1];
		vis = new bool[n + 1];
		m = 0;
	}
	~linkedGraph() {
		delete[] e;
		delete[] vis;
	}

	void add(int u, int v, const T& w) {
		e[u].push_back(make_pair(v, w));
		++m;
	}
	void erase(int u, int v) {
		auto i = 0;
		for (auto it = e[u].begin(); it != e[u].end() && it->first != v; ++it, ++i);
		e[u].erase(i);
		--m;
	}
	void bfs(int s) {
		linkedQueue<int> q;
		vis[s] = true;
		q.push(s);
		while (!q.empty()) {
			auto u = q.front(); q.pop();
			cout << u << ' ';
			for (auto it = e[u].begin(); it != e[u].end(); ++it) {
				auto v = it->first;
				if (!vis[v]) {
					q.push(v);
					vis[v] = true;
				}
			}
		}
		cout << endl;
	}
	void dfs(int u) {
		cout << u << ' ';
		vis[u] = true;
		for (auto it = e[u].begin(); it != e[u].end(); ++it) {
			auto v = it->first;
			if (!vis[v])
				dfs(v);
		};
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
	int dis(int s, int t) const {
		T* dis = new T[n + 1];
		for (auto i = 1; i <= n; ++i)	dis[i] = 0x6f6f6f6f;
		struct dh {
			int u;
			T d;
			bool operator<(const dh& x) const { return d < x.d; }
		};
		Heap<dh, less<>> q;
		dis[s] = 0;
		q.push({ s, 0 });
		while (!q.empty()) {
			dh uu = q.top(); q.pop();
			int u = uu.u;
			if (dis[u] < uu.d)	continue;
			for (auto it = e[u].begin(); it != e[u].end(); ++it) {
				int v = it->first;
				T& w = it->second;
				if (dis[v] > dis[u] + w) {
					dis[v] = dis[u] + w;
					q.push({ v, dis[v] });
				}
			}
		}
		auto ans = dis[t];
		delete[] dis;
		return ans;
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
			for (auto it = e[i].begin(); it != e[i].end(); ++it)
				ee[cnt++] = { i, it->first, it->second };
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
		return tot == n - 1 ? sum : -1;
	}
	int prim(int s) const {
		T* dis = new T[n + 1];
		int* path = new int[n + 1];
		for (auto i = 1; i <= n; ++i)	dis[i] = (T)0x6f6f6f6f;
		for (auto i = 1; i <= n; ++i)	vis[i] = false;
		for (auto it = e[s].begin(); it != e[s].end(); ++it) {
			int v = it->first;
			T w = it->second;
			dis[v] = w;
			path[v] = s;
		}
		vis[s] = true;
		int sum = 0;
		for (int i = 1; i < n; ++i) {
			int MIN = 0x6f6f6f6f;
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
			for (auto it = e[u].begin(); it != e[u].end(); ++it) {
				int v = it->first;
				T w = it->second;
				if (!vis[v] && dis[v] > w) {
					dis[v] = w;
					path[v] = u;
				}
			}
		}
		delete[] dis;
		delete[] path;
		return sum;
	}
};

#endif //linkedGraph_