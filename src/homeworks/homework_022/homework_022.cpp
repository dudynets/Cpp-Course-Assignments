#include <iostream>

using namespace std;

// Function that sorts an array of elements of provided type in ascending order using the bubble sort algorithm
// Input:
//   - array: pointer to the array of elements
//   - numberOfElements: number of elements in the array
// Output:
//   - pointer to the sorted array
template<typename T>
T *bubbleSort(const T *array, int numberOfElements) {
  // Create a new array to store sorted elements
  T *sortedArray = new T[numberOfElements];

  // Copy array into sortedArray
  for (int i = 0; i < numberOfElements; i++) {
    sortedArray[i] = array[i];
  }

  // Iterate through all the elements in the array
  for (int i = 0; i < numberOfElements - 1; i++) {
    // Iterate through the unsorted part of the array in each iteration
    for (int j = 0; j < numberOfElements - i - 1; j++) {
      // Check if elements are in the wrong order
      if (sortedArray[j] > sortedArray[j + 1]) {
        // Swap elements
        T temp = sortedArray[j];
        sortedArray[j] = sortedArray[j + 1];
        sortedArray[j + 1] = temp;
      }
    }
  }

  // Return the sortedArray
  return sortedArray;
}

// Class that represents a person
class Person {
 private:
  string name;
  string address;
 public:
  // Constructors
  Person() = default;
  Person(string _name, string _address) : name(std::move(_name)), address(std::move(_address)) {}

  // Overload the > operator
  bool operator>(const Person &other) const {
    return this->name > other.name;
  }

  // Overload the << operator
  friend ostream &operator<<(ostream &os, const Person &person) {
    os << person.name << " from " << person.address;
    return os;
  }
};

// Main function
int main() {
  // Define an array of integers
  int unsortedIntegers[] = {4, 1, 3, 2, 5, 0, 6, 7, 9, 8};

  // Define an array of strings
  string unsortedStrings[] = {"a", "c", "b", "e", "d", "g", "f", "i", "h", "j"};

  // Define an array of people
  Person unsortedPeople[] = {
      Person("John", "London"),
      Person("Bob", "New York"),
      Person("Alice", "Paris"),
      Person("Mike", "Tokyo"),
      Person("Alex", "Berlin"),
      Person("Sam", "Rome"),
      Person("Tom", "Madrid"),
      Person("Sasha", "Lviv"),
      Person("Kate", "Kyiv"),
      Person("James", "Washington D.C.")
  };

  // Sort the arrays
  int *sortedIntegers = bubbleSort(unsortedIntegers, 10);
  string *sortedStrings = bubbleSort(unsortedStrings, 10);
  Person *sortedPeople = bubbleSort(unsortedPeople, 10);

  // Print the sorted array of integers
  cout << "Sorted integers:\n";
  for (int i = 0; i < 10; i++) {
    cout << "  - " << sortedIntegers[i] << "\n";
  }
  cout << "\n\n";

  // Print the sorted array of strings
  cout << "Sorted strings:\n";
  for (int i = 0; i < 10; i++) {
    cout << "  - " << sortedStrings[i] << "\n";
  }
  cout << "\n\n";

  // Print the sorted array of people
  cout << "Sorted people:\n";
  for (int i = 0; i < 10; i++) {
    cout << "  - " << sortedPeople[i] << "\n";
  }

  return 0;
}
