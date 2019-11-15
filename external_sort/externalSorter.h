#ifndef _externalSorter
#define _externalSOrter

#include <fstream>
#include <algorithm>
#include <stdexcept>
#include "minWinnerTree.h"
#include "playerNode.h"

#define ROOM 10

template<typename T>
class externalSorter {
public:
	externalSorter(const char* inputFile, const char* outputFile, int n) : inputFile(inputFile), outputFile(outputFile), n(n) { cnt = new int[n + 1]; }
	~externalSorter() { delete[] cnt; }
	bool sort() {
		try {
			run();
			KwayMerge();
			for (int i = 1; i <= maxID; ++i)	remove((to_string(i) + ".tmp").c_str());
		} catch (exception) {
			return false;
		}
		return true;
	};
protected:
	void run();
	void KwayMerge();
	const char* inputFile, * outputFile;
	int n;
	int maxID;
	int* cnt;
};

template<typename T>
void externalSorter<T>::run() {
	playerNode<int>* player = new playerNode<T>[ROOM + 1];
	ifstream fin(inputFile);

	int driver = 0;
	for (int i = 1; i <= ROOM; ++i) {
		fin >> player[i].key;
		driver++;
		player[i].id = 1;
	}

	minWinnerTree<playerNode<T>> winnerTree(player, ROOM);
	maxID = 0;
	for (int i = 1; i <= n; ++i)	cnt[i] = 0;
	for (int i = ROOM + 1; i <= n; ++i) {
		int winner = winnerTree.winner();
		int winnerID = player[winner].id;

		cnt[winnerID]++;
		if (maxID < winnerID)	maxID = winnerID;

		string fileName = to_string(winnerID) + ".tmp";
		ofstream fout(fileName.c_str(), ios::app);
		if (cnt[winnerID] > 1)	fout << ' ';
		fout << player[winner].key;
		fout.close();

		int key;
		fin >> key;
		if (key < player[winner].key) player[winner].id += 1;
		player[winner].key = key;
		winnerTree.replay(winner);
		driver += 2;
	}
	for (int i = 1; i <= ROOM; ++i) {
		int winner = winnerTree.winner();
		int winnerID = player[winner].id;

		cnt[winnerID]++;
		if (maxID < winnerID)	maxID = winnerID;

		string fileName = to_string(winnerID) + ".tmp";
		ofstream fout(fileName.c_str(), ios::app);
		if (cnt[winnerID] > 1)	fout << ' ';
		fout << player[winner].key;
		fout.close();

		player[winner].key = 0;
		player[winner].id = n + 1;
		winnerTree.replay(winner);

		driver += 1;
	}
	fin.close();
	delete[] player;
	cout << "run: " << driver << endl;
}

template<typename T>
void externalSorter<T>::KwayMerge() {
	int div = ROOM / maxID;
	int mod = ROOM % maxID;
	playerNode<int>* player = new playerNode<int>[ROOM + 1];
	ifstream* _fin = new ifstream[maxID + 1];

	for (int i = 1; i <= maxID; ++i)	cnt[i] = min(cnt[i], div + (i <= mod ? 1 : 0));
	for (int i = 1; i <= maxID; ++i)	_fin[i] = ifstream(to_string(i) + ".tmp");
	for (int i = 1; i <= ROOM; ++i)	player[i].id = 2;

	int sum = 0;
	int driver = 0;
	int* belong = new int[n + 1];
	for (int i = 1; i <= maxID; ++i) {
		for (int j = 1; j <= cnt[i]; ++j) {
			_fin[i] >> player[sum + j].key;
			driver++;
			player[sum + j].id = 1;
			belong[sum + j] = i;
		}
		sum += cnt[i];
	}
	minWinnerTree<playerNode<int> > winnerTree(player, ROOM);

	ofstream fout(outputFile);
	for (int i = 1; i <= n; ++i) {
		int winner = winnerTree.winner();
		int winnerID = belong[winner];
		fout << player[winner].key << ' ';
		driver++;

		if (_fin[winnerID].peek() != EOF) {
			_fin[winnerID] >> player[winner].key;
			driver++;
		} else player[winner].id = 2;

		winnerTree.replay(winner);
	}
	fout.close();
	delete[] belong;
	delete[] player;
	delete[] _fin;
	cout << "k-way merge: " << driver << endl;
}

#endif