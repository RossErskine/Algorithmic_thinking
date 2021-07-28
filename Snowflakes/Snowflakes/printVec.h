#include <vector>
#include <iostream>

void printVector(std::vector<std::vector<int>> vec) {
	for (int i = 0; i != vec.size(); i++) {
		for (int j = 0; j != vec[i].size(); j++) {
			std::cout << vec[i][j] << '\t';
		}
		std::cout << '\n';
	}
}
