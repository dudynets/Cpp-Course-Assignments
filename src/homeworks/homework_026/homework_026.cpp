#include <iostream>

using namespace std;

// Function that sorts elements of array from 0 to i
template<typename T>
void sort(T *arr, int n, int i) {
  // Validate array
  if (arr == nullptr) {
    throw invalid_argument("Invalid array");
  }

  // Validate index
  if (i < 0 || i >= n) {
    throw invalid_argument("Invalid index");
  }

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
  // Print header
  cout << "Sort array of integers by index\n\n";

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
  // Print header
  cout << "Sort array of strings by index\n\n";

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

    // Validate max length (string)
    if (arr[i].length() > 20) {
      throw length_error("Invalid value length");
    }
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
  try {
    // Test with integers
    sortIntegers();
  } catch (invalid_argument &e) {
    cerr << "\nError: " << e.what();
  } catch (length_error &e) {
    cerr << "\nError: " << e.what();
  } catch (...) {
    cerr << "\nError: Unknown error";
  }

  // Print divider
  cout << "\n\n================\n\n";

  try {
    // Test with strings
    sortStrings();
  } catch (invalid_argument &e) {
    cerr << "\nError: " << e.what();
  } catch (length_error &e) {
    cerr << "\nError: " << e.what();
  } catch (...) {
    cerr << "\nError: Unknown error";
  }

  return 0;
}
