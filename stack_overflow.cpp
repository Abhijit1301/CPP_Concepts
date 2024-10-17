#include <iostream>
using namespace std;

int recurse(int b) {
    if (b == -5) return 100;
    recurse(--b);
}

int main() {
    cout<<"Hello World!" << endl;
    cout << recurse(10) << endl;
}
