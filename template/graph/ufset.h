#ifndef ufset_
#define ufset_

class ufset {
protected:
	int* f;
	int n;
public:
	explicit ufset(int n) :n(n) {
		f = new int[n + 1];
		init();
	}
	~ufset() { delete[] f; }
	void init() {
		for (int i = 1; i <= n; ++i)	f[i] = i;
	}
	int find(int x) {
		return f[x] == x ? x : f[x] = find(f[x]);
	}
	bool unite(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y)	return false;
		f[y] = x;
		return true;
	}
};

#endif //ufset_