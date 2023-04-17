#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include <exception>
#include "doctest/doctest.h"

using namespace std;

template<typename T>
class Queue {
 private:
  // Array that stores the elements of the queue
  T *elements;

  // Index of the start element in the queue
  int headIndex;

  // Index of the end element in the queue
  int tailIndex;

  // Maximum size of the queue
  int maxSize;

  // Current size of the queue
  int currentSize;

 public:
  // Constructor
  explicit Queue(int size = 10) {
    elements = new T[size];
    maxSize = size;
    headIndex = 0;
    tailIndex = -1;
    currentSize = 0;
  }

  // Destructor
  ~Queue() {
    delete[] elements;
  }

  // Method that adds an element to the queue
  void enqueue(T item) {
    // Check if queue is full
    if (currentSize == maxSize) {
      // If it is, throw an exception
      throw overflow_error("Queue overflow");
    }

    // Increment tail index in circular fashion
    // We use the modulo operator to make sure that the index is always between 0 and maxSize - 1
    tailIndex = (tailIndex + 1) % maxSize;

    // Add element to the queue
    elements[tailIndex] = item;

    // Increment current size of queue
    currentSize++;
  }

  // Method that removes an element from the queue
  void dequeue() {
    // Check if queue is empty
    if (currentSize == 0) {
      // If it is, throw an exception
      throw underflow_error("Queue underflow");
    }

    // Increment head index in circular fashion
    // We use the modulo operator to make sure that the index is always between 0 and maxSize - 1
    headIndex = (headIndex + 1) % maxSize;

    // Decrement current size of queue
    currentSize--;
  }

  // Method that gets the front element in the queue
  T peek() {
    // Check if queue is empty
    if (currentSize == 0) {
      // If it is, throw an exception
      throw underflow_error("Queue underflow");
    }

    // Return the element at the head index
    return elements[headIndex];
  }

  // Getter that returns the size of the queue
  int size() {
    return currentSize;
  }

  // Getter that defines whether the queue is empty
  bool isEmpty() {
    return (currentSize == 0);
  }
};

// Main function
int main() {
  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

// Tests
TEST_CASE("Adding elements to queue") {
  // Create queue
  Queue<int> queue(3);

  // Add elements to queue
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  // Check if queue size is correct
  CHECK(queue.size() == 3);

  // Check if queue is not empty
  CHECK(!queue.isEmpty());

  // Check if elements are in correct order
  CHECK(queue.peek() == 1);
  queue.dequeue();
  CHECK(queue.peek() == 2);
  queue.dequeue();
  CHECK(queue.peek() == 3);
  queue.dequeue();
}

TEST_CASE("Removing elements from queue") {
  // Create queue
  Queue<int> queue(3);

  // Add elements to queue
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  // Remove elements from queue
  queue.dequeue();
  queue.dequeue();
  queue.dequeue();

  // Check if queue size is correct
  CHECK(queue.size() == 0);

  // Check if queue is empty
  CHECK(queue.isEmpty());
}

TEST_CASE("Queue overflow") {
  // Create queue of size 3
  Queue<int> queue(3);

  // Add elements to queue
  queue.enqueue(1);
  queue.enqueue(2);
  queue.enqueue(3);

  // Check if queue overflow is handled correctly
  CHECK_THROWS_AS(queue.enqueue(4), overflow_error);
}

TEST_CASE("Queue underflow") {
  // Create queue
  Queue<int> queue(3);

  // Check if queue underflow is handled correctly
  CHECK_THROWS_AS(queue.dequeue(), underflow_error);
}
