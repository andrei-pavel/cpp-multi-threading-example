#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::vector<uint32_t> buffer;
std::mutex mutex;

void aFunction() {
  while (true) {
    std::cout << "a" << std::endl;
    mutex.lock();
  }
}

void bFunction() {
  while (true) {
    std::cout << "b" << std::endl;
    mutex.lock();
  }
}

int main() {
  // Initialize threads.
  std::thread a(aFunction);
  std::thread b(bFunction);

  // Wait for threads to finish.
  a.join();
  b.join();

  return EXIT_SUCCESS;
}
