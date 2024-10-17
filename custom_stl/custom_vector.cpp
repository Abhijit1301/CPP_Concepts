#include <memory>
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>

template <typename T, typename Allocator = std::allocator<T>>
struct custom_vector_base {
	Allocator alloc;
	T* begin;
	T* space;
	T* end;
	// Allocator alloc;

	custom_vector_base(const unsigned int& size, const Allocator& a = Allocator{}):
		alloc{a},
		begin{alloc.allocate(size)},
		space{begin + size},
		end{begin + size} {
		// std::cout << "size = " << size << " begin = " << begin << " end = " << end << " space = " << space << " size = " << space - begin << " capacity = " << end - begin << std::endl;
	}
	~custom_vector_base() {
		alloc.deallocate(begin, end - begin);
	}
	custom_vector_base(const custom_vector_base& cvb) = delete;
	custom_vector_base& operator=(const custom_vector_base& cvb) = delete;

	custom_vector_base(custom_vector_base&& cvb):
		begin{cvb.begin},
		space{cvb.space},
		end{cvb.end},
		alloc{move(cvb.alloc)}
	{
		cvb.begin = cvb.space = cvb.end = nullptr;
	}

	custom_vector_base& operator=(custom_vector_base&& cvb) {
		// std::cout << "move assignment..." << std::endl;
		begin = cvb.begin;
		space = cvb.space;
		end = cvb.end;
		alloc = std::move(cvb.alloc);
		cvb.begin = cvb.space = cvb.end = nullptr;
		return *this;
	}

	void clear() {
		alloc.deallocate();
	}
};

template <typename T, typename Allocator> class custom_vector;
template <typename T, typename Allocator>
std::ostream& operator<<(std::ostream& ostr, const custom_vector<T, Allocator> & vec);

template <typename T, typename Allocator = std::allocator<T>>
class custom_vector {
	custom_vector_base<T, Allocator> cvb;
	void check(unsigned int index) {
		std::ostringstream ost("invalid index: ");
		ost << __FILE__ << ':' << __LINE__;
		if (index > size()) throw std::range_error(ost.str());
	}

public:
	// custom_vector();
	custom_vector(unsigned int size, const T& val = T{}, const Allocator& a = Allocator{});
	// custom_vector(std::initializer_list<T> list);
	custom_vector(const custom_vector& vec);
	custom_vector(custom_vector&& vec);

	~custom_vector() = default;

	custom_vector& operator=(const custom_vector& vec);
	custom_vector& operator=(custom_vector&& vec);

	T& operator[](const unsigned int& index) { check(index); return *(cvb.begin+index); }
	const T& operator[] (const unsigned int& index) const { check(index); return *(cvb.begin+index); }

	custom_vector& push_back(const T& elem);
	custom_vector& pop_back();

	unsigned int size() const { return cvb.space - cvb.begin; }
	unsigned int capacity() const { return cvb.end - cvb.begin; }
	void reserve(unsigned int n);
	void resize(unsigned int n, const T& = T{});

	template <typename U, typename A>
	friend std::ostream& operator<<(std::ostream& ostr, const custom_vector<U, A>& vec);
};

template <typename T, typename Allocator>
custom_vector<T, Allocator>::custom_vector(unsigned int size, const T& val, const Allocator& alloc):
	cvb{size, alloc} {
	std::uninitialized_fill(cvb.begin, cvb.end, val);
}

template <typename T, typename Allocator>
custom_vector<T, Allocator>::custom_vector(const custom_vector& vec):
	cvb{vec.size(), vec.cvb.alloc}
{
	std::uninitialized_copy(vec.cvb.begin, vec.cvb.space, cvb.begin);
}

template <typename T>
void my_uninitialized_move(T* srcBegin, T* srcEnd, T* destBegin) {
	while (srcBegin < srcEnd) {
		// std::cout << "before: " << *destBegin;
		new(static_cast<void*>(destBegin)) T{std::move(*srcBegin)};
		// std::cout << " after: " << *destBegin << std::endl;
		srcBegin->~T();
		++destBegin;
		++srcBegin;
	}
}

template <typename T, typename Allocator>
custom_vector<T, Allocator>::custom_vector(custom_vector&& vec):
	cvb{move(vec.cvb)}
{
	// std::uninitialized_move(vec.cvb.begin, vec.cvb.space, cvb.begin);
	my_uninitialized_move(vec.cvb.begin, vec.cvb.space, cvb.begin);
}

template<typename T, typename Allocator>
custom_vector<T, Allocator>& custom_vector<T, Allocator>::operator=(const custom_vector& vec) {
	if (capacity() < vec.size()) {
		custom_vector<T, Allocator> temp{vec};
		swap(*this, temp);
		return *this;
	}
	if (this == &vec) return *this;

	int sz = size();
	int vecSz = vec.size();
	cvb.alloc = vec.cvb.alloc;
	if (sz > vecSz) {
		std::copy(vec.cvb.begin, vec.cvb.space, cvb.begin);
		for (T* itr = cvb.begin + vecSz; itr < cvb.space; ++itr)
			itr->~T(); 
	} else {
		copy(vec.cvb.begin, vec.cvb.begin + sz, cvb.begin);
		std::uninitialized_copy(vec.cvb.begin + sz, vec.cvb.space, cvb.space);
	}
}

template<typename T, typename Allocator>
custom_vector<T, Allocator>& custom_vector<T, Allocator>::operator=(custom_vector&& vec) {
	for (T* itr = cvb.begin; itr < cvb.space; ++itr)
		itr->~T();
	swap(*this, vec);
	return *this;
}

