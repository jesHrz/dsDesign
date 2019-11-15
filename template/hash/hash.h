#ifndef hash_
#define hash_

#include <string>
#include <iostream>
using namespace std;

template<typename T>	class Hash;

template<>
class Hash<string> {
public:
	size_t operator()(const string key) const {
		unsigned long long value = 0;
		int n = key.length();
		for (int i = 0; i < n; ++i)
			value = value * 128 + key.at(i);
		return size_t(value);
	}
};

template<>
class Hash<int> {
public:
	size_t operator() (const int key) const {
		return size_t(key);
	}
};

template<>
class Hash<short> {
public:
	size_t operator() (const short key) const {
		return size_t(key);
	}
};

template<>
class Hash<long> {
public:
	size_t operator() (const long key) const {
		return size_t(key);
	}
};

template<>
class Hash<long long> {
public:
	size_t operator() (const long long key) const {
		return size_t(key);
	}
};

#endif //hash_