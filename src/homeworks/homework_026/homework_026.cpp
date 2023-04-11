#include <iostream>

using namespace std;

// Function that sorts elements of array from 0 to i
template<typename T>
void sort(T *arr, int n, int i) {
  // Iterate through array
  for (int j = 0; j < i; j++) {
    // Iterate through array from j to i
    for (int k = j + 1; k < i; k++) {
      // Swap elements if they are not in order
      if (arr[j] > arr[k]) {
        T temp = arr[j];
        arr[j] = arr[k];
        arr[k] = temp;
      }
    }
  }
}

// Function that asks for elements of the array, applies sort function and prints sorted array
void sortIntegers() {
  // Ask for number of elements in array
  int n;
  cout << "Enter number of elements in array:\n";
  cout << "--> ";
  cin >> n;
  cout << "\n";

  // Ask for array elements
  int *arr = new int[n];
  cout << "Enter array:\n";
  for (int i = 0; i < n; i++) {
    cout << "--> ";
    cin >> arr[i];
  }
  cout << "\n";

  // Ask for index
  int index;
  cout << "Enter index:\n";
  cout << "--> ";
  cin >> index;

  // Sort array
  sort(arr, n, index);

  // Print sorted array
  cout << "\nSorted array of integers:\n";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }

  // Free memory
  delete[] arr;
}

// Function that asks for elements of the array, applies sort function and prints sorted array
void sortStrings() {
  // Ask for number of elements in array
  int n;
  cout << "Enter number of elements in array:\n";
  cout << "--> ";
  cin >> n;
  cout << "\n";

  // Ask for array elements
  auto *arr = new string[n];
  cout << "Enter array:\n";
  for (int i = 0; i < n; i++) {
    cout << "--> ";
    cin >> arr[i];
  }
  cout << "\n";

  // Ask for index
  int index;
  cout << "Enter index:\n";
  cout << "--> ";
  cin >> index;

  // Sort array
  sort(arr, n, index);

  // Print sorted array
  cout << "\nSorted array of strings:\n";
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
  }

  // Free memory
  delete[] arr;
}

// Main function
int main() {
  // Test with integers
  sortIntegers();

  // Print divider
  cout << "\n\n================\n\n";

  // Test with strings
  sortStrings();

  return 0;
}
