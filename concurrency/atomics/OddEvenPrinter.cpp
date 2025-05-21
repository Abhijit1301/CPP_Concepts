#include <iostream>
#include <atomic>
#include <thread>

#define LIMIT 15

bool isOdd(int &num) {
  return num % 2;
}

bool isEven(int num) {
  return !isOdd(num);
}

void print(int &counter, bool printOdd, std::atomic<bool>& oddFlag, std::atomic<bool>& evenFlag, std::atomic<int>& loopCounter)
{
  while (counter < LIMIT) {
    if (oddFlag.load() && printOdd && isOdd(counter)) {
      std::cout << "Odd Printer: " << counter++ << std::endl;
      oddFlag.store(false);
      evenFlag.store(true);
    }
    else if (evenFlag.load() && !printOdd && isEven(counter)) {
      std::cout << "Even Printer: " << counter++ << std::endl;
      evenFlag.store(false);
      oddFlag.store(true);
    }
    loopCounter++;
  }
}

int main() {
  int counter = 1;
  std::atomic<bool> oddFlag {true};
  std::atomic<bool> evenFlag {false};
  std::atomic<int>  loopCounter {0};
  std::thread t1(&print, std::ref(counter), false, std::ref(oddFlag), std::ref(evenFlag), std::ref(loopCounter));
  std::thread t2(&print, std::ref(counter), true, std::ref(oddFlag), std::ref(evenFlag), std::ref(loopCounter));

  t1.join();
  t2.join();

  std::cout << "Loop counter = " << loopCounter.load() << std::endl;
}
