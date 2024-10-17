#include <iostream>
#include <vector>

template <typename T>
T arraySum(T begin, T end) {
	T::value_type prev = T::value_type{};
	std::cout << "prev = " << prev << std::endl;
	while (begin < end) {
		*begin += prev;
		prev = *begin;
		++begin;
	}
	return begin - 1;
}

template <typename T>
T* arraySum(T* begin, T* end) {
	T prev = T{};
	while (begin < end) {
		*begin += prev;
		prev = *begin;
		++begin;
	}
	return begin-1;
}

int main() {
	std::vector<int> vec = {1,2,3,4,5,6};
	int arr[] = {1,2,3,4,5,6};

	arraySum(vec.begin(), vec.end());
	arraySum(arr, arr+6);

	for (int index = 0; index < vec.size(); ++index) std::cout << vec[index] << " ";
	std::cout << std::endl;
	for (int index = 0; index < sizeof(arr)/sizeof(int); ++index) std::cout << arr[index] << " ";
}