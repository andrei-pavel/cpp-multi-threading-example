#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

size_t const CONSUMER_COUNT = 1;
size_t const PRODUCER_COUNT = 1;

std::vector<uint32_t> Buffer;
std::mutex Mutex;
int32_t ID = 0;
int32_t LastShownID = -1;

void consumer() {
  Mutex.lock();
  int32_t id = ID;
  ++ID;
  Mutex.unlock();
  while (true) {
    Mutex.lock();
    // while (true) {
    auto item = Buffer.begin();
    if (item != Buffer.end()) {
      Buffer.erase(item);
      if (LastShownID != id) {
        std::cout << "Consumer " << id << std::endl;
        LastShownID = id;
      }
    }
    // }
    Mutex.unlock();
  }
}

void producer() {
  Mutex.lock();
  int32_t id = ID;
  ++ID;
  Mutex.unlock();
  while (true) {
    Mutex.lock();
    static uint32_t item = 0;
    Buffer.push_back(item++);
    if (LastShownID != id) {
      std::cout << "Producer " << id << std::endl;
      LastShownID = id;
    }
    Mutex.unlock();
  }
}

int main() {
  std::vector<std::thread> threads;

  // Launch consumers.
  for (ssize_t i = CONSUMER_COUNT; i > 0; --i) {
    threads.push_back(std::thread(consumer));
  }

  // Launch producers.
  for (ssize_t i = PRODUCER_COUNT; i > 0; --i) {
    threads.push_back(std::thread(producer));
  }

  // Wait for all.
  for (size_t i = 0; i < threads.size(); ++i) {
    threads[i].join();
  }

  return EXIT_SUCCESS;
}
