#include <iostream>
using namespace std;

class base {
    public:
        int a;
        base(int val): a{val} {};
};

class derived: base {
    public:
        int b;
        derived(int val1, int val2): base(val1), b{val2}{};
};

void test(base* b) {
    cout << "b->a = " << b->a << endl;
}

int main() {
    cout<<"Hello World!";
    derived* d = new derived{5,6};
    test(d); // error...
}