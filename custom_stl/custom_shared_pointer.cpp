#include <iostream>

template <typename T>
class SP {
	T* data;
	int* count;
public:
	explicit SP(T* pData)
	try: data{pData}, count{new int{1}}
	{
		std::cout << "explicit 1 arg ctr..." << std::endl;
	}
	catch(...) {
		delete pData;
		std::cerr << "Unable to create counter." << std::endl;
		throw;
	}

	SP(const SP& sp): data{sp.data}, count{sp.count} {
		std::cout << "copy ctr..." << std::endl;
		++*count;
	}
	SP(SP&& sp) = default;

	~SP() {
		std::cout << "[SP] dtor. count = " << *count << std::endl;
		--*count;
		if (!*count) {
			delete data;
			delete count;
		}
	}

	SP& operator=(SP sp) {
		std::cout << "copy assignment operator" << std::endl;
		sp.swap(*this);
	}

	void swap(SP& other) {
		std::swap(data, other.data);
		std::swap(count, other.count);
	}
	SP& operator=(SP&& sp) = default;

	T* operator->() const noexcept { return data; }
	T& operator*() const noexcept { return *data; }

	int use_count() const noexcept { return *count; }


	T* get() const noexcept { return data; }
	explicit operator bool() const noexcept { return data; }
};

template <typename T, typename... Args>
SP<T> make_sp(Args&&... args) {
	return SP<T>{new T{std::forward<Args>(args)...}};
}

struct Data{
	int a;
	Data(): a{25} { std::cout << "[DATA] default ctr..." << std::endl; }
	Data(int x): a{x} { std::cout << "[DATA] 1 arg ctr... x= " << x << std::endl; }
};

int main() {
	SP<Data> sp1 = make_sp<Data>();
	SP<Data> sp2 = make_sp<Data>(45);
	SP<Data> sp3 = sp1;
	SP<Data> sp4 = std::move(sp2);
}