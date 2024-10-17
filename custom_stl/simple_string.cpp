#include <stdexcept>
#include <iostream>

class simple_string {
public:
	using size_type = unsigned int;
	// constructors
	simple_string();
	simple_string(const char * cstr);
	simple_string(const simple_string& str);
	simple_string(simple_string&& str);

	// destructor
	~simple_string();

	// assignment operators
	simple_string& operator=(const simple_string& str);
	simple_string& operator=(simple_string&& str);

	// operators
	char& operator[](size_type index) { check(index); return ptr[index]; }
	char operator[] (size_type index) const { check(index); return ptr[index]; }
	char& at(size_type index) { check(index); return ptr[index]; }
	char at(size_type index) const { check(index); return ptr[index]; }
	simple_string& operator+(const char& chr);
	size_type size() const { return sz; }
	size_type capacity() const { return sz <= simple_string::short_max ? simple_string::short_max : sz + space; }
	const char* c_str() const { return ptr; }

private:
public:
	size_type sz;
	char* ptr;
	char* ptr2;
	static const short short_max = 15;
	static const short another = 34;
	union {
		size_type space;
		char ch[short_max + 1];
	};

	void check(size_type n) const {
		if (n < 0 || sz <= n)
			throw std::out_of_range("[ERROR]: accessing element from outside the range of the string");
		
	}

	void copy_from(const simple_string& str);
	void move_from(simple_string& str);
};

char* expand(char* str, int n) {
	char* pch = new char[n];
	strcpy(pch, str);
	return pch;
}

void simple_string::copy_from(const simple_string& str) {
	if (str.sz <= simple_string::short_max) {
		memcpy(ch, str.ch, sizeof(str));
		ptr = ch;
	} else {
		ptr = expand(str.ptr, str.sz + 1);
		sz = str.sz;
		space = 0;
	}
}

void simple_string::move_from(simple_string& str) {
	if (str.sz <= simple_string::short_max) {
		memcpy(ch, str.ch, sizeof(str));
	} else {
		ptr = str.ptr;
		sz = str.sz;
		space = str.space;
		str.ptr = str.ch;
		str.sz = 0;
		str.ch[0] = 0;
	}
}

simple_string::simple_string(): ptr(ch), sz(0)
{
	ch[0] = 0;
}

simple_string::simple_string(const char* cstr):
				sz{strlen(cstr)},
				ptr{(sz <= simple_string::short_max) ? ch : new char[sz + 1]},
				space{0}
{
	strcpy(ptr, cstr);
}

simple_string::simple_string(const simple_string& str)
{
	copy_from(str);
}

simple_string::simple_string(simple_string&& str)
{
	move_from(str);
}

simple_string::~simple_string() {
	if (sz > simple_string::short_max) delete[] ptr;
}

simple_string& simple_string::operator=(const simple_string& str) {
	if (this == &str) return *this;
	char* tmp = (sz >= simple_string::short_max) ? ptr : 0;
	copy_from(str);
	delete[] tmp;
	return *this;
}

simple_string& simple_string::operator=(simple_string&& str) {
	if (this == &str) return *this;
	if (sz > simple_string::short_max) delete[] ptr;
	move_from(str);
	return *this;
}

simple_string& simple_string::operator+(const char& ch) {
	if (sz == simple_string::short_max) {
		int n = sz + sz + 2;
		ptr = expand(ptr, n);
		space = n - sz - 2;

	} else if (sz > simple_string::short_max) {
		if (space == 0) {
			int n = sz + sz + 2;
			char* temp = expand(ptr, n);
			delete[] ptr;
			ptr = temp;
			space = n - sz - 2;
		} else {
			--space;
		}
	}
	ptr[sz] = ch;
	ptr[++sz] = 0;

	return *this;
}

const char* begin(const simple_string& str) {
	return str.c_str();
}

const char* end(const simple_string& str) {
	return str.c_str() + str.size();
}

std::ostream& operator<<(std::ostream& ostream, const simple_string& str) {
	return ostream << str.c_str();
}

simple_string& operator+(simple_string& str1, const simple_string& str2) {
	for (auto ch: str2) {
		str1 = str1 + ch;
	}
	std::cout << str1 << std::endl;
	return str1;
}

int main() {
	simple_string s1; 
	simple_string s2{"hello, world!... How have you been? So far so good???"};
	std::cout << s1 << "\n" << s2 << std::endl;
	std::cout << "sizeof(s1) = " << sizeof(s1) << " sizeof(s2) = " << sizeof(s2) << std::endl;
	std::cout << "s2 + some other string = " << s2 + "some other string" << std::endl;
	std::cout << "character access operator test: \n";
	for (char ch: s2) std::cout << ch << " ";
	std::cout << std::endl;
	try {
		std::cout << "Let's try to access out of bounds index...\n";
		std::cout << s2[s2.size()] << std::endl;
	} catch(std::out_of_range excp) {
		std::cout << excp.what() << std::endl;
	}

	return 0;
}
