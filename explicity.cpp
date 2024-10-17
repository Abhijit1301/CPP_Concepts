#include <iostream>
#include <initializer_list>

using namespace std;

struct A {
	int a;
	double b;
	// explicit A(int val): a{val}, b{78.98} {
	A(int val): a{val}, b{78.98} {
		cout << "Constructor... A(int val). a = " << a << " b = " << b << endl;
	}

	// try to toggle the constructor declaration and see the magic :P
	// explicit A(initializer_list<double> list) {
	A(initializer_list<double> list) {
		if (list.size() >= 2) {
			a = list.begin()[0];
			b = list.begin()[1];
		} else if (list.size() == 1) {
			a = list.begin()[0];
			b = -1.75;
		} else {
			a = -34;
			b = -55.83;
		}
		cout << "Constructor... A(initializer_list<double> list). a = " << a << " b = " << b << endl;
	}
	// explicit A(double val): a{-77}, b{val} {
	A(double val): a{-77}, b{val} {
		cout << "Constructor... A(double val). a = " << a << " b = " << b << endl;
	}
};

int main() {
	A a1 = 45.6789;
	A a2 = 13;
	A a3 = {45};
	A a4 = {34, 66};
	A a5 = {};

	return 0;
}