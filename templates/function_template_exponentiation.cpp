#include <iostream>

template<int n>
int power(int m) {
	return m * power<n - 1>(m);
}

template<>
int power<0>(int m) {
	return 1;
}

int main() {
	std::cout << "2 to the power 10 = " << power<10>(2) << std::endl;
}