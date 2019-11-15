#ifndef _playerNode
#define _playerNode

template<typename T>
struct playerNode {
	int id;
	T key;
	bool operator <= (const playerNode& A) const {
		if (id != A.id) return id <= A.id;
		return key <= A.key;
	}
};

#endif