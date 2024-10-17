#include <iostream>
using namespace std;
int main() {
    cout<<"Hello World!";
    char x = 20;
    char* ptr = &x;
    while (1) {
        cout << *ptr << " ";
		ptr -= 1000;
    }
	return 0;
}