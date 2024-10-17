#include <iostream>

class Base{
protected:
	int ba;
	double bb;
public:
	explicit Base(int a, double b) : ba(a), bb(b) {
		std::cout << "base class ctr: a = " << a << " and b = " << b << std::endl;
	}
};

class Derived: public Base {
	using Base::Base;
	int da;
	double db;
public:
	explicit Derived(std::string str): Base{77, 88.99}, da{44}, db{55.99} {
		std::cout << "Derived class ctr: str = " << str << std::endl;
	}

	double add() { return ba + bb; }
	double addDerived() { return da + db; }
};

int main() {
	Derived d1{"Hello World!"};
	std::cout << "type id of d1 = " << typeid(d1).name() << std::endl;
	std::cout << "d1.add() = " << d1.add() << " d1.addDerived() = " << d1.addDerived() << std::endl;
	Derived d2{55, 67.0};
	std::cout << "type id of d2 = " << typeid(d2).name() << std::endl;
	std::cout << "d2.add() = " << d2.add() << " d2.addDerived() = " << d2.addDerived() << std::endl;

	return 0;
}