#include <iostream>

template<int n, int m>
struct exponentiation_compile_time
{
	static const int value = n * exponentiation_compile_time<n, m-1>::value;
};

template<int n>
struct exponentiation_compile_time<n,0>
{
	static const int value = 1;
};

int main()
{
	std::cout << "2 ^ 10 = " << exponentiation_compile_time<2, 10>::value << std::endl;
}
