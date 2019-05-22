#ifndef hashTable_
#define hashTable_

#include "dictionary.h"
#include "hash.h"
#include <stdexcept>


template<typename K, typename E>
class hashTable :public dictionary<K, E> {
public:
	hashTable(int = 10);
	~hashTable() {
		for (int i = 0; i < divisor; ++i)	delete table[i];
		delete[] table;
	}

	bool empty() const { return dsize == 0; };
	int size() const { return dsize; };

	pair<const K, E>* find(const K&) const;

	void erase(const K&);
	void insert(const K&, const E&);

	void output(ostream&) const;

protected:
	Hash<K> hash;
	pair<const K, E>** table;
	int divisor;
	int dsize;
};

template<typename K, typename E>
hashTable<K, E>::hashTable(int _divisor) {
	if (_divisor < 1)	throw logic_error("the divisor must greater than 0.");
	divisor = _divisor;
	dsize = 0;
	table = new pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; ++i)	table[i] = nullptr;
}

template<typename K, typename E>
pair<const K, E>* hashTable<K, E>::find(const K& key) const {
	int o = hash(key) % divisor;
	int i = o;
	while (true) {
		if (table[i] == nullptr)	return nullptr;
		else if (table[i]->first == key) return table[i];
		i = (i + 1) % divisor;
		if (i == o)	break;
	}
	return nullptr;
}

template<typename K, typename E>
void hashTable<K, E>::erase(const K& key) {
	int o = hash(key) % divisor;
	int i = o;
	bool find = false;
	while (true) {
		if (table[i] == nullptr)	break;
		else if (table[i]->first == key) {
			find = true;
			delete table[i];
			table[i] = nullptr;
			dsize--;
			break;
		}
		i = (i + 1) % divisor;
		if (i == o)	break;
	}
	if (find) {
		o = i;
		int Next = (i + 1) % divisor;
		while (Next != o && table[Next] != nullptr) {
			int ash = hash(table[Next]->first) % divisor;
			if (Next > i) {
				if (ash > Next || ash <= i)
				{
					pair<const K, E>* tmp = table[Next];
					table[Next] = table[i];
					table[i] = tmp;
					i = Next;
				}
			}
			else {
				if (ash > Next && ash <= i)
				{
					pair<const K, E>* tmp = table[Next];
					table[Next] = table[i];
					table[i] = tmp;
					i = Next;
				}
			}
			Next = (Next + 1) % divisor;
		}
	}
}

template<typename K, typename E>
void hashTable<K, E>::insert(const K& key, const E& value) {
	int o = hash(key) % divisor;
	int i = o;
	while (true) {
		if (table[i] == nullptr) {
			table[i] = new pair<const K, E>(key, value);
			dsize++;
			return;
		}
		else if (table[i]->first == key) {
			table[i]->second = value;
			return;
		}
		i = (i + 1) % divisor;
		if (i == o)	throw overflow_error("dicitionary is full");
	}
}

template<typename K, typename E>
void hashTable<K, E>::output(ostream& out) const {
	for (int i = 0; i < divisor; ++i) {
		out << "NO." << i << " bucket:";
		if (table[i] == nullptr)	out << "NULL" << endl;
		else out << table[i]->first << ' ' << table[i]->second << endl;
	}
}

#endif //hashTable_