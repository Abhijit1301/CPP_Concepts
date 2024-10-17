#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <chrono>
#include <vector>

constexpr int size = 10000000;
std::vector<int> data(size * 3);

void driver1(std::mutex& mutex, std::unique_lock<std::mutex>& l1, std::condition_variable& c1, std::condition_variable& c2, int& count, int& condition, int turn , int limit) {
	using namespace std::chrono_literals;
	while (--limit) {
		l1.lock();
		while (turn % 3 != condition)
			c1.wait(l1);
		// std::cout << "[Thread " << turn+1 << "]: " <<  ++count << std::endl;
		data[count++] = count;
		condition++;
		condition %= 3;
		c2.notify_one();
		l1.unlock();
	}
}

void driver(std::mutex& mutex, std::unique_lock<std::mutex>& l1, std::condition_variable& c1, std::condition_variable& c2, int& count, int& condition, int turn , int limit) {
	while (--limit) {
		l1.lock();
		while (turn % 3 != condition)
			c1.wait(l1);
		// std::cout << "[Thread " << turn+1 << "]: " <<  ++count << std::endl;
		data[count++] = count;
		condition++;
		condition %= 3;
		c2.notify_one();
		l1.unlock();
	}
}


int main() {
	std::mutex m;
	std::condition_variable c1, c2, c3;
	std::unique_lock<std::mutex> l1{m, std::defer_lock};
	std::unique_lock<std::mutex> l2{m, std::defer_lock};
	std::unique_lock<std::mutex> l3{m, std::defer_lock};
	std::unique_lock<std::mutex> lmain{m, std::defer_lock};
	int count{};
	int condition{-1};

	// parallelPrint p(m, c1, c2, c3);
	std::thread t1(driver1, std::ref(m), std::ref(l1), std::ref(c1), std::ref(c2), std::ref(count), std::ref(condition), 0, size+1);
	std::thread t2(driver, std::ref(m), std::ref(l2), std::ref(c2), std::ref(c3), std::ref(count), std::ref(condition), 1, size+1);
	std::thread t3(driver, std::ref(m), std::ref(l3), std::ref(c3), std::ref(c1), std::ref(count), std::ref(condition), 2, size+1);

	lmain.lock();
	condition = 0;
	c1.notify_one();
	lmain.unlock();
	t1.join();
	t2.join();
	t3.join();

	for (int i = 0; i < 3 * size; ++i) {
		if (data[i] != (i + 1)) std::cout << "data[" << i << "] = " << data[i] << std::endl;
	}
	std::cout << "Done!!!" << std::endl;
}