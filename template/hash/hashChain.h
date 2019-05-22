#ifndef hashChain_
#define hashChain_

#include "hash.h"
#include "dictionary.h"
#include <linearList/chain.h>
#include <utility>
#include <iostream>
#include <stdexcept>

using namespace std;

template<typename K, typename E>
class hashChain : public dictionary<K, E> {
public:
	hashChain(int _divisor = 11);
	~hashChain() { delete[] table; };

	bool empty() const { return dsize == 0; }
	int size() const { return dsize; }

	pair<const K, E>* find(const K&) const;

	void erase(const K&);
	void insert(const K&, const E&);

	void output(ostream&) const;
protected:
	chain<pair<const K, E> >* table;
	Hash<K> hash;
	int dsize;
	int divisor;
};

template<typename K, typename E>
hashChain<K, E>::hashChain(int _divisor) {
	if (_divisor < 1)	throw logic_error("the divisor must greater than 0.");

	divisor = _divisor;
	dsize = 0;

	table = new chain<pair<const K, E> >[divisor];
}

template<typename K, typename E>
pair<const K, E>* hashChain<K, E>::find(const K& key) const {
	int index = hash(key) % divisor;
	for (auto it = table[index].begin(); it != table[index].end(); ++it)
		if (it->first == key)
			return &*it;
	return nullptr;
}

template<typename K, typename E>
void hashChain<K, E>::erase(const K& key) {
	int index = hash(key) % divisor;
	int j = 0;
	for (auto it = table[index].begin(); it != table[index].end(); ++it)
	{
		if (it->first == key) {
			table[index].erase(j);
			dsize--;
			break;
		}
		j++;
	}
}

template<typename K, typename E>
void hashChain<K, E>::insert(const K& key, const E& value) {
	int index = hash(key) % divisor;
	int j = 0;
	for (auto it = table[index].begin(); it != table[index].end(); ++it) {
		if (it->first == key) {
			it->second = value;
			return;
		}
		if (it->first > key) {
			break;
		}
		j++;
	}
	dsize++;
	table[index].insert(j, make_pair(key, value));
}

template<typename K, typename E>
void hashChain<K, E>::output(ostream& out) const {
	for (int i = 0; i < divisor; ++i) {
		//cout << i << ": " << endl;
		out << "NO." << i << " bucket:";
		if (table[i].empty())	out << "NULL";
		else
			for (auto it = table[i].begin(); it != table[i].end(); ++it)
				out << it->first << ' ' << it->second << " | ";
		out << endl;
	}
}


#endif //hashChain_