#define DOCTEST_CONFIG_IMPLEMENT

#include <stack>
#include <doctest/doctest.h>

using namespace std;

// Class that implements a stack
class CustomStack {
 private:
  // Max size of the stack
  int size;

  // Array that stores the elements in the stack
  int *array;

  // Current number of elements in the stack
  int count;
 public:
  // Constructor
  CustomStack(int _size) : size(_size), array(new int[size]), count(0) {};

  // Destructor
  ~CustomStack() {
    delete[] array;
  }

  // Method that deletes the last element in the stack
  void pop() {
    if (!isEmpty()) {
      array[count--] = 0;
    }
  }

  // Method that adds a new element to the end of the stack
  void push(int value) {
    if (count == size) {
      // shift all elements to the left
      for (int i = 0; i < count; i++) {
        array[i] = array[i + 1];
      }

      // add new element to the end
      array[count - 1] = value;
    } else {
      // add new element to the end
      array[count++] = value;
    }
  }

  // Method that swaps two elements in the stack
  void swap(int index1, int index2) {
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
  }

  // Getter for top element in stack
  int getTop() const {
    return array[count - 1];
  }

  // Getter that defines if stack is empty
  bool isEmpty() const {
    return count == 0;
  }

  // Getter for count
  int getCount() const {
    return count;
  }

  // Getter for array
  int *getArray() const {
    return array;
  }
};

// Main function
int main() {
  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

// Test cases for custom stack
TEST_CASE("Push and pop in custom stack") {
  CustomStack stack(5);

  stack.push(1);
  stack.push(2);
  stack.push(3);
  CHECK(stack.getCount() == 3);

  stack.pop();
  CHECK(stack.getCount() == 2);

  int *array = stack.getArray();
  CHECK(array[0] == 1);
  CHECK(array[1] == 2);
}

TEST_CASE("Adding more elements than size to custom stack") {
  CustomStack stack(5);

  stack.push(1);
  stack.push(2);
  stack.push(3);
  stack.push(4);
  stack.push(5);
  stack.push(6);
  CHECK(stack.getCount() == 5);

  int *array = stack.getArray();
  CHECK(array[0] == 2);
  CHECK(array[1] == 3);
  CHECK(array[2] == 4);
  CHECK(array[3] == 5);
  CHECK(array[4] == 6);
}

TEST_CASE("Getting top element in custom stack") {
  CustomStack stack(5);

  stack.push(1);
  stack.push(2);
  stack.push(3);
  CHECK(stack.getTop() == 3);
}

TEST_CASE("Emptying custom stack") {
  CustomStack stack(5);

  stack.push(1);
  stack.push(2);
  stack.push(3);
  CHECK(stack.getCount() == 3);

  stack.pop();
  stack.pop();
  stack.pop();
  CHECK(stack.isEmpty());
}

TEST_CASE("Swapping elements in custom stack") {
  CustomStack stack(5);

  stack.push(1);
  stack.push(2);
  stack.push(3);
  CHECK(stack.getTop() == 3);

  stack.swap(0, 2);
  CHECK(stack.getTop() == 1);
}

// Test cases for STL stack
TEST_CASE("Push and pop in STL stack") {
  stack<int> stack;

  stack.push(1);
  stack.push(2);
  stack.push(3);
  CHECK(stack.size() == 3);

  stack.pop();
  CHECK(stack.size() == 2);
}

TEST_CASE("Getting top element in STL stack") {
  stack<int> stack;

  stack.push(1);
  stack.push(2);
  stack.push(3);
  CHECK(stack.top() == 3);
}

TEST_CASE("Emptying STL stack") {
  stack<int> stack;

  stack.push(1);
  stack.push(2);
  stack.push(3);
  CHECK(stack.size() == 3);

  stack.pop();
  stack.pop();
  stack.pop();
  CHECK(stack.empty());
}

TEST_CASE("Swapping elements in STL stack") {
  stack<int> stack1;
  stack<int> stack2;

  stack1.push(1);
  stack1.push(2);
  stack1.push(3);
  CHECK(stack1.top() == 3);

  stack2.push(4);
  stack2.push(5);
  stack2.push(6);
  CHECK(stack2.top() == 6);

  stack1.swap(stack2);
  CHECK(stack1.top() == 6);
  CHECK(stack2.top() == 3);
}
