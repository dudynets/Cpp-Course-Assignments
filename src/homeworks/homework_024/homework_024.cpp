#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

// Function that modifies array and returns string
string Modified(double(*f)(double), double a[], int n) {
  // Create string stream
  ostringstream oss;

  // Set precision for double to 2 decimal places
  oss << fixed << setprecision(2);

  // Print table header
  oss << "----------------------------------------------------------\n";
  oss << "|  " << setw(17) << "i  |" << setw(19) << "a[i]  |" << setw(21) << "Modified a[i]  |\n";
  oss << "----------------------------------------------------------\n";

  // Print table body
  for (int i = 0; i < n; i++) {
    oss << "|  " << setw(14) << i << "  | " << setw(15) << a[i] << "  | " << setw(15) << f(a[i]) << "  |\n";
  }
  oss << "----------------------------------------------------------\n";

  // Return string
  return oss.str();
}

double square(double x) {
  return pow(x, 2);
}

double sinCosTg(double x) {
  return sin(x) + cos(x) - tan(x);
}

double nearestInt(double x) {
  return round(x);
}

// Main function
int main() {
  // Define a file stream and open a file
  ofstream ofs("../src/homeworks/homework_024/output.txt");

  // Check if the file is open
  if (!ofs.is_open()) {
    cout << "Error opening file" << endl;
    return 1;
  }

  // Define an array of doubles
  double a[] = {
      1.1,
      2.2,
      3.3,
      4.4,
      5.5,
      6.6,
      7.7,
      8.8,
      9.9,
      10.1,
      11.2,
      12.3,
      13.4,
      14.5,
      15.6,
      16.7,
      17.8,
      18.9,
      19.0
  };

  // Get array size
  int n = sizeof(a) / sizeof(a[0]);

  // Print modified array (square)
  ofs << "SQUARE:\n  — Function: a[i]^2\n";
  ofs << Modified(square, a, n);
  ofs << "\n\n";

  // Print modified array (sin + cos - tg)
  ofs << "SIN + COS - TG:\n  — Function: sin(a[i]) + cos(a[i]) - tg(a[i])\n";
  ofs << Modified(sinCosTg, a, n);
  ofs << "\n\n";

  // Print modified array (nearest integer)
  ofs << "NEAREST INTEGER:\n";
  ofs << Modified(nearestInt, a, n);
  ofs << "\n\n";

  // Nearest integer using lambda
  ofs << "NEAREST INTEGER USING LAMBDA:\n";
  ofs << Modified([](double x) { return round(x); }, a, n);

  // Close the file
  ofs.close();

  return 0;
}
