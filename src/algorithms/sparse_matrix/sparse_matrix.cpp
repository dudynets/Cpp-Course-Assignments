#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include "doctest/doctest.h"

using namespace std;

// Structure that represents a matrix element
struct MatrixElement {
  int col;
  int value;
};

// Structure that represents a node in a linked list
struct ListNode {
  MatrixElement matrixElement;
  ListNode *nextNode = nullptr;

  ListNode(MatrixElement _matrixElement, ListNode *_nextNode = nullptr) {
    matrixElement = _matrixElement;
    nextNode = _nextNode;
  }
};

// Class that implements a linked list
class List {
 private:
  ListNode *listHead;
  int size;

 public:
  // Constructor
  List() {
    listHead = nullptr;
    size = 0;
  }

  // Destructor
  ~List() {
    // While the list is not empty, delete the first node
    while (listHead != nullptr) {
      // Save the next node
      ListNode *next = listHead->nextNode;

      // Delete the current node
      delete listHead;

      // Move to the next node
      listHead = next;
    }
  }

  // Method that adds a new element at the end of the list
  void push_back(MatrixElement elem) {
    // Check if the list is empty
    if (listHead == nullptr) {
      // If it is, create a new node and make it the head of the list
      listHead = new ListNode(elem);
    } else {
      // If it is not, traverse the list until the last node is reached
      ListNode *currentNode = listHead;
      while (currentNode->nextNode != nullptr) {
        currentNode = currentNode->nextNode;
      }

      // Create a new node and add it to the end of the list
      currentNode->nextNode = new ListNode(elem);
    }

    // Increase the size of the list
    size++;
  }

  // Method that inserts a new element at a given index
  void insert(int index, MatrixElement elem) {
    // Check if the index is valid
    if (index == 0) {
      // If it is, create a new node and make it the head of the list
      listHead = new ListNode(elem, listHead);

      // Increase the size of the list
      size++;
    } else {
      // If it is not, traverse the list until the node before the index is reached
      ListNode *currentNode = listHead;
      int i = 0;
      while (i < index - 1 && currentNode->nextNode != nullptr) {
        currentNode = currentNode->nextNode;
        i++;
      }

      // Create a new node and add it to the list
      currentNode->nextNode = new ListNode(elem, currentNode->nextNode);

      // Increase the size of the list
      size++;
    }
  }

  // Getter for the size of the list
  [[nodiscard]] int getSize() const {
    return size;
  }

  // Overload of the [] operator
  MatrixElement &operator[](int index) {
    // Traverse the list until the index is reached
    ListNode *currentNode = listHead;
    int i = 0;
    while (i < index && currentNode != nullptr) {
      currentNode = currentNode->nextNode;
      i++;
    }

    // Return the element at the index
    return currentNode->matrixElement;
  }
};

// Class that implements a sparse matrix
class SparseMatrix {
 private:
  int rows;
  int cols;
  List *matrix;

 public:
  // Constructor
  SparseMatrix(int rows, int cols) {
    this->rows = rows;
    this->cols = cols;
    matrix = new List[rows];
  }

  // Destructor
  ~SparseMatrix() {
    delete[] matrix;
  }

  // Method that inserts a new element in the matrix
  void insert(int row, int col, int value) {
    // Validate the position
    if (row >= rows || col >= cols) {
      throw out_of_range("position is invalid");
      return;
    }

    // If the value is 0, do not insert it
    if (value == 0) {
      return;
    }

    // Check if the element already exists
    List &rowList = matrix[row];
    for (int i = 0; i < rowList.getSize(); i++) {
      if (rowList[i].col == col) {
        rowList[i].value = value;
        return;
      }
    }

    // If it does not exist, insert it in the correct position
    rowList.push_back({col, value});
  }

  // Method that returns the value of an element in the matrix
  int get(int row, int col) {
    // Validate the position
    if (row >= rows || col >= cols) {
      throw out_of_range("position is invalid");
      return 0;
    }

    // Traverse the list until the element is found
    List &rowList = matrix[row];
    for (int i = 0; i < rowList.getSize(); i++) {
      if (rowList[i].col == col) {
        // If the element is found, return its value
        return rowList[i].value;
      }
    }

    // If the element is not found, return 0
    return 0;
  }

  // Method that prints the matrix
  void print() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        int value = get(i, j);
        cout << value << " ";
      }
      cout << "\n";
    }
  }
};

int main() {
  // Run tests
  doctest::Context context;
  int res = context.run();
  return res;
}

// Test cases
TEST_CASE("Adding elements to the matrix") {
  SparseMatrix mat(3, 4);

  mat.insert(0, 1, 5);
  mat.insert(1, 2, 3);
  mat.insert(2, 0, 2);
  mat.insert(2, 3, 4);

  CHECK(mat.get(0, 1) == 5);
  CHECK(mat.get(1, 2) == 3);
  CHECK(mat.get(2, 0) == 2);
  CHECK(mat.get(2, 3) == 4);
}

TEST_CASE("Adding zero elements to the matrix") {
  SparseMatrix mat(3, 4);

  mat.insert(0, 1, 5);
  mat.insert(1, 2, 3);
  mat.insert(2, 0, 2);
  mat.insert(2, 3, 4);
  mat.insert(2, 1, 0); // this element should not be saved

  CHECK(mat.get(0, 1) == 5);
  CHECK(mat.get(1, 2) == 3);
  CHECK(mat.get(2, 0) == 2);
  CHECK(mat.get(2, 3) == 4);
  CHECK(mat.get(2, 1) == 0);
}

TEST_CASE("Adding elements to the matrix in the wrong order") {
  SparseMatrix mat(3, 4);

  mat.insert(0, 1, 5);
  mat.insert(1, 2, 3);
  mat.insert(2, 0, 2);
  mat.insert(2, 3, 4);
  mat.insert(2, 1, 0); // this element should not be saved
  mat.insert(0, 0, 1);
  mat.insert(1, 0, 2);
  mat.insert(1, 1, 3);
  mat.insert(2, 2, 4);

  CHECK(mat.get(0, 0) == 1);
  CHECK(mat.get(0, 1) == 5);
  CHECK(mat.get(1, 0) == 2);
  CHECK(mat.get(1, 1) == 3);
  CHECK(mat.get(1, 2) == 3);
  CHECK(mat.get(2, 0) == 2);
  CHECK(mat.get(2, 1) == 0);
  CHECK(mat.get(2, 2) == 4);
  CHECK(mat.get(2, 3) == 4);
}

TEST_CASE("Adding an element to invalid position") {
  SparseMatrix mat(3, 4);

  CHECK_THROWS(mat.insert(17, 12, 5));
  CHECK_THROWS(mat.get(17, 12));

  mat.insert(2, 3, 5);
  CHECK(mat.get(2, 3) == 5);
}

TEST_CASE("Printing matrix") {
  SparseMatrix mat(3, 4);

  mat.insert(0, 1, 5);
  mat.insert(1, 2, 3);
  mat.insert(2, 0, 2);
  mat.insert(2, 3, 4);

  ostringstream out;
  streambuf *coutBuffer = cout.rdbuf();
  cout.rdbuf(out.rdbuf());
  mat.print();
  cout.rdbuf(coutBuffer);

  CHECK(out.str() == "0 5 0 0 \n0 0 3 0 \n2 0 0 4 \n");
}
