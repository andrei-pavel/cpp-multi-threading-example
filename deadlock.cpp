#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

size_t const A_COUNT = 1;
size_t const B_COUNT = 1;

std::mutex Mutex1, Mutex2;

void a() {
  while (true) {
    Mutex1.lock();
    Mutex2.lock();
    std::cout << "a" << std::flush;
    Mutex2.unlock();
    Mutex1.unlock();
  }
}

void b() {
  while (true) {
    Mutex2.lock();
    Mutex1.lock();
    std::cout << "b" << std::flush;
    Mutex1.unlock();
    Mutex2.unlock();
  }
}

int main() {
  std::vector<std::thread> threads;

  // Launch As.
  for (ssize_t i = A_COUNT; i > 0; --i) {
    threads.push_back(std::thread(a));
  }

  // Launch Bs.
  for (ssize_t i = B_COUNT; i > 0; --i) {
    threads.push_back(std::thread(b));
  }

  // Wait for all.
  for (size_t i = 0; i < threads.size(); ++i) {
    threads[i].join();
  }

  return EXIT_SUCCESS;
}
