#include <iostream>
#include <cstdarg>
#include <complex>
#include <chrono>
#include <thread>

using namespace std;

// void print_all_args(...) { //This is invalid until c23, prior to c23, the ellipsis must follow a named parameter and must be delimited by ','
void print_all_args(const char* msg, ...) {
    cout << msg << endl;
    va_list args;
    va_start(args, msg);
    int arg;
    while (arg = va_arg(args, bool) != NULL) {
        cout << arg << endl;
    }
    va_end(args);
}

void EBCDIC_test_aix() {
    char c = 'a';
    for (int i = 0; i < 26; i++) {
        printf("%c ", (char)(c + i));
    }
    printf("\n");
}

void print_all_remaining_digits_from(char c) {
    while ( c <= '9') {
        cout << c++ << " ";
    }
    cout << endl;
}

void print_next_10_chars(char c) {
    for (int i = 0; i < 10; i++) {
        cout << c + i << " ";
    }
    cout << endl;
}

void test_pointer_conversions() {
    bool b {true};
    char c {'a'};
    signed char sc {'s'};
    unsigned char uc {'u'};
    char16_t c16 {'w'};
    char32_t c32 {'z'};
    int i {77777};
    short int si {9999};
    long long int li {9999999999};
    float f {2.35};
    double d {1999.995};

    bool* bp = &b;
    char* cp = &c;
    signed char* scp = &sc;
    unsigned char* ucp = &uc;
    char16_t* c16p = &c16;
    char32_t* c32p = &c32;
    int* ip = &i;
    short int* sip = &si;
    long long int* lip = &li;
    float* fp = &f;
    double* dp = &d;

    cout << "dereferenced pointers:\n b = " << *bp << " c = " << * cp << " sc = " << *scp << " uc = " << *ucp << " c16 = " << *c16p << " c32 = " << *c32p << " i = " << *ip << " si = " << *sip
         << " li = " << *lip << " f = " << *fp << " d = " << *dp << endl;

    // bp = &c;
    // cp = &b;

    // scp = &c;
    // cp = &uc;

    // ip = &c;
    // ip = &si;
    // ip = &li;
    // ip = &c16;
    // ip = &c32;
    // ip = &f;
    // ip = &d;
}

void test_integer_literal_types() {
    cout << sizeof(2147483647) << endl;
    cout << sizeof(2147483647ll) << endl; // Not inline with The C++ programming language book.
    cout << sizeof(3147483648) << endl;
    cout << sizeof(020000000000) << endl;
    cout << sizeof(017777777777) << endl;
    cout << sizeof(0x7FFFFFFF) << endl;
    cout << sizeof(0x80000000) << endl;
}

void self_initialization() {
    int x = 99;
    {
        int z = x;
        int x = x;
        int y = x;
        cout << "z = " << z << " y = " << y << " x = " << x << endl;
    }
}

void declaration_operators() {
    char arr[] = {'a', 'b'};
    char(*var)[2];
    var = &arr;
    for (char c: *var) {
        cout << " " << c;
    }
    cout << endl;
    char* char_pointers[] = {*var, &(*var)[1]};
    for (char* cp: char_pointers) {
        cout << " " << *cp;
    }
    cout << endl;
}

void initialize_list() {
    complex<double> z(1, 0);
    complex<double> z1(1);
    complex<double> z2{1, 0};
    // complex<double> z3(); // linker error, because it's a function declaration...
    complex<double> z4{};

    cout << "z = " << z << " z1 = " << z1 << " z2 = " << z2 << " z3 = " <<  " null " << " z4 = " << z4 << endl;
}

void auto_detection(int& v) {
    cout << "before v = " << v << endl;
    auto x = v, &y = v;

    x = 7;
    cout << " after first attemtp to change v, v = " << v << endl;

    y = 99;
    cout << " after second attemtp to change v, v = " << v << endl;
}

void array_size(int x) {
    int y = 88;
    const int z = 77;
    int arr1[z];
    // int arr2[y]; // expression did not evaluate to a constant
    // int arr3[x]; // expression did not evaluate to a constant
}

