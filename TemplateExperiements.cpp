#include <iostream>

// Tests if we can pass a const type to a template parameter...
template <typename T>
void printme(T val) {
	std::cout << "my val = " << val << " & my type = " << typeid(T).name() << 
	" is constant? " << std::is_const<T>::value << std::endl;
	T val2 = val;
	val2 = val2 + 2 * val;
}

int main() {
	const int v1 = 455;
	int v2 = 554;
	printme(v1);
	printme(v2);
	printme<const int>(345);
	printme<int>(4566);
	std::cout << "type of const variable = " << typeid(v1).name() << std::endl;
}