#include <iostream>
#include <vector>
#include "../utils/random_array_generator.h"


int main() {
	try {
		std::vector<int> arr = get_random_int_vector(20, 40, 50);
		for(int elem: arr) std::cout << elem << " ";
		std::cout << std::endl;
	} catch (std::string exp) {
		std::cout << "exception caught: " << exp << std::endl;
		return 1;
	}
	return 0;
}