void printing_char_arrays(char* input) {
    char arr1[] = {'a', 'b', 'c'};
    char arr2[] = {'d', 'e', 'f', 'g', 'h', '\0'};
    char arr3[] = "more adventurous!!";
    char* arr4 = "testing constness of std::string"; // should be giving error as per the book, but 
                                                     // Microsoft (R) C/C++ Optimizing Compiler Version 19.37.32824 for x86 does not.

    cout << "arr1 = " << arr1 << "\narr2 = " << arr2 << "\narr3 = " << arr3 << "\n input array = " << input << "\n arr4 = " << arr4 << endl; 
    cout << "printing aray from a specific index:\n arr1+1 = " << arr1+1 << "\narr2 + 2 = " << arr2 + 2 << "\narr3 + 3 = "
         << arr3 + 3 << "\n input array + 4 = " << input + 4 << "\n arr4+5 = " << arr4 + 5 << endl;
    cout << "printing array sizes:\n sizeof(arr1) = " << sizeof(arr1) << "\nsizeof(arr2)" << sizeof(arr2) << "\nsizeof(arr3)"
         << sizeof(arr3) << "\n size(input) = " << sizeof(input) << "\nsizeof(arr4) = " << sizeof(arr4) << endl;

    cout << "character at arr4+10 = " << arr4[10] << endl;
    // arr4[10] = '\0'; // fails if arr4 is char*, but works if arr4 is char[];
    cout << "after changing, arr4 = " << arr4 << endl;
    cout << "beep at the end of the message \a" << endl;
    std::chrono::milliseconds timespan(2000);
    std::this_thread::sleep_for(timespan);
    cout << "beep after sleeping for 2 seconds... \a" << endl;
}

void iterate_an_array_in_a_different_manner() {
    int arr[] = {1,2,3,4,5};
    for (int i = 0; i < 5; i++) {
        cout << "arr["<<i<<"] = " << i[arr] << " "; // from the book: The C++ Programming Language by Bjarne Stroustrup
                                                    // a[j] == ∗(&a[0]+j) == ∗(a+j) == ∗(j+a) == j[a]
    }
    cout << endl;
}

void pointer_arithmatic() {
    int arr1[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int arr2[] = {44, 55, 66, 77};
    // cout << "&arr1[3] + &arr1[2] = " << &arr1[3] + &arr1[2] << endl; //'+': cannot add two pointers
    cout << "&arr1[3] - &arr1[2] = " << &arr1[3] - &arr1[2] << endl;
    cout << "(char*)&arr1[2] - (char*)&arr1[3] = " << (char*)&arr1[3] - (char*)&arr1[2] << endl;
    cout << "(short*)&arr1[2] - (short*)&arr1[3] = " << (short*)&arr1[3] - (short*)&arr1[2] << endl;
    cout << "&arr1[3] - &arr2[3] = " << &arr1[2] - &arr2[3] << endl; // this behaviour is undefined.....
}

int& return_a_received_ref_as_is(int& input) {
    return input;
}

void change_local_var_by_ref() {
    int arr[] = {11, 22, 33, 44, 55, 66};
    cout << "before: ";
    for (int i: arr) cout << " " << i;
    cout << endl;
    return_a_received_ref_as_is(arr[3]) = 33;
    cout << "after: ";
    for (int i: arr) cout << " " << i;
    cout << endl;
}

int main() {
    //bool b{7}; // narrowing: A narrowing conversion changes a value to a data type that might not be able to hold some of the possible values.
                 // e.g. fraction to integral, integral to boolean (boolean can be true or false, while integral (16 bit) can be -16384 to 16384)

    int x1 = 1;
    bool b1{x1==2}; // permitted


    // bool conversions
    bool x = true;
    bool y = false;

    bool z = x+y;
    bool z1 = x-y;
    bool z2 = x||y;
    bool z3 = x>>y;
    bool z4 = x << y;
    bool z5 = x && y;

    // print_all_args("printing following variables in order: x, y, z, z1, z2, z3, z4, z5", x, y, z, z1, z2, z3, z4, z5, NULL);
    // cout << "--------------------------------------" << endl;
    // cout << "x = " << x << " y = " << y << " z = " << z << " z1 = " << z1 << " z2 = " << z2 << " z3 = " << z3 << " z4 = " << z4 << " z5 = " << z5 << endl;

    // print_all_remaining_digits_from('0');
    // print_next_10_chars('0');
    // test_integer_literal_types();
    // self_initialization();
    // declaration_operators();
    // initialize_list();
    int test_var = -20;
    // auto_detection(test_var);
    char char_input[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    // const char* p_char_input = {'1', '2', '3', '4', '5', '6', '7', '8', '9'}; // 'initializing': cannot convert from 'initializer list' to 'const char *'
    // printing_char_arrays(char_input);
    // printing_char_arrays(p_char_input);
    // iterate_an_array_in_a_different_manner();
    // pointer_arithmatic();
    change_local_var_by_ref();

    return 0;
}