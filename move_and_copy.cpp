#include <iostream>

class CopyVsMove {
public:

	int a;
	double b;
	char c;
	std::string s;

	CopyVsMove(): a{23}, b{34.34}, c{100}, s{"A quick brown..."} {
		std::cout << "Default constructor......... a,b,c and s: ";
		std::cout << a << "  " << b << "  " << c << "  " << s << std::endl;
	}
	CopyVsMove(int a, double d, char c, std::string str): a{a}, b{d}, c{c}, s{str} {
		std::cout << "All args constructor......... a,b,c and s: ";
		std::cout << a << "  " << b << "  " << c << "  " << s << std::endl;
	}

	CopyVsMove(const CopyVsMove& obj) {
		std::cout << "Copy constructor..." << std::endl;
		this->a = obj.a;
		this->b = obj.b;
		this->c = obj.c;
		this->s = obj.s;
	}
	CopyVsMove(CopyVsMove&& obj):
		a{std::exchange(obj.a, 0)},
		b{std::exchange(obj.b, -1.11)},
		c{std::exchange(obj.c, '_')},
		s{std::move(obj.s)}
	{
		std::cout << "Move constructor..." << std::endl;
	}
	std::ostream& operator<<(std::ostream& streamObj) {
		streamObj << "a = " << a << " b = " << b << " c = " << c << " s = " << s << std::endl;
		return streamObj;
	}
};

class Derived: public CopyVsMove {
	int da;
	double dd;
};

CopyVsMove createObj(CopyVsMove obj) {
	return obj;
}


int main() {
	CopyVsMove obj1(20, 55.55, 98, "Hello Abhijeet");
	CopyVsMove obj2 = obj1;
	obj2 << std::cout;
	CopyVsMove obj3 = createObj(obj1);
	obj3 << std::cout;

	Derived d1;
	d1 << std::cout;
	Derived d2 = d1;
	d2 << std::cout;
	d1 << std::cout;

	createObj(createObj(d1));

	return 0;
}
