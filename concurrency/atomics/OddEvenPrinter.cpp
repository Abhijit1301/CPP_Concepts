#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

#define LIMIT 10*10*10*10*10

bool isOdd(int &num) {
  return num % 2;
}

bool isEven(int num) {
  return !isOdd(num);
}

void print(int &counter, bool printOdd, std::atomic<bool>& oddFlag, std::atomic<bool>& evenFlag/*, std::atomic<int>& loopCounter*/)
{
  int oddCounter = 0;
  int evenCounter = 0;

  while (true) {
    if (oddFlag.load() && printOdd && isOdd(counter)) {
      // std::cout << "Odd Printer: " << counter++ << std::endl;
      counter++;
      oddCounter++;
      oddFlag.store(false);
      evenFlag.store(true);
      if (oddCounter == LIMIT) {
        break;
      }
    }
    else if (evenFlag.load() && !printOdd && isEven(counter)) {
      // std::cout << "Even Printer: " << counter++ << std::endl;
      counter++;
      evenCounter++;
      evenFlag.store(false);
      oddFlag.store(true);
      if (evenCounter == LIMIT) {
        break;
      }
    }
    // loopCounter++;
  }
}

void performPrints(int iterations, int & failureCount) {
  while (iterations) {
    // std::cout << "Iteration: " << iterations-- << std::endl;
    int counter = 0;
    // int failureCount = 0;
    std::atomic<bool> oddFlag {false};
    std::atomic<bool> evenFlag {true};
    // std::atomic<int>  loopCounter {0};

    // noting time before starting the threads...
    auto startTime = std::chrono::high_resolution_clock::now();

    std::thread t1(&print, std::ref(counter), false, std::ref(oddFlag), std::ref(evenFlag)/*, std::ref(loopCounter)*/);
    std::thread t2(&print, std::ref(counter), true, std::ref(oddFlag), std::ref(evenFlag)/*, std::ref(loopCounter)*/);

    t1.join();
    t2.join();

    // noting time right after both threads have joined...
    auto endTime = std::chrono::high_resolution_clock::now();

    // std::cout << "Loop counter = " << loopCounter.load() << std::endl;
    // std::cout << "Counter = " << counter << std::endl;

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime);
    // std::cout << "Time taken from starting of threads to joining of threads\n\t\t in (ms): " << duration.count() << std::endl;
    if (counter != 2 * LIMIT) {
      failureCount++;
    }
    // std::cout << "Iteration: " << iterations-- << ", duration(ms): " << duration.count()
              // << " and failures: " << failureCount << std::endl;
  }
}

int main() {
  int iterations = 1000;
  int failureCount = 0;
  performPrints(iterations, failureCount);
  std::cout << "MAIN:::::  Failure #: " << failureCount << std::endl;

  return 0;
}
