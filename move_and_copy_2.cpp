#include <iostream>
#include <string>

struct MyData {
    int* count;
    MyData(): count{new int{567}} { std::cout << "default ctor..." << std::endl; }
    explicit MyData(int x): count{new int{x}} { std::cout << "single arg ctor..." << std::endl; }
    MyData(const MyData& rhs): count{new int{*rhs.count}} {std::cout << "copy ctor..." << std::endl;}
    MyData(MyData&& rhs): count{rhs.count} {std::cout << "move ctor..." << std::endl; rhs.count = nullptr;}
    MyData& operator=(const MyData& rhs) = delete;
    MyData& operator=(MyData&& rhs) noexcept = delete;
};

MyData func(MyData& arg) {
    MyData arg1{4332};
    std::cout << "arg1 = " << *arg1.count << std::endl;
    MyData arg2 = arg1;
    std::cout << "arg2 = " << *arg2.count << std::endl;
    std::cout << "returning from func...\n";
    return arg2;
}

void printMyData(MyData& arg) {
    std::cout << "[lvalue ref] My data.count = " << *arg.count << std::endl;
}

void printMyData(MyData&& arg) {
    std::cout << "[RValue ref] My data.count = " << *arg.count << std::endl;
}

int main()
{
    std::cout<<"Hello World\n";
    MyData local{789};
    MyData local2{45789};
    
    // MyData ret = func(local);
    MyData ret2 = local2;
    
    printMyData(local2);
    printMyData(func(local2));
    std::cout << "local = " << local.count << std::endl;
    // std::cout << "ret = " << *ret.count << std::endl;

    return 0;
}
