#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include <exception>
#include "doctest/doctest.h"

using namespace std;

// Structure that represents an element of the priority queue
template<typename T>
struct Element {
  T value;
  int priority;
};

// Class that represents a priority queue
template<typename T>
class PriorityQueue {
 private:
  // Array that stores the elements of the priority queue
  Element<T> *elements;

  // Maximum size of the priority queue
  int maxSize;

  // Current size of the priority queue
  int currentSize;

 public:
  // Constructor
  explicit PriorityQueue(int size = 10) {
    elements = new Element<T>[size];
    maxSize = size;
    currentSize = 0;
  }

  // Destructor
  ~PriorityQueue() {
    delete[] elements;
  }

  // Method that adds an element to the priority queue
  void enqueue(T value, int priority) {
    // Check if priority queue is full
    if (currentSize == maxSize) {
      // If it is, throw an exception
      throw overflow_error("Priority queue overflow");
    }

    // Define the index where the new element should be inserted
    int insertIndex = 0;

    // Loop through the elements of the priority queue
    for (int i = 0; i < currentSize; i++) {
      // If the priority of the new element is higher than the priority of the current element,
      if (priority < elements[i].priority) {
        // Set the index where the new element should be inserted to the current index
        insertIndex = i;

        // Stop the loop
        break;
      } else {
        // Otherwise, insert the new element after the current element
        insertIndex = i + 1;
      }
    }

    // Shift the elements to make room for the new element
    for (int i = currentSize; i > insertIndex; i--) {
      elements[i] = elements[i - 1];
    }

    // Insert the new element
    elements[insertIndex].value = value;
    elements[insertIndex].priority = priority;

    // Increment current size of priority queue
    currentSize++;
  }

  // Method that removes the element with the highest priority from the priority queue
  void dequeue() {
    // Check if priority queue is empty
    if (currentSize == 0) {
      // If it is, throw an exception
      throw underflow_error("Priority queue underflow");
    }

    // Define the index of the element with the highest priority
    int maxIndex = 0;

    // Loop through the elements of the priority queue
    for (int i = 1; i < currentSize; i++) {
      // If the priority of the current element is higher than the priority of the element with the highest priority,
      // set the index of the element with the highest priority to the current index
      if (elements[i].priority > elements[maxIndex].priority) {
        maxIndex = i;
      }
    }

    // Shift the elements to remove the element with the highest priority
    for (int i = maxIndex; i < currentSize - 1; i++) {
      elements[i] = elements[i + 1];
    }

    // Decrement current size of priority queue
    currentSize--;
  }

  // Method that gets the element with the highest priority in the priority queue
  T peek() {
    // Check if priority queue is empty
    if (currentSize == 0) {
      // If it is, throw an exception
      throw underflow_error("Priority queue underflow");
    }

    // Return the last element in the priority queue, which is the element with the highest priority
    return elements[currentSize - 1].value;
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
TEST_CASE("Add elements to the priority queue") {
  // Create a priority queue
  PriorityQueue<int> priorityQueue(5);

  // Add elements to the priority queue
  priorityQueue.enqueue(1, 1);
  priorityQueue.enqueue(2, 2);
  priorityQueue.enqueue(3, 3);
  priorityQueue.enqueue(4, 4);
  priorityQueue.enqueue(5, 5); // Highest priority

  // Check if the elements were added to the priority queue
  CHECK(priorityQueue.peek() == 5);
}

TEST_CASE("Remove elements from the priority queue") {
  // Create a priority queue
  PriorityQueue<int> priorityQueue(5);

  // Add elements to the priority queue
  priorityQueue.enqueue(1, 1);
  priorityQueue.enqueue(2, 2);
  priorityQueue.enqueue(3, 3);
  priorityQueue.enqueue(4, 4);
  priorityQueue.enqueue(5, 5); // Highest priority

  // Remove elements from the priority queue
  priorityQueue.dequeue();
  priorityQueue.dequeue();
  priorityQueue.dequeue();
  priorityQueue.dequeue();
  priorityQueue.dequeue();

  // Check if the elements were removed from the priority queue
  CHECK_THROWS_AS(priorityQueue.peek(), underflow_error);
}

TEST_CASE("Add elements to the priority queue in the random priority order") {
  // Create a priority queue
  PriorityQueue<int> priorityQueue(5);

  // Add elements to the priority queue
  priorityQueue.enqueue(1, 2);
  priorityQueue.enqueue(2, 5); // Highest priority
  priorityQueue.enqueue(3, 4);
  priorityQueue.enqueue(4, 1);
  priorityQueue.enqueue(5, 3);

  // Check if the elements were added to the priority queue
  CHECK(priorityQueue.peek() == 2);
}

TEST_CASE("Add elements to the priority queue in the reverse priority order") {
  // Create a priority queue
  PriorityQueue<int> priorityQueue(5);

  // Add elements to the priority queue
  priorityQueue.enqueue(1, 5); // Highest priority
  priorityQueue.enqueue(2, 4);
  priorityQueue.enqueue(3, 3);
  priorityQueue.enqueue(4, 2);
  priorityQueue.enqueue(5, 1);

  // Check if the elements were added to the priority queue
  CHECK(priorityQueue.peek() == 1);
}

TEST_CASE("Add elements to the priority queue in the same priority order") {
  // Create a priority queue
  PriorityQueue<int> priorityQueue(5);

  // Add elements to the priority queue
  priorityQueue.enqueue(1, 1);
  priorityQueue.enqueue(2, 1);
  priorityQueue.enqueue(3, 1);
  priorityQueue.enqueue(4, 1);
  priorityQueue.enqueue(5, 1);

  // Check if the elements were added to the priority queue
  CHECK(priorityQueue.peek() == 5);
}

TEST_CASE("Add elements to the priority queue in the same priority order and remove them") {
  // Create a priority queue
  PriorityQueue<int> priorityQueue(5);

  // Add elements to the priority queue
  priorityQueue.enqueue(1, 1);
  priorityQueue.enqueue(2, 1);
  priorityQueue.enqueue(3, 1);
  priorityQueue.enqueue(4, 1);
  priorityQueue.enqueue(5, 1);

  // Remove elements from the priority queue
  priorityQueue.dequeue();
  priorityQueue.dequeue();
  priorityQueue.dequeue();
  priorityQueue.dequeue();
  priorityQueue.dequeue();

  // Check if the elements were removed from the priority queue
  CHECK_THROWS_AS(priorityQueue.peek(), underflow_error);
}

TEST_CASE("Priority queue overflow") {
  // Create a priority queue
  PriorityQueue<int> priorityQueue(5);

  // Add elements to the priority queue
  priorityQueue.enqueue(1, 1);
  priorityQueue.enqueue(2, 2);
  priorityQueue.enqueue(3, 3);
  priorityQueue.enqueue(4, 4);
  priorityQueue.enqueue(5, 5); // Highest priority

  // Check if the priority queue overflowed
  CHECK_THROWS_AS(priorityQueue.enqueue(6, 6), overflow_error);
}

TEST_CASE("Priority queue underflow") {
  // Create a priority queue
  PriorityQueue<int> priorityQueue(5);

  // Check if the priority queue underflowed
  CHECK_THROWS_AS(priorityQueue.dequeue(), underflow_error);
}
