#include <iostream>
#include "skipList.h"
#include <cstdlib>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

using namespace std;

void display() {
	std::cout << "======================================" << std::endl;
	std::cout << "||        1. insert key value       ||" << std::endl;
	std::cout << "||        2. find key               ||" << std::endl;
	std::cout << "||        3. erase key              ||" << std::endl;
	std::cout << "||        4. erase maxKey           ||" << std::endl;
	std::cout << "||        5. erase minKey           ||" << std::endl;
	std::cout << "||        6. display                ||" << std::endl;
	std::cout << "======================================" << std::endl;
	return;
}

int main() {
	srand(time(0));
	skipList<int, int> sl(-100000000, 100000000, 100000, 0.7);
	std::pair<const int, int>* res;

	display();
	while (true) {
		int op, key, value;
		std::cin >> op;
		switch (op) {
		case 1:
			std::cin >> key >> value;
			sl.insert(key, value);
			break;
		case 2:
			std::cin >> key;
			res = sl.find(key);
			if (res != nullptr)	std::cout << "(" << res->first << ", " << res->second << ")" << std::endl;
			else std::cout << "No such element" << std::endl;
			break;
		case 3:
			std::cin >> key;
			sl.erase(key);
			std::cout << "ok" << std::endl;
			break;
		case 4:
			sl.eraseMaxKey();
			std::cout << "ok" << std::endl;
			break;
		case 5:
			sl.eraseMinKey();
			std::cout << "ok" << std::endl;
			break;
		case 6:
			sl.output();
			break;
		default:
			return 0;
		}
	}

	return 0;
}