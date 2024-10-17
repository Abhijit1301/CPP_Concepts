#include <iostream>
using namespace std;

class A{
	int a;
	int *p;
public:
	explicit A(int val);
	void alter(int newVal) const;
	int getA() { return a; }
};

A::A(int val): a{val}, p(&a) {};
void A::alter(int newVal) const {
	// a = newVal; // error
	*p = newVal; // not an error
}

int main() {
	A a(35);
	cout << "before::::\n";
	cout << a.getA();
	a.alter(99);
	cout << "\nAfter::::\n";
	cout << a.getA() << endl;
}