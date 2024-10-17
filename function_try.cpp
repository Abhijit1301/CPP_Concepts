#include <iostream>

class A {
public:
	A() {
	    std::cout << " A's ctor...." << std::endl;
		throw 5;
	}
	~A() {
	    std::cout << " A's dtor..." << std::endl;
// 		throw 7;
	}
};

class B {
public:
	B() {
		std::cout << "B's ctor..." << std::endl;
		throw 88;
	}
	~B() {
	    std::cout << "B's dtor...." << std::endl;
// 		throw 9;
	}
};

class C {
	A a;
	B b;
public:
	C() try: a{A{}}, b{B{}} {
		std::cout << "C's ctor..." << std::endl;
	} catch(int excp) {
	    std::cout << "exception caught in C's function try block.... = " << excp << std::endl;
	    throw 99;
	}
// 	~C() {
// 		std::cout << "C's dtor..." << std::endl;
// 	}
	~C()
	try {
		std::cout << "C's dtor... function" << std::endl;
	} catch (int excp) {
		std::cout << "caught exception in C's dtor... = " << excp << std::endl;
	}
};

int main() {
	try {
		C c;
	} catch(int excp) {
		std::cout << "exception caught in MAIN... : " << excp << std::endl;
	}
	std::cout << "resuming main..." << std::endl;
}