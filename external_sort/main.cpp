#include <iostream>
#include <string>
#include "externalSorter.h"

using namespace std;

int main() {
	int n;
	string input, output;
	cout << "Please input the name of inputFile, the name of outputFile and the number of elements, splited by space:" << endl;
	cin >> input >> output >> n;

	externalSorter<int> sorter(input.c_str(), output.c_str(), n);
	if (sorter.sort())	cout << "success" << endl;
	else cout << "failed" << endl;

	return 0;
}