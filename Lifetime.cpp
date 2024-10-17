#include <iostream>
using namespace std;

char* getcharr() {
// void getcharr() {
    char arr[11];
    for (int i = 0; i < 10; i++)
    {
        if (i%2) arr[i] = 'o';
        else arr[i] = 'e';
    }
    arr[10] = 0;
    // cout << arr << endl;
    return arr;
}

int main() {
    cout<<"Hello World!";
    // getcharr();
    const char* arr = getcharr();
    cout << arr << endl;
}
