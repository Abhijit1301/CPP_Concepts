#include <windows.h>
#include <profileapi.h>

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

const int CPU = 64;

struct custom_counter {
	int global_count{};
	std::mutex global_counter_lock{};
	int threshold = 100000;
	int local_count[CPU]{};
	std::mutex local_counter_lock[CPU]{};
} counter;

void increment(custom_counter* ctr, int thread_id) {
	int index = thread_id % CPU;
	std::lock_guard<std::mutex> local_guard(ctr->local_counter_lock[index]);
	++ctr->local_count[index];
	if (ctr->local_count[index] == ctr->threshold) {
		std::lock_guard<std::mutex> global_guard(ctr->global_counter_lock);
		ctr->global_count += ctr->local_count[index];
		ctr->local_count[index] = 0;
	}
	// std::cout << "After incrementing counter value = " << ctr->count << std::endl;
}

int getCount(custom_counter* ctr) {
	std::lock_guard<std::mutex> global_guard(ctr->global_counter_lock);
	return ctr->global_count;
}

void incrementnTimes(custom_counter* ctr, int n, int thread_id) {
	for(int i = 0; i < n; ++i) increment(ctr, thread_id);
}

// void decrementnTimes(custom_counter* ctr, int n) {
// 	for(int i = 0; i < n; ++i) decrement(ctr);
// }

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
		std::thread* t = new std::thread(incrementnTimes, &counter, n, i);
		thread_list.push_back(t);
	}

	// std::thread t1(incrementnTimes, &counter, n, ++thread_id);
	// std::thread t2(incrementnTimes, &counter, n, ++thread_id);
	// std::thread t3(incrementnTimes, &counter, n, ++thread_id);
	// std::thread t4(incrementnTimes, &counter, n, ++thread_id);
	// std::thread t5(incrementnTimes, &counter, n, ++thread_id);
	// std::thread t6(incrementnTimes, &counter, n, ++thread_id);
	// std::thread t7(incrementnTimes, &counter, n, ++thread_id);
	// std::thread t8(incrementnTimes, &counter, n, ++thread_id);

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
