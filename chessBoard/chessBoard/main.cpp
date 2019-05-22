#include <iostream>
#include <cassert>
using namespace std;
void dfs(int x, int y, int l, int px, int py, int** e) {
	if (l == 1) {
		bool vis[5] = { false };
		int dx[] = { 0, -1, 0, 1 };
		int dy[] = { 1, 0, -1, 0 };
		for (int i = x; i < x + (1 << l); ++i) {
			for (int j = y; j < y + (1 << l); ++j) {
				for (int k = 0; k < 4; ++k) {
					int tx = i + dx[k];
					int ty = j + dy[k];
					vis[e[tx][ty]] = true;
				}
			}
		}
		int col;
		for (col = 1; col <= 4 && vis[col]; ++col);
		for (int i = x; i < x + (1 << l); ++i) {
			for (int j = y; j < y + (1 << l); ++j) {
				if (i == px && j == py)	continue;
				e[i][j] = col;
			}
		}
		return;
	}
	int len = 1 << l;
	if (px < x + len / 2 && py < y + len / 2) {
		e[x + len / 2 - 1][y + len / 2] = 1;
		e[x + len / 2][y + len / 2 - 1] = 1;
		e[x + len / 2][y + len / 2] = 1;
		dfs(x, y, l - 1, px, py, e);
		dfs(x, y + len / 2, l - 1, x + len / 2 - 1, y + len / 2, e);
		dfs(x + len / 2, y, l - 1, x + len / 2, y + len / 2 - 1, e);
		dfs(x + len / 2, y + len / 2, l - 1, x + len / 2, y + len / 2, e);
	}
	else if (px < x + len / 2 && py >= y + len / 2) {
		e[x + len / 2 - 1][y + len / 2 - 1] = 1; 
		e[x + len / 2][y + len / 2 - 1] = 1;
		e[x + len / 2][y + len / 2] = 1;
		dfs(x, y, l - 1, x + len / 2 - 1, y + len / 2 - 1, e);
		dfs(x, y + len / 2, l - 1, px, py, e);
		dfs(x + len / 2, y, l - 1, x + len / 2, y + len / 2 - 1, e);
		dfs(x + len / 2, y + len / 2, l - 1, x + len / 2, y + len / 2, e);
	}
	else if (px >= x + (1 << (l - 1)) && py < y + (1 << (l - 1))) {
		e[x + len / 2 - 1][y + len / 2 - 1] = 1;
		e[x + len / 2 - 1][y + len / 2] = 1;
		e[x + len / 2][y + len / 2] = 1;
		dfs(x, y, l - 1, x + len / 2 - 1, y + len / 2 - 1, e);
		dfs(x, y + len / 2, l - 1, x + len / 2 - 1, y + len / 2, e);
		dfs(x + len / 2, y, l - 1, px, py, e);
		dfs(x + len / 2, y + len / 2, l - 1, x + len / 2, y + len / 2, e);
	}
	else {
		e[x + len / 2 - 1][y + len / 2 - 1] = 1;
		e[x + len / 2 - 1][y + len / 2] = 1;
		e[x + len / 2][y + len / 2 - 1] = 1;
		dfs(x, y, l - 1, x + len / 2 - 1, y + len / 2 - 1, e);
		dfs(x, y + len / 2, l - 1, x + len / 2 - 1, y + len / 2, e);
		dfs(x + len / 2, y, l - 1, x + len / 2, y + len / 2 - 1, e);
		dfs(x + len / 2, y + len / 2, l - 1, px, py, e);
	}
}
int main() {
	int k, len;
	int px, py;
	cin >> k;
	cin >> px >> py;
	len = 1 << k;
	assert(px > 0 && px <= len && py > 0 && py <= len);
	int** e = new int* [len + 2];
	for (int i = 0; i <= len + 1; ++i)	e[i] = new int[len + 2];
	for (int i = 0; i <= len + 1; ++i)
		for (int j = 0; j <= len + 1; ++j)
			e[i][j] = 0;
	dfs(1, 1, k, px, py, e);
	for (int i = 1; i <= len; ++i) {
		for (int j = 1; j <= len; ++j)
			cout << e[i][j] << ' ';
		cout << endl;
	}
	for (int i = 0; i <= len + 1; ++i)	delete[] e[i];
	delete[] e;
	return 0;
}