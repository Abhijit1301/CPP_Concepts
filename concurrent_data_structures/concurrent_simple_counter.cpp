#include <windows.h>
#include <profileapi.h>

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

struct custom_counter {
	int count{};
	std::mutex common_counter_lock{};
} counter;

void increment(custom_counter* ctr) {
	std::lock_guard<std::mutex> slg(ctr->common_counter_lock);
	++ctr->count;
	// std::cout << "After incrementing counter value = " << ctr->count << std::endl;
}

void decrement(custom_counter* ctr) {
	std::lock_guard<std::mutex> slg(ctr->common_counter_lock);
	--ctr->count;
	// std::cout << "After decrementing counter value = " << ctr->count << std::endl;
}

int getCount(custom_counter* ctr) {
	std::lock_guard<std::mutex> slg(ctr->common_counter_lock);
	return ctr->count;
}

void incrementnTimes(custom_counter* ctr, int n) {
	for(int i = 0; i < n; ++i) increment(ctr);
}

void decrementnTimes(custom_counter* ctr, int n) {
	for(int i = 0; i < n; ++i) decrement(ctr);
}

int main() {
	std::cout << "Initial counter value = " << getCount(&counter) << std::endl;
	int n = 1000000;
	int thread_count = 128;

	// Timing the process...
	LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
	LARGE_INTEGER Frequency;

	QueryPerformanceFrequency(&Frequency); 
	QueryPerformanceCounter(&StartingTime);
	// Timing initialization END

	std::vector<std::thread*> thread_list{};
	for (int i = 1; i <= thread_count; ++i) {
		std::thread* t = new std::thread(incrementnTimes, &counter, n);
		thread_list.push_back(t);
	}
	// std::thread t1(incrementnTimes, &counter, n);
	// std::thread t2(incrementnTimes, &counter, n);
	// std::thread t3(incrementnTimes, &counter, n);
	// std::thread t4(incrementnTimes, &counter, n);
	// std::thread t5(incrementnTimes, &counter, n);
	// std::thread t6(incrementnTimes, &counter, n);
	// std::thread t7(incrementnTimes, &counter, n);
	// std::thread t8(incrementnTimes, &counter, n);

	// t1.join(); t2.join(); t3.join(); t4.join(); t5.join(); t6.join(); t7.join(); t8.join();
	for (int i = 0; i < thread_count; ++i) {
		thread_list[i]->join();
	}

	// calculating time taken...
	QueryPerformanceCounter(&EndingTime);
	ElapsedMicroseconds.QuadPart = EndingTime.QuadPart - StartingTime.QuadPart;
	ElapsedMicroseconds.QuadPart *= 1000000;
	ElapsedMicroseconds.QuadPart /= Frequency.QuadPart;

	std::cout << "initial ticks = " << StartingTime.QuadPart << " final ticks = " << EndingTime.QuadPart << std::endl;
	std::cout << "time taken in micro seconds = " << ElapsedMicroseconds.QuadPart << std::endl;

	std::cout << "Done playing with counter. final value = " << getCount(&counter) << std::endl;
}
