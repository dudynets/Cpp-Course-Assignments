#include <iostream>
#include <vector>

using namespace std;

template<typename T>
int counter(const vector<T> &array, const T &element) {
  int count = 0;

  for (T _element : array) {
    if (_element == element) {
      count++;
    }
  }

  return count;
}

int main() {
  try {
    // Prompting for elements
    int numberOfElements = 0;

    cout << "Enter the number of elements: ";
    cin >> numberOfElements;

    if (cin.fail()) {
      throw invalid_argument("number of elements must be an integer");
    }

    vector<int> elements(numberOfElements);

    for (int i = 0; i < numberOfElements; i++) {
      cout << "Enter element number " << i + 1 << ": ";

      cin >> elements[i];

      if (cin.fail()) {
        throw invalid_argument("element must be a valid integer");
      }
    }

    // Prompting for element to count
    int elementToFind;
    cout << "Enter the element you want to find: ";
    cin >> elementToFind;

    if (cin.fail()) {
      throw invalid_argument("element to find must be a valid integer");
    }

    // Finding the number of element occurrences
    int count = counter<int>(elements, elementToFind);

    // Printing the result
    cout << "The number of \"" << elementToFind << "\" element occurrences in the array is " << count;
  }
  catch (invalid_argument &error) {
    cout << "Error: " << error.what();
  }
  catch (...) {
    cout << "Unknown error";
  }

  return 0;
}
