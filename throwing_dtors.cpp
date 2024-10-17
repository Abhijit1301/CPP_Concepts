#include <iostream>
using namespace std;

class A {
public:
  A() { cout << "A's constructor" << endl;}
  ~A() { cout << "A's destructor." << endl; throw "A's exception";}
};

class B {
public:
  B() { cout << "B's constructor" << endl;}
  ~B() { cout << "B's destructor." << endl; throw "B's exception";}
};

int main() {
  
  try {
    A a;
    B b;
	throw "from MAIN.....";
  } catch(const char* exception) {
    cout << "exception caught. message: " << exception << endl;
  }
  cout << "resume main" << endl;
}