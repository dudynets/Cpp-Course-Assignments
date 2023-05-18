#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

// Functor for the transform function
struct Fun {
  double max;

  explicit Fun(double _max) : max(_max) {}

  double operator()(double x) const {
    if (x > 0) {
      return max;
    } else {
      return x;
    }
  }
};

// Function that solves the problem
void f(vector<double> &l1, vector<double> &l2) {
  // Get the iterator to the maximum element in l2
  auto max_it = max_element(l2.begin(), l2.end());

  // Get the maximum element in l2
  double max = *max_it;

  // Transform l1 using the Fun functor
  transform(l1.begin(), l1.end(), l1.begin(), Fun(max));

  // Remove all negative elements from l1 and copy them to l2
  remove_copy_if(l1.begin(), l1.end(), back_inserter(l2), [](double x) { return x <= 0; });

  // Compute the sum of the elements in l2
  double sum = accumulate(l2.begin(), l2.end(), 0.0);

  // Print the results
  cout << "l1: ";
  for (auto x : l1) {
    cout << x << " ";
  }
  cout << endl;
  cout << "l2: ";
  for (auto x : l2) {
    cout << x << " ";
  }
  cout << endl;
  cout << "Sum of l2: " << sum << endl;
}

// Main function
int main() {
  vector<double> l1 = {1.0, 2.0, -3.0, 4.0, -5.0};
  vector<double> l2 = {-6.0, -7.0, 8.0, -9.0, 10.0};
  f(l1, l2);

  return 0;
}