template <typename T, typename Allocator>
void custom_vector<T, Allocator>::reserve(unsigned int n) {
	if (n < capacity()) return;
	custom_vector_base<T, Allocator> temp{n, cvb.alloc};
	temp.space = temp.begin + size();
	// std::cout << *this << std::endl;
	// std::uninitialized_move (cvb.begin, cvb.space, temp.begin);
	my_uninitialized_move(cvb.begin, cvb.space, temp.begin);
	// std::cout << *this << std::endl;
	// std::cout << "size before: " << size() << std::endl;
	swap(cvb, temp);
	// std::cout << "size before: " << size() << std::endl;
}

template <typename T, typename Allocator>
void custom_vector<T, Allocator>::resize(unsigned int n, const T& val) {
	reserve(n);
	if (size() > n) {
		for (T* itr = cvb.begin; itr < cvb.space; ++itr)
			itr->~T();
	} else {
		std::uninitialized_fill(cvb.space, cvb.begin + n, val);
	}
	cvb.space = cvb.begin + n;
}

template <typename T, typename Allocator>
custom_vector<T, Allocator>& custom_vector<T, Allocator>::push_back(const T& val) {
	if (size() == capacity())
		reserve(size() ? 1.7 * size() : 8);
	// cvb.alloc.construct(cvb.space, val);
	new (static_cast<void*>(cvb.space)) T{val};
	++cvb.space;
	return *this;
}

template <typename T, typename Allocator>
std::ostream& operator<<(std::ostream& ostr, const custom_vector<T, Allocator> & vec) {
	for (T* itr = vec.cvb.begin; itr < vec.cvb.space; ++itr)
		ostr << *itr << " ";
	return ostr;
}

using my_pair = std::pair<std::string, double>;
template <>
std::ostream& operator<< < my_pair, std::allocator<my_pair>>(std::ostream& ostr,
															const custom_vector<my_pair, std::allocator<my_pair>>& vec) {
	for (std::pair<std::string, double>* itr = vec.cvb.begin; itr < vec.cvb.space; ++itr) {
		ostr << "<" << itr->first << "," << itr->second << "> ";
	}
	return ostr;
}
struct MyData {
	int a;
	MyData(): a{456} {
		std::cout << "[MyData]: default ctor..." << std::endl;
	}
	MyData(const MyData& rhs): a{rhs.a} {
		std::cout << std::endl << "[MyData]: copy ctor..." << std::endl;
	}
	MyData(MyData&& rhs): a{rhs.a} { 
		std::cout << "[MyData]: move ctor..." << std::endl;
		std::exchange(rhs.a, 0);
	}
	MyData& operator=(const MyData& rhs) {
		std::cout << "[MyData]: copy assignment..." << std::endl;
		a = rhs.a;
	}
	MyData& operator=(MyData&& rhs) {
		std::cout << "[MyData]: move assignment..." << std::endl;
		a = rhs.a;
		std::exchange(rhs.a, 0);
	}
};

std::ostream& operator<< (std::ostream& os, MyData obj) {
	os << obj.a;
	return os;
}

int main() {
	custom_vector<int> cvec1(5, 77);

	// std::cout << "cvec1 = " << cvec1 << std::endl;

	cvec1.push_back(5);
	cvec1.push_back(15);
	cvec1.push_back(17);
	cvec1.push_back(25);
	cvec1.push_back(125);
	cvec1.push_back(172);

	// std::cout << "after 5 push_back, cvec1 = " << cvec1 << std::endl;

	custom_vector<int> cvec2 = cvec1;
	// std::cout << "cvec2 = " << cvec2 << std::endl;

	custom_vector<int> cvec3 = std::move(cvec1);
	// std::cout<< "cvec3 = " << cvec3 << std::endl;
	// std::cout << "after moving cvec1 = " << cvec1 << std::endl;

	custom_vector<int> cvec4 = std::move(cvec3);
	// std::cout << "cvec4 = " << cvec4 << std::endl;
	// std::cout << "after moving cvec3 = " << cvec3 << std::endl;

	cvec4.resize(15, 456);
	// std::cout << "cvec4 resized: " << cvec4 << std::endl;

	cvec4.push_back(-45);
	cvec4.push_back(-145);
	cvec4.push_back(-415);
	cvec4.push_back(-451);
	// std::cout << "after pushing 4 more elements, cvec4 = " << cvec4 << std::endl;

	custom_vector<my_pair> cvec5{5};
	// std::cout << "default cvec5 = " << cvec5 << std::endl;

	custom_vector<my_pair> cvec6{5, {"my pair", 7.777}};
	// std::cout << "initial value my_pair custom vector = " << cvec6 << std::endl;
	cvec6.push_back({"6th element", 6.66});
	cvec6.push_back({"7th element", 7.77});
	cvec6.push_back({"8th element", 8.88});
	cvec6.push_back({"9th element", 9.99});
	cvec6.push_back({"10th element", 10.1010});
	// std::cout << "after pushing 5 elements, cvec6 = " << cvec6 << std::endl;

	cvec6.resize(15, {"resized cvec6...", 99.99});
	// std::cout << "after resizing cvec6 to 15 elements... = " << cvec6 << std::endl;

	cvec6.push_back({"16th elem...", 16.1616});
	cvec6.push_back({"17th elem...", 17.1717});
	cvec6.push_back({"18th elem...", 18.1818});
	// std::cout << "after pushing again cvec6  = " << cvec6 << std::endl;

	custom_vector<MyData> cvec7(5);
	std::cout << cvec7 << std::endl;
	MyData d_1;
	d_1.a = 9999;
	cvec7.push_back(d_1);
	std::cout << cvec7 << std::endl;
}
