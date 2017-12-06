#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::vector<uint32_t> buffer;
std::mutex mutex;

void consumerFunction() {
  while (true) {
    mutex.lock();
    while (true) {
      auto item = buffer.begin();
      if (item == buffer.end()) {
        break;
      }
      std::cout << *item << std::endl;
      buffer.erase(item);
    }
    mutex.unlock();
  }
}

void producerFunction() {
  while (true) {
    mutex.lock();
    static uint32_t item = 0;
    do {
      buffer.push_back(item++);
    } while (item % 10 != 0);
    mutex.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main() {
  // Initialize threads.
  std::thread consumer(consumerFunction);
  std::thread producer(producerFunction);

  // Wait for threads to finish.
  consumer.join();
  producer.join();

  return EXIT_SUCCESS;
}
