#include <iostream>
using namespace std;

int main() {
	int* num = nullptr;
	cout << num  << "\n typeid(num) = " << typeid(num) << endl;
	delete num;
}