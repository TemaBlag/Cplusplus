#include <iostream>
#include <vector>

void fuck() {
	if (true) {
		std::cout << "FUCK THE KING";
		return;
	}
	std::cout << "you are gay";
}

int main() {
	fuck();
	std::vector<int> matveev{1, 2, 3, 4};
	for (int i = 0; i <= matveev.size(); ++i) {
		std::cout << matveev[i];

	}
	return 0;
}