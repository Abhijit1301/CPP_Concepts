#include <vector>
#include <iostream>
#include <exception>
#include <limits>
#include <thread>

int main() {
	try {
		std::vector<long long int> v;
		long long int lli = std::numeric_limits<long long int>::min();
		while (1) {
			v.push_back(lli++);
			if (lli % 100000000 == 0) std::this_thread::sleep_for(500ms);
		}
	} catch (exception e) {
		std::cout << "Exception occurred: " << e.what();
	} 
}