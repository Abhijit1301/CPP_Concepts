#include <iostream>
#include <vector>
#include <cstdlib>
#include "random_array_generator.h"

std::vector<int> get_random_int_vector(int size, int offset, int limit) {
	std::cout << "size = " << size << " offset = " << offset << " limit = " << limit << std::endl;

	if (2 * offset >= limit) throw(std::string{"offset must be less than half of limit"});
	if (size <= 0) throw(std::string{"Size must be greater than 0..."});
	if (size > 1000000) throw(std::string{"Maximum size can be 1 Million only..."});
	std::vector<int> randomIntegers(size);
	for (int i = 0; i < size; i++) {
		randomIntegers[i] = (rand() % limit) + offset;
	}
	return randomIntegers;
}