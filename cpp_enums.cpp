#include <iostream>

int main()
{
    printf("Hello World");
    enum class Days: char{
        Monday,
        Tuesday,
        Wednesday
    };
    Days d1 = Days::Monday;
	Days d2 = Days::Tuesday;
	Days d3 = Days::Wednesday;
	
    std::cout << std::endl << std::boolalpha << (d1 == d2) << "  " << sizeof(d2) << "  " << static_cast<int>(d3)  << std::endl;

    return 0;
}