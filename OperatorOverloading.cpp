#include <iostream>
#include <vector>
using namespace std;

struct test{
	int a;
};

int operator+(test a, int b) {
	return a.a - b;
}

size_t operatorsizeof(test t) {
	return sizeof(t);
}

// overload resolution of operators
//
class X {
public:
	void operator+(int) { cout << "This is operator+(int)" << endl; }
	// explicit X(int) {}; // Now 1+a will not work
	X(int) {};
};
void operator+(X a,X b) { cout << "This is operator+(X,X)" << endl; }
void operator+(X,double) { cout << "This is operator+(X,double)" << endl; }
void f(X a)
{
	a+1; // a.operator+(1)
	1+a; // ::operator+(X(1),a)
	a+1.0; // ::operator+(a,1.0)
}
// [end] overload resolution of operators
//

// subscript operator overloading
//
struct Assoc {
	vector<pair<string,int>> vec; // vector of {name,value} pairs
	const int& operator[] (const string&) const;
	int& operator[](const string&);
};

int& Assoc::operator[](const string& s)
// search for s; return a reference to its value if found;
// otherwise, make a new pair {s,0} and return a reference to its value
{
	for (auto x : vec)
		if (s == x.first) return x.second;
			vec.push_back({s,0}); // initial value: 0
	return vec.back().second; // return last element (§31.2.2)
}
// [end] subscript operator overloading
//

// Dereferencing test
//
void dereference() {
	test* t1 = new test{23};
	cout << "t1->a = " << t1->a << " (*t1).a = " << (*t1).a << "\n... '.' has higher precedence than '*'...\n";
	cout << "t1[0].a = " << t1[0].a << " hmmm... let's see, t1[1].a = " << t1[1].a << endl;

	// This will crash if i is sufficiently large
	for (int i = 0; i < 10; i++) {
		cout << "t1[" << i << "] = " << t1[i].a << "...   ";
	}
	for (int i = 0; i < 10; i++) {
		cout << "t1[0-" << i << "] = " << t1[0-i].a << "...   ";
	}
	cout << endl;
}
// [end] Dereferencing test
//

// prevent new operator
//
struct dummy{
	void* operator new(size_t count) = delete;
	int a;
	int b;
};

void deletedNew() {
	dummy d1{1,2};
	// dummy* d2 = new dummy{3,4};
}
// [end] prevent new operator
//

int main() {
	cout << test{17} + 6 << endl;
	cout << 45 + 55 << endl;

	// overload resolution of operators
	f(X{44});

	// subscript operator overloading
	// Assoc values;
	// string buf;
	// while (cin>>buf && buf != "9") ++values[buf];
	// for (auto x : values.vec) cout << '{' << x.first << ',' << x.second << "}\n";
	// cout << endl;

	dereference();
	cout << "Done................" << endl;
}